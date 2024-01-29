#include<linux/kernal.h>
#include<linux/module.h>
#include<linux/init.h>

static int __init module_enter(void)
{

}

static void __exit module_exit(void)
{

}

module_init(module_enter);
module_exit(module_exit);