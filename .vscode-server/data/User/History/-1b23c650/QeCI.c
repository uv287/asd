#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("23M0788");
MODULE_DESCRIPTION("This programme To findout the children of the given pid");

int pid = 1;
module_param(pid, int,  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

static int __init findout_chidren_of_process(void)
{
    //find out the process and store the pointer into the process pointer
    struct task_struct *process,*child;
    struct pid *pid_struct = find_get_pid(pid);

    struct list_head *head;

    process = pid_task(pid_struct, PIDTYPE_PID);

    if (!process) {
        printk(KERN_INFO "Process with PID %d not found\n", pid);
        return -EINVAL; // Return error code
    }
    
    //struct list_head child_head= process->children;

    list_for_each(head, &process->children)
    {
        child= list_entry(head, struct task_struct, sibling);
        printk(KERN_INFO "Process Name: %s -> Process ID: %d\n", child->comm, child->pid);
    }

    return 0;
    
}

static void __exit child_module_exit(void)
{
    printk("Exit from the child process findout module");
}

module_init(findout_chidren_of_process);
module_exit(child_module_exit);