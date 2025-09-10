// chardev.c: Создает символьное устройство, которое сообщает, сколько раз
// происходило считывание из файла при обращении к нему через /dev/DEVICE_NAME
// Не поддерживается операция записи

#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/poll.h>

MODULE_LICENSE("GPL");

// Прототипы функций, обычно помещаются в .h-файл
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char __user *, size_t, 
				loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "chardev"	// Имя устройства, как оно показано в /proc/devices
#define BUF_LEN 80		// Максимальная длина сообщения устройства

static int major;	// Старший номер устройства

enum {
	CDEV_NOT_USED = 0,
	CDEV_EXCLUSICE_OPEN = 1,
};

// Проверка, открыто ли устройство. Предотвращает множественное обращение
// к устройству
static atomic_t already_open = ATOMIC_INIT(CDEV_NOT_USED); 
// atomic_t -- специальный тип для атомарных операций


static char msg[BUF_LEN]; // Сообщение, которое устройство будет выдавать при запросе

static struct class *cls; // Структура для создания класса устройств

static struct file_operations chardev_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
};

static int __init chardev_init(void) {
	major = register_chrdev(0, DEVICE_NAME, &chardev_fops);
	if (major < 0) {
		pr_alert("Registering char device failed with %d\n", major);
		return major;
	}
	pr_info("I was assigned major number %d.\n", major);

	cls = class_create(THIS_MODULE, DEVICE_NAME);
	device_create(cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
	pr_info("Device created on /dev/%s\n", DEVICE_NAME);

	return SUCCESS;
}

static void __exit chardev_exit(void) {
	device_destroy(cls, MKDEV(major, 0));
	class_destroy(cls);
	unregister_chrdev(major, DEVICE_NAME);
	pr_info("Device succesfully destroyed!");
}

static int device_open(struct inode *inode, struct file *file) {
	static int counter = 0;
	
	if (atomic_cmpxchg(&already_open, CDEV_NOT_USED, CDEV_EXCLUSICE_OPEN)) {
		return -EBUSY;
	} 	// atomic_cmpxchg сравнивает значение, хранящееся в первом аргументе
		// с ожидаем значением (второй аргумент), если они равны, то записывает
		// новое значение (третий аргумент), если не равны, то ничего не делает
		// return -EBUSY -- код ошибки errno, который возвращается, если 
		// устройство уже отрыто
	sprintf(msg, "I already told you %d times Hello world!\n", counter++);
	try_module_get(THIS_MODULE);	// Безопасно увеличивает счетчик ссылок модуля,
					// если он еще не выгружается
	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file) {
	atomic_set(&already_open, CDEV_NOT_USED);
	module_put(THIS_MODULE);
	return SUCCESS;
}

static ssize_t device_read(struct file *filp, char __user *buffer,
				size_t length, loff_t *offset) {
	int bytes_read = 0;
	const char *msg_ptr = msg;

	if (!*(msg_ptr + *offset)) {
		*offset = 0;
		return 0;
	}

	msg_ptr += *offset;
	while (length && *msg_ptr) {
		put_user(*(msg_ptr++), buffer++);
		--length;
		++bytes_read;
	}

	*offset += bytes_read;
	return bytes_read;
}

static ssize_t device_write(struct file *filp, const char __user *buff,
				size_t len, loff_t *off) {
	pr_alert("Sorry, this operation is not supported.\n");
	return -EINVAL;
}

module_init(chardev_init);
module_exit(chardev_exit);