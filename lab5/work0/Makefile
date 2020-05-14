obj-m = main.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc blk.c -o blk.out
	gcc nonblk.c -o nonblk.out
	gcc poll.c -o poll.out
	gcc select.c -o selec.out
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
