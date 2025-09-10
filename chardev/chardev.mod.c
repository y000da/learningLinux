#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xc3aaf0a9, "__put_user_1" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x92997ed8, "_printk" },
	{ 0x360b547d, "module_put" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xd5599ff5, "try_module_get" },
	{ 0xb6a802be, "__register_chrdev" },
	{ 0xc884d27b, "__class_create" },
	{ 0x6b0bb3db, "device_create" },
	{ 0x8a872e97, "device_destroy" },
	{ 0x4001da82, "class_destroy" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xc9d7e676, "module_layout" },
};

MODULE_INFO(depends, "");

