#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/sched.h>

int pid = 1;
module_param(pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

unsigned long va;
module_param(va, unsigned long, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

static int __init virtual_to_physical(void)
{
   struct task_struct *process;
   struct pid *pid_struct = find_get_pid(pid);
   process = pid_task(pid_struct, PIDTYPE_PID);

   struct mm_struct *mm;
   mm = process -> mm;

   down_read(&mm->mmap_sem);

   struct vm_area_struct *vm;



   up_read(&mm->mmap_sem);


}

static void __exit add_conver_exit(void)
{

}

module_init(virtual_to_physical);
module_exit(add_conver_exit);