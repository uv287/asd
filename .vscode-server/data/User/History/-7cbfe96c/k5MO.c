#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/unistd.h>
#include <linux/param.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("23M0788");
MODULE_DESCRIPTION("This programme To findout the physical address of the given pid");

unsigned long pa =0;
int pid = 1;
struct page *pg;
module_param(pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

unsigned long va = 0;
module_param(va, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

static int __init virtual_to_physical(void)
{
    struct task_struct *process;
    struct mm_struct *mm;
    struct mm_rss_stat *rss_stat;

    //pagesize = sysconf(_SC_PAGE_SIZE);

    struct pid *pid_struct = find_get_pid(pid);
    process = pid_task(pid_struct, PIDTYPE_PID);
    mm = process -> mm;

    unsigned long pages = mm -> total_vm;

    unsigned long va_size;
    va_size=pages * PAGE_SIZE;

    printk("Size of the virtual address space is : %lu\n",va_size);

    rss_stat = &mm->rss_stat;

    unsigned long physical_size = 0;
    physical_size += atomic_long_read(&rss_stat->count[MM_FILEPAGES]);
    physical_size += atomic_long_read(&rss_stat->count[MM_ANONPAGES]);
    physical_size += atomic_long_read(&rss_stat->count[MM_SHMEMPAGES]);

    printk("Size of the Physical address space is : %lu\n",physical_size*PAGE_SIZE);

    return 0;
}

static void __exit add_conver_exit(void)
{
   printk("Exiting the lkm3 module\n");
}

module_init(virtual_to_physical);
module_exit(add_conver_exit);