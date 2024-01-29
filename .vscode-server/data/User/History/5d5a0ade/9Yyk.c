#include<linux/kernal.h>
#include<linux/module.h>
#include<linux/proc_fs.h>

#define HAVE_PROC_OPS

#define procfs_name "hello_procfs"

static struct proc_dir_entry *proc_file;

static const struct proc_ops file_perm = {
.proc_read = reading;
};

static int __init proc_entry(void)
{
    proc_file = proc_create(procfs_name, 0644, NULL, &file_perm);

    if(proc_file == NULL)
    {
        proc_remove(proc_file);
        printk(KERN_ALERT "%s file could not intilize in prfoc directory",procfs_name);
        return -ENOMEM;
    }
    else
    {
        printk(KERN_INFO "%s file cretaed in proc file system",procfs_name);
    }


}