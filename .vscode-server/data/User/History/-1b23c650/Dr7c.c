#include<linux/kernal.h>
#include<linux/module.h>
#include<linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("23M0788");
MODULE_DESCRIPTION("")

int pid = 0;
module_param(pid, int,  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

static int __init module_enter(void)
{
    //find out the process and store the pointer into the process pointer
    struct task_struct *process;
    process=find_task_by_vid(pid);
    
    struct list_head *childrens= process->children;

    list_for_each_entry(child, childrens, next)
    {
         printk(KERN_INFO "Process Name: %s -> Process ID: %d\n", processes->comm, processes->pid);
    }
    
}

static void __exit module_exit(void)
{

}

module_init(module_enter);
module_exit(module_exit);