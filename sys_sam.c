// SPDX-License-Identifier: GPL


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/buffer_read.h>
#include <uapi/asm-generic/errno-base.h>
#include <linux/file.h>

/* 
 * Writes 'data' upto size 'size' starting from 'offset' to a file descriptor 'file'
 * Returns the number of bytes written
 */

int file_write(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size) 
{
    mm_segment_t oldfs;
    int ret;

    oldfs = get_fs();
    set_fs(get_ds());

    ret = vfs_write(file, data, size, &offset);

    set_fs(oldfs);
    return ret;
}

/* 
 * Traverses through the task_list and finds the corresponding task_struct
 * prints the members in kernel log and also put them in a file
 * in /home/maalik/code/ dir
 * 
 * Returns 0 for success, otherwise errno
 */

asmlinkage long sys_sh_task_info(pid_t pid_no, char *f_name)
{
	printk(KERN_INFO "& HERE WE BEGIN ------->>>>>\n");
        struct task_struct *task_list;
	int flag=0;
        for_each_process(task_list) {
		if(task_list->pid == pid_no){
                pr_info("Name = %s\n PID:     = %d\n PPID:    = %d\n  State:   = %ld\n Priority = %ld\n CPU no   = %ld\n", task_list->comm, task_list->pid, task_list->parent->pid, (long)task_list->state, (long) task_list->prio, (long) task_list->on_cpu);
                flag=1;
		} }
		if(flag==0){
		pr_info(" No such PID exist, try again u fool...");
	char *f_path="/home/archit/code/";
	strcat(f_path,f_name);
	printk("This is F_PATH %s\n",f_path);
	char data[100000];
	sprintf(data,"Name     = %s\n PID:     = %d\n PPID:    = %d\n  State:   = %ld\n Priority = %ld\n CPU no   = %ld\n", task_list->comm, task_list->pid, task_list->parent->pid, (long)task_list->state, (long) task_list->prio, (long) task_list->on_cpu);
    struct file *filp = NULL;
    mm_segment_t oldfs;
    int err = 0;

    oldfs = get_fs();
    set_fs(get_ds());
    filp = filp_open(f_path,O_CREAT, 0644);
    set_fs(oldfs);

    file_write(filp,0,data,strlen(data));	
	filp_close(filp, NULL);

	printk(KERN_INFO "<<<<<------ MAGIC ENDS HERE !!!");
	return 0;
}
}
