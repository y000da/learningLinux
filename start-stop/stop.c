#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

void cleanup_module(void) {
    pr_info("Short is the life of a kernel module\n");
}