#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/proc_fs.h>
#include <linux/kernel_stat.h>
#include <linux/pagemap.h>
#include <linux/mm.h>
#include <linux/errno.h>
#include <linux/kernel_stat.h>
#include <linux/pagemap.h>
#include <linux/swap.h>
#include <linux/slab.h>
#include <asm/io.h>


#define HAVE_PROC_OPS

#define procfs_name "get_pgfaults"

static struct proc_dir_entry *proc_file;

static ssize_t reading(struct file *file, char __user *buffer, size_t length, loff_t *offset)
{
   char ans[100];
   ssize_t len,l;
   unsigned long ev[NR_VM_EVENT_ITEMS];
   all_vm_events(ev);
   l=sprintf(ans,"Total page Faults are : %lu\n",ev[PGFAULT]);
   len =l;

//    if (l > len) {
//         return -EINVAL;
//     } else {
//         r_value = copy_to_user(buffer, ans, l);
//         if (r_value != 0) {
//             printk(KERN_INFO "Data copy failed in the user\n");
//             return -EFAULT; 
//         } else {
            
//             printk(KERN_INFO "Procfile read %s\n", file->f_path.dentry->d_name.name);
//             *offset += l; 
//             return l; 
//         }
//     }
    if(*offset >= l || copy_to_user(buffer, ans, l))
    {
        printk(KERN_INFO "Data copy failed in the user\n");
        len=0;
        return len;
    }
    else
    {
        printk(KERN_INFO "Procfile read %s\n",file->f_path.dentry->d_name.name);
        *offset = *offset + l;
        return len;
    }
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