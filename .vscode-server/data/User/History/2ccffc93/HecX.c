#include<linux/module.h>
#include<linux/init.h>
#include<linux/printk.h>

static int entry()
{
    pr_info("Welcome");
    return 0;
}

static void exit()
{
    pr_info("Goodbye");
}

module_init(entry);
module_exit(exit);