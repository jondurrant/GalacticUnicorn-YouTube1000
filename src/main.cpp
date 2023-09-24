/***
 * main.cpp - Celebrating 1000 Subscribers
 * With PiMoroni Galactic Unicorn
 * Jon Durrant
 * 24-Sep-2023
 *
 *
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include <cstring>


#include "libraries/pico_graphics/pico_graphics.hpp"
#include "galactic_unicorn.hpp"
#include "YT1000.h"

using namespace pimoroni;

PicoGraphics_PenRGB888 graphics(53, 11, nullptr);
GalacticUnicorn galactic_unicorn;


std::string message = "Thank You";


void celebrate(){
	graphics.set_pen(0, 0, 0);
	graphics.clear();

	for (int y = 0; y < 12; y++) {
		for (int x = 0; x < 53; x++) {
			int i = x + (y * 53);
			uint32_t c = YT1000[i];
			uint8_t r = (c & 0x00ff0000) >> 16;
			uint8_t g = (c & 0x0000ff00) >> 8;
			uint8_t b = (c & 0x000000ff);
			graphics.set_pen(r, g, b);
			graphics.pixel(Point(x, y));
		}
	}
	galactic_unicorn.update(&graphics);
}

void thanks(){
	graphics.set_pen(0, 0, 0);
	graphics.clear();

	graphics.set_pen(0x50, 0x50, 0xff);
	graphics.text(message, Point(2, 2), -1, 0.55);

	galactic_unicorn.update(&graphics);
}

int main(void) {
	uint32_t now, last = 0;
	bool doCel = true;

	stdio_init_all();
	galactic_unicorn.init();

	sleep_ms(2000);
	printf("GO\n");

	for (;;) {
		if (galactic_unicorn.is_pressed(
				galactic_unicorn.SWITCH_BRIGHTNESS_UP)) {
			galactic_unicorn.adjust_brightness(+0.01);
		}
		if (galactic_unicorn.is_pressed(
				galactic_unicorn.SWITCH_BRIGHTNESS_DOWN)) {
			galactic_unicorn.adjust_brightness(-0.01);
		}

		now = to_ms_since_boot(get_absolute_time ());
		if((now - last) > 5000){
			if (doCel){
				celebrate();
			} else {
				thanks();
			}
			last = now;
			doCel = !doCel;
		}


	}

	return 0;
}
