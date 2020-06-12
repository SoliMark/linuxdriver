#include <linux/module.h>
#include <linux/init.h>
//#include <sys/time.h>
#include <linux/time.h>

MODULE_LICENSE("Dual BSD/GPL");


static int devone_init(void)
{
    printk(KERN_ALERT "driver loaded\n");

    ktime_t ktm;
    struct timespec64 time64;
    struct tm time_tm;
    ktm = ktime_get_real();
    time64 = ktime_to_timespec64(ktm);
    time64_to_tm(time64.tv_sec,0,&time_tm);
    printk("Current UTC:%lld",ktm);
    printk("%lld convert:",ktm);
    printk("%ld/%d/%d %d:%d:%d \n" ,time_tm.tm_year+1900,time_tm.tm_mon+1,time_tm.tm_mday,time_tm.tm_hour,time_tm.tm_min,time_tm.tm_sec);
    return 0;
}

static void devone_exit(void)
{
    printk(KERN_ALERT "driver unloaded\n");
}

module_init(devone_init);
module_exit(devone_exit);
