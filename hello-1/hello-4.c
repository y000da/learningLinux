// Пробуем передавать аргументы командной строки в модуль

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>	// Для приема аргументов командной строки
#include <linux/stat.h>		// Содержит определения для работы с правами 
				// доступа и типами файлов

MODULE_LICENSE("GPL");

static short int myshort = 1;
static int myint = 420;
static long int mylong = 9999;
static char*mystring = "blah blah blah";
static int myintarray[2] = { 420, 420 };
static int arr_argc = 0;

module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "A long integer");
module_param_array(myintarray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintarray, "An array of integers");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");


static int __init hello_4_init(void) {
	pr_info("Hello World 4 !\n=================\n");
	pr_info("myshort is a short integer: %hd\n", myshort);
	pr_info("myint is an integer: %d\n", myint);
	pr_info("mylong is a long integer: %ld\n", mylong);
	pr_info("mystring is a string: %s\n", mystring);

	for (int i = 0; i < ARRAY_SIZE(myintarray); i++) {
		pr_info("myintarray[%d] = %d\n", i, myintarray[i]);
	}
	pr_info("got %d arguments for myintarray.\n", arr_argc);
	return 0;
}

static void __exit hello_4_exit(void) {
	pr_info("Goodbye World 4 !\n");
}

module_init(hello_4_init);
module_exit(hello_4_exit);