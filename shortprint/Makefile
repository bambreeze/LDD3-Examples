PWD := $(shell pwd)
KERNELDIR = /home/bambreeze/workspace/ldd6410-read-only/linux-2.6.31
INSTALLDIR = /home/bambreeze/workspace/skyeye/initrd/lib/modules

CROSS_COMPILE   = arm-linux-
CC      = $(CROSS_COMPILE)gcc

# Comment/uncomment the following line to disable/enable debugging
#DEBUG = y

EXTRA_CFLAGS += -O2 -I..

# call from kernel build system
ifneq ($(KERNELRELEASE),)

obj-m	:= shortprint.o

else

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif

modules_install:
	mount -o loop /home/bambreeze/workspace/skyeye/initrd.img /home/bambreeze/workspace/skyeye/initrd/
	cp shortprint.ko $(INSTALLDIR)
	cp shortprint_load $(INSTALLDIR)
	umount /home/bambreeze/workspace/skyeye/initrd/

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions Module.* modules.*

depend .depend dep:
	$(CC) $(CFLAGS) -M *.c > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif

.PHONY: modules modules_tests modules_install clean
