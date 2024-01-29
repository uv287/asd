#include<linux/module.h>
#include <linux/init.h>
#include<linux/kernel.h>
#include <linux/sched.h>

MODULE_DESCRIPTION("Module which print the running process in the machine");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("23M0788");

static int __init init_module(void)
{
    struct task_struct *processes;
    struct list_head *head = &current->tasks;

    list_for_each_entry(processes, head, tasks)
    {
        if(processes->state==TASK_RUNNING)
        {
            printk(KERN_INFO "Process Name : %s -> Process ID : %d\n",processes->comm, processes->pid);
        }
    }

    return 0;
}

static void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting lkml1 module");
}

module_init(module_entry);
module_exit(module_exit);