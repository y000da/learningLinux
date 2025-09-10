#include <linux/kernel.h> // Тут есть pr_info()
#include <linux/module.h> // Must-have для всех модулей


int init_module(void) {
	pr_info("INFO Hello world 1 !\n");
	pr_emerg("EMERGENCY Hello world 1!\n");
	pr_alert("ALERT Hello world 1 !\n");
	pr_crit("CRITICAL Hello world 1 !\n");
	pr_err("ERROR Hello world 1 !\n");
	pr_warn("WARNING Hello world 1 !\n");
	pr_notice("NOTICE Hello world 1 !\n");
	pr_debug("DEBUG Hello world 1 !\n");
	return 0;
}

void cleanup_module(void) {
	pr_info("Goodbye world !\n");
}

MODULE_LICENSE("GPL");