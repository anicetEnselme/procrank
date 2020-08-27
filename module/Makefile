obj-m := procrank.o
KDIR := /home/enselme/git/kernels/linux-5.0.9      # Your kernel path

default:
	make -C $(KDIR) M=$(shell pwd) modules

clean:
	make -C $(KDIR) M=$(PWD) clean


