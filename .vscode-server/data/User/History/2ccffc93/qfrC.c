#include<linux/module.h>
#include<linux/init.h>
#include<linux/printk.h>

static int __init hello_2_init()
{
    pr_info("Welcome");
    return 0;
}

static void __exit hello_2_exit()
{
    pr_info("Goodbye");
}

module_init(hello_2_init);
module_exit(hello_2_exit);

MODULE_LICENSE("GPL");