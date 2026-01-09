/*
 * Copyright (c) 2026 ordinaryrice
 *
 * Released under the MIT license
 * https://opensource.org/licenses/mit-license.php
 */

#include "pico/stdlib.h"
#include "common.h"
#include "gpio_buttons.h"

void button_setup(uint gpio)
{
	gpio_init(gpio);
	gpio_set_dir(gpio, GPIO_IN);
	gpio_pull_up(gpio);
}

void buttons_init()
{
	button_setup(BTN_BACK_PIN);
	button_setup(BTN_PLAY_PAUSE_PIN);
	button_setup(BTN_NEXT_PIN);
	button_setup(BTN_STOP_PIN);
	button_setup(BTN_VOL_DOWN_PIN);
	button_setup(BTN_VOL_UP_PIN);
}

uint8_t buttons_get()
{
	uint8_t button = 0;
	if (!gpio_get(BTN_VOL_DOWN_PIN))        button = 5;
	else if (!gpio_get(BTN_VOL_UP_PIN))     button = 6;
	else if (!gpio_get(BTN_BACK_PIN))       button = 1;
	else if (!gpio_get(BTN_PLAY_PAUSE_PIN)) button = 2;
	else if (!gpio_get(BTN_NEXT_PIN))       button = 3;
	else if (!gpio_get(BTN_STOP_PIN))       button = 4;
	return button;
}



