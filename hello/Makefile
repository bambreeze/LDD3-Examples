# Comment/uncomment the following line to enable/disable for skyeye
SKYEYE = y

PWD := $(shell pwd)
ifeq ($(SKYEYE),y)
    KERNELDIR = ~/workspace/ldd6410-read-only/linux-2.6.31
    INSTALLDIR = ~/workspace/skyeye/initrd/lib/modules

    CROSS_COMPILE   = arm-linux-
    CC      = $(CROSS_COMPILE)gcc
else
    KERNELDIR ?= /lib/modules/$(shell uname -r)/build
endif

obj-m := hello.o

.PHONY: modules modules_install clean

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	cp hello.ko $(INSTALLDIR)

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order Module.symvers
