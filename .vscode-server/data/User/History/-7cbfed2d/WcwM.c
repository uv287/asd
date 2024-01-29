#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

int pid = 1;
module_param(pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

unsigned long v_add;
module_param(v_add, unsigned long, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

static int __init virtual_to_physical(void)
{
    
}

static void __exit add_conver_exit(void)
{

}

module_init(virtual_to_physical);
module_exit(add_conver_exit);