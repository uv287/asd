#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <unistd.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("23M0788");
MODULE_DESCRIPTION("This programme To findout the physical address of the given pid");

unsigned long pa =0;
static size_t pagesize;
int pid = 1;
struct page *pg;
module_param(pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

unsigned long va = 0;
module_param(va, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

static int __init virtual_to_physical(void)
{
    struct task_struct *process;
    unsigned long pfn;
    struct mm_struct *mm;
    struct vm_area_struct *vm;

    pagesize = sysconf(_SC_PAGE_SIZE);

    struct pid *pid_struct = find_get_pid(pid);
    process = pid_task(pid_struct, PIDTYPE_PID);
    mm = process -> mm;

    down_read(&mm->mmap_lock);

    

    up_read(&mm->mmap_lock);

    return 0;
}

static void __exit add_conver_exit(void)
{
   printk("Exiting the lkm3 module\n");
}

module_init(virtual_to_physical);
module_exit(add_conver_exit);