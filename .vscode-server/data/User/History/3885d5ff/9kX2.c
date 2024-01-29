#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/proc_fs.h>

#define HAVE_PROC_OPS

#define procfs_name "get_pgfaults"

static struct proc_dir_entry *proc_file;

static ssize_t reading(struct file *file, char __user *buffer, size_t len, loff_t *offset)
{
    char data[13]="Hello World!\n";
    int l = sizeof(data);
    ssize_t ans= l;

    if(*offset >= l || copy_to_user(buffer, data, l))
    {
        printk(KERN_INFO "Data copy failed in the user\n");
        ans=0;
        return ans;
    }
    else
    {
        printk(KERN_INFO "Procfile read %s\n",file->f_path.dentry->d_name.name);
        *offset = *offset + l;
        return ans;
    }
}

static const struct proc_ops file_perm = {
.proc_read = reading,
};

static int __init pgfault_entry(void)
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