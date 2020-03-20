#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/sched/task.h>

MODULE_LICENSE("Dual BSD/GPL");

static int getpid_init(void)
{
    struct task_struct *task,*p;
    struct list_head *ps;
    printk("begin.\n");
    task=&init_task;
    list_for_each(ps,&task->tasks)
    {
        p=list_entry(ps,struct task_struct,tasks);
        printk("%d\t%s\n",p->pid,p->comm);
    }
    return 0;

}

static void getpid_exit(void) 
{
	printk(KERN_ALERT "driver unloaded\n");
}

module_init(getpid_init);
module_exit(getpid_exit);

