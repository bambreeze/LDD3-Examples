PWD := $(shell pwd)
KERNELDIR = /home/bambreeze/workspace/ldd6410-read-only/linux-2.6.31
INSTALLDIR = /home/bambreeze/workspace/skyeye/initrd/lib/modules

CROSS_COMPILE   = arm-linux-
CC      = $(CROSS_COMPILE)gcc

# Comment/uncomment the following line to disable/enable debugging
#DEBUG = y

# Add your debugging flag (or not) to CFLAGS
ifeq ($(DEBUG),y)
  DEBFLAGS = -O -g -DSHORT_DEBUG # "-O" is needed to expand inlines
else
  DEBFLAGS = -O2
endif

EXTRA_CFLAGS += $(DEBFLAGS)
EXTRA_CFLAGS += -I..

# call from kernel build system
ifneq ($(KERNELRELEASE),)

obj-m	:= short.o

else

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif

#modules_tests: short_tests.o
#	$(CC) -o short_tests short_tests.o 

modules_install:
	mount -o loop /home/bambreeze/workspace/skyeye/initrd.img /home/bambreeze/workspace/skyeye/initrd/
	cp short.ko $(INSTALLDIR)
#	cp short_tests $(INSTALLDIR)
	cp short_load $(INSTALLDIR)
	umount /home/bambreeze/workspace/skyeye/initrd/

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions Module.* modules.*

depend .depend dep:
	$(CC) $(CFLAGS) -M *.c > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif

.PHONY: modules modules_tests modules_install clean
