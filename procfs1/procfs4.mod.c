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
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xb64bc54f, "proc_create" },
	{ 0x1e186b3e, "remove_proc_entry" },
	{ 0x2cf56265, "__dynamic_pr_debug" },
	{ 0x1347aded, "seq_open" },
	{ 0x66f10083, "seq_printf" },
	{ 0x10f28306, "seq_read" },
	{ 0xda06b58b, "seq_lseek" },
	{ 0x559256ad, "seq_release" },
	{ 0xc9d7e676, "module_layout" },
};

MODULE_INFO(depends, "");

