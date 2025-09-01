#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>

#define DEVICE_NAME "dummy"
#define MAJOR_NUM 42
#define NUM_DEVICES 4

static struct class *dummy_class;

// Файловые операции драйвера, они вызываются, когда программа в 
// пользовательском пространстве вызывает open(), read(), write() и
// close().
// 
// В данном случае каждая функция просто выводит сообщение ядра, чтобы 
// было видно, что к ней обращались.
static int dummy_open(struct inode *inode, struct file *file) {
        pr_info("%s\n", __func__);
        return 0;
}
static int dummy_release(struct inode *inode, struct  file *file) {
        pr_info("%s\n", __func__);
        return 0;
}
static ssize_t dummy_read(struct file *file, char *buffer, size_t length, 
                        loff_t *offset) {
        pr_info("%s %u\n", __func__, length);
        return 0;
}
static ssize_t dummy_write(struct file *file, const char *buffer, size_t length, 
                        loff_t *offset) {
        pr_info("%s %u\n", __func__, length);
        return length;
} 

struct file_operations dummy_flops = {  // Структура , содержащая указатели на
// четыре функции, реализованные в драйвере
        .owner = THIS_MODULE,
        .open = dummy_open,
        .release = dummy_release,
        .read = dummy_read,
        .write = dummy_write,
};

int __init dummy_init(void) {   // Функция, вызываемая сразу после загрузки модуля
        printk("Dummy loaded\n");

        int ret = register_chrdev(MAJOR_NUM, DEVICE_NAME, &dummy_flops);        //
        // Функция, необходимая для обозначения того, что это драйвер символьного
        // устройства. Сообщает ядру о существовании драйвера со старшим номером 
        // MAJOR_NUM, но ничего не говорит о типе драйвера, поэтому подкаталог в
        // /sys/class не создается.
        if (ret != 0) return ret;

        dummy_class = class_create(DEVICE_NAME);   // Создание класса
        // устройства dummy. В результате образуется каталог /sys/class/dummy

        for (int i = 0; i < NUM_DEVICES; i++) { // Создание NUM_DEVICES устройств
        // класса dummy. В результате образуются их подкаталоги 
        //в /sys/class/dummy/. В каждом подкаталоге -- файл dev, содержащий
        // старший и младший номера устройств. Это всё, что необходимо диспетчеру
        // устройств для создания узлов устройств
                device_create(dummy_class, NULL, MKDEV(MAJOR_NUM, i), NULL, 
                "dummy%d", i);
        }

        return 0;
}
void __exit dummy_exit(void) {  // Освобождает ресурсы, захваченные функцией
// init. В данном случае освобождает класс устройств и старший номер.
        for (int i = 0; i < NUM_DEVICES; i++) {
                device_destroy(dummy_class, MKDEV(MAJOR_NUM, i));
        }

        class_destroy(dummy_class);
        unregister_chrdev(MAJOR_NUM, DEVICE_NAME);

        printk("Dummy unloaded\n");
}

module_init(dummy_init);        // Макросы, которые задают функции, вызываемые
module_exit(dummy_exit);        // при загрузке и выгрузке модуля

MODULE_LICENSE("GPL");                  // Макросы, добавляющие базовую
MODULE_AUTHOR("Chris Simmonds");        // информацию о модуле, которую
MODULE_DESCRIPTION("A dummy driver");   // можно извлечь из откомпилированного
// кода модуля командой modinfo