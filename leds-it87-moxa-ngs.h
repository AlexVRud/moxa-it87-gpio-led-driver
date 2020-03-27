/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef __LEDS_IT87_MOXA_NGS_H
#define __LEDS_IT87_MOXA_NGS_H

enum it87xx_board {
	IT87XX_BOARD_MOXA_V_2201,

	IT87XX_BOARD_UNKNOWN,
	IT87XX_BOARD_NO
};

#define IT87XX_BOARD_MAX_NAME 30

struct it87xx_board_type {
	enum it87xx_board board;
	char *board_name;
};

struct it87xx_board_type_list {
	struct it87xx_board_type board;
	char *model_name;
};

struct it87xx_board_store {
	enum it87xx_board board;
	char name[IT87XX_BOARD_MAX_NAME];
};

/* V Series */
static const struct it87xx_board_type_list it87xx_board_type_list_models[] = {

	{{IT87XX_BOARD_MOXA_V_2201, "Moxa V2201"}, "V2201-E1-T"},
	{{IT87XX_BOARD_MOXA_V_2201, "Moxa V2201"}, "V2201-E1-T-LX"},
	{{IT87XX_BOARD_MOXA_V_2201, "Moxa V2201"}, "V2201-E1-T-W7E"},
	{{IT87XX_BOARD_MOXA_V_2201, "Moxa V2201"}, "V2201-E1-W-T"},
	{{IT87XX_BOARD_MOXA_V_2201, "Moxa V2201"}, "V2201-E2-T"},
	{{IT87XX_BOARD_MOXA_V_2201, "Moxa V2201"}, "V2201-E2-W-T"},
	{{IT87XX_BOARD_MOXA_V_2201, "Moxa V2201"}, "V2201-E4-T"},
	{{IT87XX_BOARD_MOXA_V_2201, "Moxa V2201"}, "V2201-E4-W-T"},
	{{IT87XX_BOARD_MOXA_V_2201, "Moxa V2201"}, "V2201-E4-W-T-LX"},
	{{0}, 0},
};

static const struct it87xx_board_type it87xx_board_unknown[] = {
	{IT87XX_BOARD_UNKNOWN, "Unknown Board"},
};

#define IT87XX_GPIO_DRIVER "gpio-it87"

#endif /* __LEDS_IT87_MOXA_NGS_H */
