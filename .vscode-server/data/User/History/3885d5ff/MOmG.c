#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/vmstat.h>

#define HAVE_PROC_OPS

#define procfs_name "get_pgfaults"

static struct proc_dir_entry *proc_file;

static ssize_t reading(struct file *file, char __user *buffer, size_t len, loff_t *offset)
{
   int r_value;
   char ans[100];
   sprintf(ans,"Total page Faults are : ",get_mm_counter(NULL, MM_FAULTS));
}

static const struct proc_ops file_op = {
.proc_read = reading,
};

static int __init pgfault_entry(void)
{
    proc_file = proc_create(procfs_name, 0644, NULL, &file_op);

    if(proc_file == NULL)
    {
        proc_remove(proc_file);
        printk(KERN_ALERT "%s file could not intilize in prfoc directory",procfs_name);
        return -ENOMEM;
    }
    else
    {
        printk(KERN_INFO "%s file cretaed in proc file system",procfs_name);
        return 0;
    }

}

static void __exit pgfault_exit(void)
{
    proc_remove(proc_file);
    printk(KERN_INFO "%s file is removed from the proc file system",procfs_name);
}

module_init(pgfault_entry);
module_exit(pgfault_exit);

MODULE_LICENSE("GPL");