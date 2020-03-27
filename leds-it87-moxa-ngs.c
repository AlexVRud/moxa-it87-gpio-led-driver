// SPDX-License-Identifier: GPL-2.0-only
/*
 *  leds-it87.c - LED control with GPIOs for IT87XX Super I/O chips
 *  Copyright (C) 2020 Moxa, Inc.
 *  Remus Wu <remusty.wu@moxa.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include "leds-it87-moxa-ngs.h"

#include <linux/dmi.h>
#include <linux/errno.h>
#include <linux/leds.h>
#include <linux/module.h>
#include <linux/platform_device.h>

/************************************************
 * Database
 ************************************************/

#define IT87XX_GPIO_LED(_board_color_function, _gpio, _active_low,	\
			_default_state)					\
{									\
	.name = _board_color_function,					\
	.gpio = _gpio,							\
	.active_low = _active_low,					\
	.default_state = _default_state,				\
}

#define IT87XX_GPIO_LED_TRIGGER(_board_color_function, _gpio, _active_low, \
				_default_trigger)			   \
{									   \
	.name = _board_color_function,					   \
	.gpio = _gpio,							   \
	.active_low = _active_low,					   \
	.default_state = LEDS_GPIO_DEFSTATE_OFF,			   \
	.default_trigger = _default_trigger,                               \
}

/* V Series */
static struct gpio_led it87xx_leds_moxa_v_2201[] = {
	IT87XX_GPIO_LED("V2201:GREEN:PRG1", 298, 1, LEDS_GPIO_DEFSTATE_OFF),
	IT87XX_GPIO_LED("V2201:GREEN:PRG2", 299, 1, LEDS_GPIO_DEFSTATE_OFF),
	IT87XX_GPIO_LED("V2201:RED:PRG3", 303, 1, LEDS_GPIO_DEFSTATE_OFF),
};

/************************************************
 * Initial
 ************************************************/

static struct gpio_led_platform_data it87xx_leds_pdata;
static void it87xx_leds_device_pdata_release(struct device *dev)
{
	/* Needed to silence this message:
	 * Device 'xxx' does not have a release() function, it is broken and
	 * must be fixed
	 */
}

static struct platform_device it87xx_leds_dev = {
	.name = "leds-gpio",
	.id = -1,
	.dev = {
		.release = it87xx_leds_device_pdata_release,
		.platform_data = &it87xx_leds_pdata,
	}
};

static struct platform_device *it87xx_leds_devs[] = {
	&it87xx_leds_dev,
};

#define it87xx_set_pdata(dev_leds)					\
	do {								\
		it87xx_leds_pdata.leds = dev_leds;			\
		it87xx_leds_pdata.num_leds = ARRAY_SIZE(dev_leds);	\
	} while (0)

static __init const struct it87xx_board_type *it87xx_board_find(void)
{
	const struct it87xx_board_type_list *device;
	const char *model;

	model = dmi_get_system_info(DMI_BOARD_NAME);
	pr_debug("model = %s\n", model);
	for (device = it87xx_board_type_list_models; device->model_name;
	     device++) {
		pr_debug("device->model_name = %s\n", device->model_name);
		if (!strcmp(model, device->model_name)) {
			pr_info("Found board: %s\n", device->model_name);
			return &device->board;
		}
	}

	return it87xx_board_unknown;
}

static int __init it87xx_leds_init(void)
{
	int ret;
	const struct it87xx_board_type *device;

	ret = request_module(IT87XX_GPIO_DRIVER);

	if (ret)
		return ret;

	device = it87xx_board_find();

	if (device->board == IT87XX_BOARD_UNKNOWN)
		return -ENODEV;

	switch (device->board) {
	case IT87XX_BOARD_MOXA_V_2201:
		it87xx_set_pdata(it87xx_leds_moxa_v_2201);
		break;
	default:
		return -ENODEV;
	}

	return platform_add_devices(it87xx_leds_devs,
				    ARRAY_SIZE(it87xx_leds_devs));
}

static void __exit it87xx_leds_exit(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(it87xx_leds_devs); i++)
		platform_device_unregister(it87xx_leds_devs[i]);
}

module_init(it87xx_leds_init);
module_exit(it87xx_leds_exit);

MODULE_AUTHOR("Remus Wu <remusty.wu@moxa.com>");
MODULE_DESCRIPTION("LED driver for GPIO IT87xx Super I/O chips");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:leds-it87-moxa-ngs");
