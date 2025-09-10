#include <linux/kernel.h> // Тут есть pr_info()
#include <linux/module.h> // Must-have для всех модулей
#include <linux/init.h>


static int __init hello_2_init(void) {
	pr_info("INFO Hello world 2 !\n");
	pr_emerg("EMERGENCY Hello world 2 !\n");
	pr_alert("ALERT Hello world 2 !\n");
	pr_crit("CRITICAL Hello world 2 !\n");
	pr_err("ERROR Hello world 2 !\n");
	pr_warn("WARNING Hello world 2 !\n");
	pr_notice("NOTICE Hello world 2 !\n");
	pr_debug("DEBUG Hello world 2 !\n");
	return 0;
}

static void __exit hello_2_exit(void) {
	pr_info("Goodbye world 2 !\n");
}

module_init(hello_2_init);
module_exit(hello_2_exit);

MODULE_LICENSE("GPL");