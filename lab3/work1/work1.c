#include <linux/kernel.h>
#include <asm/current.h>
/*
#define SCHED_NORMAL            0
#define SCHED_FIFO              1
#define SCHED_RR                2
#define SCHED_BATCH             3
// SCHED_ISO: reserved but not implemented yet 
#define SCHED_IDLE              5
#define SCHED_DEADLINE          6
*/
asmlinkage long sys_work1(void){
	printk("pid is %d\n",current->pid);
	char policy[7][20]{"SCHED_NORMAL","SCHED_FIFO","SCHED_BATCH","reserved","SCHED_IDLE","SCHED_DEADLINE"};
	printk("schedule policy is %s",policy[current->policy]);
}
