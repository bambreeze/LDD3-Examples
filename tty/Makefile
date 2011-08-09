PWD := $(shell pwd)
INSTALLDIR = ~/workspace/skyeye/initrd/lib/modules

# Comment/uncomment the following line to disable/enable compiling on ldd6410
SKYEYE = y

ifeq ($(SKYEYE),y)
KERNELDIR = ~/workspace/ldd6410-read-only/linux-2.6.31
CROSS_COMPILE   = arm-linux-
CC      = $(CROSS_COMPILE)gcc
else
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
endif

# Comment/uncomment the following line to disable/enable debugging
#DEBUG = y

# Add your debugging flag (or not) to CFLAGS
ifeq ($(DEBUG),y)
  DEBFLAGS = -O -g -DSCULL_DEBUG # "-O" is needed to expand inlines
else
  DEBFLAGS = -O2
endif

EXTRA_CFLAGS += $(DEBFLAGS) -I..

ifneq ($(KERNELRELEASE),)
# call from kernel build system

obj-m	:= tiny_tty.o tiny_serial.o

else

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif

modules_install:
	mount -o loop ~/workspace/skyeye/initrd.img ~/workspace/skyeye/initrd/
	cp *.ko $(INSTALLDIR)
	umount ~/workspace/skyeye/initrd/

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.* Module.*

depend .depend dep:
	$(CC) $(CFLAGS) -M *.c > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif
