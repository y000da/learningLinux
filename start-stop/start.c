#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

int  init_module(void) {
    pr_info("Hello world -- this is the kernel speaking\n");
    return 0;
}