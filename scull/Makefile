PWD := $(shell pwd)
KERNELDIR = /home/bambreeze/workspace/ldd6410-read-only/linux-2.6.31
INSTALLDIR = /home/bambreeze/workspace/skyeye/initrd/lib/modules

CROSS_COMPILE   = arm-linux-
CC      = $(CROSS_COMPILE)gcc

# Comment/uncomment the following line to disable/enable debugging
DEBUG = y

# Add your debugging flag (or not) to CFLAGS
ifeq ($(DEBUG),y)
  DEBFLAGS = -O -g -DSCULL_DEBUG # "-O" is needed to expand inlines
else
  DEBFLAGS = -O2
endif

EXTRA_CFLAGS += $(DEBFLAGS)

# call from kernel build system
ifneq ($(KERNELRELEASE),)

scull-objs := scull_basic.o scull_pipe.o
obj-m	:= scull.o

else

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif

modules_tests: scull_tests.o
	$(CC) -o scull_tests scull_tests.o 

modules_install:
	mount -o loop /home/bambreeze/workspace/skyeye/initrd.img /home/bambreeze/workspace/skyeye/initrd/
	cp scull.ko $(INSTALLDIR)
	cp scull_tests $(INSTALLDIR)
	cp scull_load $(INSTALLDIR)
	umount /home/bambreeze/workspace/skyeye/initrd/

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions Module.markers modules.order Module.symvers scull_tests

depend .depend dep:
	$(CC) $(CFLAGS) -M *.c > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif

.PHONY: modules modules_tests modules_install clean
