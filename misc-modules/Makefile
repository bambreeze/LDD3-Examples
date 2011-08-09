PWD := $(shell pwd)
KERNELDIR = /home/bambreeze/workspace/ldd6410-read-only/linux-2.6.31
INSTALLDIR = /home/bambreeze/workspace/skyeye/initrd/lib/modules

CROSS_COMPILE   = arm-linux-
CC      = $(CROSS_COMPILE)gcc

# call from kernel build system
ifneq ($(KERNELRELEASE),)
	obj-m := hello.o hellop.o seq.o jit.o jiq.o sleepy.o complete.o \
			 silly.o faulty.o kdatasize.o kdataalign.o
else
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif

#modules_tests: misc_modules_tests.o
#	$(CC) -o misc_modules_tests misc_modules_tests.o 

modules_install:
	mount -o loop /home/bambreeze/workspace/skyeye/initrd.img /home/bambreeze/workspace/skyeye/initrd/
	cp *.ko $(INSTALLDIR)
#	cp misc_modules_tests $(INSTALLDIR)
	umount /home/bambreeze/workspace/skyeye/initrd/

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions Module.markers modules.order Module.symvers \
	misc_modules_tests

.PHONY: modules modules_tests modules_install clean
