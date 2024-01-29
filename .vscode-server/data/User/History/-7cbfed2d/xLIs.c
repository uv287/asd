#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

int pid = 1;
module_param(pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)