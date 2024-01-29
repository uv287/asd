#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("23M0788");
MODULE_DESCRIPTION("This programme To findout the physical address of the given pid");

int pid = 1;
module_param(pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

unsigned long va;
module_param(va, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

static int __init virtual_to_physical(void)
{
   struct task_struct *process;
   struct pid *pid_struct = find_get_pid(pid);
   process = pid_task(pid_struct, PIDTYPE_PID);

   unsigned long pa =0;

   struct mm_struct *mm;
   mm = process -> mm;

   down_read(&mm->mmap_lock);

   struct vm_area_struct *vm;

   vm = find_vma(mm, va);

   if (vma == NULL)
   {
      printk("Virtual adddress does not belong to this process\n");
      return 0;
   } 

   pa = virt_to_phys((void *)va);

   printk("Physical address is %lu\n",pa);

   up_read(&mm->mmap_lock);

   return 0;
}

static void __exit add_conver_exit(void)
{
   printk("Exiting the lkm3 module\n");
}

module_init(virtual_to_physical);
module_exit(add_conver_exit);