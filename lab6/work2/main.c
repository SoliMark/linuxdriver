#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/timer.h>
MODULE_LICENSE("Dual BSD/GPL");

#define SLEEP_TIMEOUT (6*HZ)
#define WAKEUP_TIMEOUT (5*HZ)

static struct timer_list tickfn;
static wait_queue_head_t wait;
static int condition = 0;

/*
static void sample_timeout(unsigned long arg)
{
    wait_queue_head_t *wq = (wait_queue_head_t*)arg;

    printk("wq %p (%s)\n",wq,__func__);
    condition = 1;
    wake_up(wq);
}
*/

static void sample_timeout(struct timer_list *timer){
    wait_queue_head_t *wq = &wait;
    printk("wq %p (%s)\n",wq,__func__);
    condition = 1;
    wake_up(wq);
}

static int sample_init(void)
{
    long val;

    printk("driver loaded: %p \n",&tickfn);
    /* init timer */
    timer_setup(&tickfn,sample_timeout,0);
    tickfn.expires = jiffies + WAKEUP_TIMEOUT;
    add_timer(&tickfn);
    /* init wait queue */
    init_waitqueue_head(&wait);
    condition = 0;
    val = wait_event_timeout(wait,condition,SLEEP_TIMEOUT);

    if(val==0) printk("Time out ocurred,(%s)\n",__func__);

    return 0;
}

static void sample_exit(void)
{
    del_timer_sync(&tickfn);

    printk(KERN_ALERT "driver unload\n");
}

module_init(sample_init);
module_exit(sample_exit);
