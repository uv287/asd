#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/sched.h>

#include "dr_doom.h"

#define FIRST_MINOR 0
#define MINOR_CNT 1

static dev_t ioctl_dev;
static struct cdev ioctl_cdev;
static struct class *ioctl_class;

static int my_open(struct inode *inode, struct file *filp)
{
    return 0;
}

static int my_close(struct inode *inode, struct file *filp)
{
    return 0;
}

static void chng_prt(pid_t child_pid, pid_t new_parent_pid)
{
    struct task_struct *child_task, *new_parent_task;

    child_task = pid_task(find_get_pid(child_pid), PIDTYPE_PID);
    new_parent_task = pid_task(find_get_pid(new_parent_pid), PIDTYPE_PID);

    if (!child_task || !new_parent_task)
    {
        printk(KERN_INFO "Invalid PID(s)\n");
        return;
    }

    list_del_init(&child_task->sibling);

    child_task->parent = new_parent_task;
    child_task->real_parent = new_parent_task;

    list_add_tail(&child_task->sibling, &new_parent_task->children);

    printk(KERN_INFO "Changed parent for PID: %d to PID: %d\n", child_pid, new_parent_pid);
}

static long my_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    ioctl_arg_t ioctl_arg;

    switch (cmd)
    {
    case IOCTL_CHANGE_PARENT:
        if (copy_from_user(&ioctl_arg, (ioctl_arg_t *)arg, sizeof(ioctl_arg_t)))
        {
            return -EFAULT;
        }
        chng_prt(ioctl_arg.child_pid, ioctl_arg.new_parent_pid);
        break;
    default:
        return -EINVAL;
    }

    return 0;
}

static struct file_operations ioctl_fops =
    {
        .owner = THIS_MODULE,
        .open = my_open,
        .release = my_close,
        .unlocked_ioctl = my_ioctl};

static int __init ioctl_driver_init(void)
{
    int ret;

    if ((ret = alloc_chrdev_region(&ioctl_dev, FIRST_MINOR, MINOR_CNT, "dr_droom")) < 0)
    {
        return ret;
    }

    cdev_init(&ioctl_cdev, &ioctl_fops);

    if ((ret = cdev_add(&ioctl_cdev, ioctl_dev, MINOR_CNT)) < 0)
    {
        unregister_chrdev_region(ioctl_dev, MINOR_CNT);
        return ret;
    }

    if (IS_ERR(ioctl_class = class_create(THIS_MODULE, "ioctl_class")))
    {
        cdev_del(&ioctl_cdev);
        unregister_chrdev_region(ioctl_dev, MINOR_CNT);
        return PTR_ERR(ioctl_class);
    }

    if (IS_ERR(device_create(ioctl_class, NULL, ioctl_dev, NULL, "dr_doom")))
    {
        class_destroy(ioctl_class);
        cdev_del(&ioctl_cdev);
        unregister_chrdev_region(ioctl_dev, MINOR_CNT);
        return PTR_ERR(device_create);
    }

    return 0;
}

static void __exit ioctl_driver_exit(void)
{
    device_destroy(ioctl_class, ioctl_dev);
    class_destroy(ioctl_class);
    cdev_del(&ioctl_cdev);
    unregister_chrdev_region(ioctl_dev, MINOR_CNT);
}

module_init(ioctl_driver_init);
module_exit(ioctl_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("23M0788");
MODULE_DESCRIPTION("dr_doom driver change the parent of a process");
