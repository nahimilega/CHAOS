#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/errno.h>
#include <linux/fs.h>
// #include <linux/buffer_read.h>
#include <uapi/asm-generic/errno-base.h>
#include <linux/file.h>


asmlinkage long sys_sh_task_info(long pid_no, char *f_name)
{	
	pid_no=1;
	f_name="lol.txt";
	printk(KERN_INFO "& HERE WE BEGIN ------->>>>>\n");
        struct task_struct *task_list;

        for_each_process(task_list) {
		if((long)task_pid_nr(task_list) == pid_no){
                pr_info("Name = %s\n PID:     = %d\n PPID:    = %d\n  State:   = %ld\n Priority = %ld\n CPU no   = %ld\n", task_list->comm, task_list->pid, task_list->parent->pid, (long)task_list->state, (long) task_list->prio, (long) task_list->on_cpu);
                }
		else{
		pr_info(" No such PID exist, try again u fool...");
}
        }
	char data[100000];
	sprintf(data,"Name     = %s\n PID:     = %d\n PPID:    = %d\n  State:   = %ld\n Priority = %ld\n CPU no   = %ld\n", task_list->comm, task_list->pid, task_list->parent->pid, (long)task_list->state, (long) task_list->prio, (long) task_list->on_cpu);

	char *f_path = "/home/maalik/code/";
	strcat(f_path,f_name);
/////////////////////////////////////////////////  open the damn file
	struct file *filp = NULL;
	mm_segment_t oldfs;
        int err = 0;
        oldfs = get_fs();
        set_fs(get_ds());
        filp = filp_open(f_path, O_CREAT|O_RDWR|O_APPEND,0644);
        set_fs(oldfs);
        if (IS_ERR(filp)) {
        err = PTR_ERR(filp);
        return -10;
////////////////////////////////////////////////  write to the file    
    	int ret;
    	set_fs(get_ds());
    	ret = vfs_write(f_name, data, strlen(data), 0);
    	set_fs(oldfs);
////////////////////////////////////////////////  close the file
	filp_close(f_name, NULL);


}	
	
	

	
	
	printk(KERN_INFO "<<<<<------ MAGIC ENDS HERE !!!");
	return 0;
}

MODULE_LICENSE("GPL");
