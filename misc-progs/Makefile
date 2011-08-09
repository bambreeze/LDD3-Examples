PWD := $(shell pwd)
KERNELDIR = /home/bambreeze/workspace/ldd6410-read-only/linux-2.6.31
INSTALLDIR = /home/bambreeze/workspace/skyeye/initrd/lib/modules

CROSS_COMPILE   = arm-linux-
CC      = $(CROSS_COMPILE)gcc

FILES = nbtest load50 mapcmp polltest mapper setlevel setconsole inp outp \
	datasize dataalign netifdebug tree

INCLUDEDIR = $(KERNELDIR)/include
CFLAGS = -O2 -fomit-frame-pointer -Wall -I$(INCLUDEDIR)

all: $(FILES)

modules_install:
	mount -o loop /home/bambreeze/workspace/skyeye/initrd.img /home/bambreeze/workspace/skyeye/initrd/
	cp $(FILES) $(INSTALLDIR)
	umount /home/bambreeze/workspace/skyeye/initrd/

clean:
	rm -f $(FILES) *~ core

