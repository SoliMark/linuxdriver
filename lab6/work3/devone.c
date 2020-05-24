//
// devone.c
//
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
//#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include <linux/wait.h>

MODULE_LICENSE("Dual BSD/GPL");

#define SLEEP_TIMEOUT (10*HZ)

static int devone_devs = 1;
static int devone_major = 0;   // dynamic allocation
static struct cdev devone_cdev;  

int condition =0;
wait_queue_head_t wait;

EXPORT_SYMBOL(condition);
EXPORT_SYMBOL(wait);
/*
void sleep_on(wait_queue_head_t *q){
    unsigned long flags;
    wait_queue_entry_t wait;

    init_waitqueue_entry(&wait,current);
    __set_current_state(TASK_UNINTERRUPTIBLE);

    spin_lock_irqsave(&q->lock,flags);
    __add_wait_queue(q,&wait);
    spin_unlock(&q->lock);
    schedule();
    spin_lock_irq(&q->lock);
    __remove_wait_queue(q,&wait);
    spin_unlock_irqrestore(&q->lock,flags);
}    
*/

ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    long cmp;
	int i;
	unsigned char val = 0xff;
	int retval;
    
    init_waitqueue_head(&wait);
    condition=0;

    cmp = wait_event_timeout(wait,condition,SLEEP_TIMEOUT);

    if(cmp==0) printk("Time out ocurred,(%s)\n",__func__);

	printk("Wakeup! (%s)\n", __func__);

	for (i = 0 ; i < count ; i++) {
		if (copy_to_user(&buf[i], &val, 1)) {
			retval = -EFAULT;
			goto out;
		}
	}

	retval = count;
out:
	return (retval);
}

struct file_operations devone_fops = {
	.read = devone_read,
};

static int devone_init(void)
{
	dev_t dev = MKDEV(devone_major, 0);
	int ret;
	int major;
	int err;

	ret = alloc_chrdev_region(&dev, 0, devone_devs, "devone");
	if (ret < 0)
		return ret;
	devone_major = major = MAJOR(dev);

	cdev_init(&devone_cdev, &devone_fops);
	devone_cdev.owner = THIS_MODULE;
	devone_cdev.ops = &devone_fops;
	err = cdev_add(&devone_cdev, MKDEV(devone_major, 0), 1);
	if (err) 
		return err;

	printk(KERN_ALERT "devone driver(major %d) installed.\n", major);

	return 0;
}

static void devone_exit(void)
{
	dev_t dev = MKDEV(devone_major, 0);

	printk(KERN_ALERT "devone driver removed.\n");

	cdev_del(&devone_cdev);

	unregister_chrdev_region(dev, devone_devs);

}

module_init(devone_init);
module_exit(devone_exit);

