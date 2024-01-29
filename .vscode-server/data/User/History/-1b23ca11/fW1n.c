#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>

MODULE_DESCRIPTION("Module which prints the running process in the machine");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("23M0788");

// Rename initialization function
int __init init_module_entry(void)
{
    struct task_struct *processes;
    struct list_head *head = &current->tasks;

    list_for_each_entry(processes, head, tasks)
    {
        if (processes->stats == TASK_RUNNING)
        {
            printk(KERN_INFO "Process Name: %s -> Process ID: %d\n", processes->comm, processes->pid);
        }
    }

    return 0;
}

// Rename exit function
void __exit exit_module(void)
{
    printk(KERN_INFO "Exiting lkml1 module\n");
}

// Use module_init and module_exit macros with renamed functions
module_init(init_module_entry);
module_exit(exit_module);
