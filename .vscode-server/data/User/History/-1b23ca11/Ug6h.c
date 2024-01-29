#include<linux/module.h>
#include <linux/init.h>

MODULE_DESCRIPTION("Module which print the running process in the machine");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("23M0788");

static int __init entry(void)
{
    struct task_struct *processes;

    if(processes->state==TASK_RUNNING)
    {
        printk(KERN_INFO "Process Name : %s -> Process ID : %d\n",processes->comm, processes->pid);
    }
}

static void __exit exit(void)
{

}

module_init(entry);
module_exit(exit);