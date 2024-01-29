#include<linux/module.h>
#include<linux/init.h>
#include<linux/printk.h>

static int __init entry()
{
    pr_info("Welcome");
    return 0;
}

static void __exit exit()
{
    pr_info("Goodbye");
}

module_init(entry);
module_exit(exit);

MODULE_LICENSE("GPL");