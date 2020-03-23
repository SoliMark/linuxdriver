obj-m :=driver.o

KERNEL_DIR = /usr/src/linux-headers-$(shell uname -r)

all:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules
	gcc usertest.c -o usertest.out
clean:
	rm -rf *.o *.ko *.mod *.symvers *.order *~ *.mod.c *.out .driver.*
