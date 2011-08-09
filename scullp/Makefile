PWD := $(shell pwd)
KERNELDIR = /home/bambreeze/workspace/ldd6410-read-only/linux-2.6.31
INSTALLDIR = /home/bambreeze/workspace/skyeye/initrd/lib/modules

CROSS_COMPILE   = arm-linux-
CC      = $(CROSS_COMPILE)gcc

# Comment/uncomment the following line to enable/disable debugging
#DEBUG = y

# Add your debugging flag (or not) to CFLAGS
ifeq ($(DEBUG),y)
  DEBFLAGS = -O -g -DSCULLP_DEBUG # "-O" is needed to expand inlines
else
  DEBFLAGS = -O2
endif

EXTRA_CFLAGS += $(DEBFLAGS) -I$(LDDINC)

TARGET = scullp

# call from kernel build system
ifneq ($(KERNELRELEASE),)

scullp-objs := main.o mmap.o
obj-m	:= scullp.o

else

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) LDDINC=$(PWD) modules

endif

modules_install:
	mount -o loop /home/bambreeze/workspace/skyeye/initrd.img /home/bambreeze/workspace/skyeye/initrd/
	cp scullp.ko $(INSTALLDIR)
	cp scullp_load $(INSTALLDIR)
	umount /home/bambreeze/workspace/skyeye/initrd/

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order Module.symvers

depend .depend dep:
	$(CC) $(CFLAGS) -M *.c > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif
