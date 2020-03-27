KRELEASE ?= $(shell uname -r)
KBUILD ?= /lib/modules/$(KRELEASE)/build
DRIVER_PATH := /lib/modules/$(KRELEASE)/kernel/drivers/leds
KOBJECT := leds-it87-moxa-ngs
obj-m := $(KOBJECT).o

modules:
	$(MAKE) -C $(KBUILD) M=$(PWD) modules

install: modules
	/usr/bin/install -m 644 -D $(KOBJECT).ko $(DRIVER_PATH)/$(KOBJECT).ko
	/usr/bin/install -m 644 -D $(KOBJECT).conf /usr/lib/modules-load.d/$(KOBJECT).conf

clean:
	$(MAKE) -C $(KBUILD) M=$(PWD) clean

.PHONY: modules install clean
