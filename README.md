# moxa-it87-gpio-led-driver

## Install required packages

make, linux-headers-\<KERNEL_RELEASE>

```bash
apt install --no-install-recommends -qqy make
apt install --no-install-recommends -qqy linux-headers-$(uname -r)
```

## Build package

1. Run `make` to build kernel module
2. Once build successful, `leds_it87_moxa_ngs.ko` could be found under current directory

## Troubleshooting for CentOS 8

1. SELinux is preventing `/usr/lib/systemd/systemd-modules-load` from `module_request()` access on the system
2. You can generate a local policy module to allow this access

```bash
ausearch -c 'systemd-modules' --raw | audit2allow -M leds_it87_moxa_ngs
semodule -i leds_it87_moxa_ngs.pp
```
