/* -*- mode: c; c-basic-offset: 2; indent-tabs-mode: nil; -*-
 *
 * Using the C-API of this library.
 *
 */
#include "led-matrix-c.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void swastique(struct LedCanvas *canvas, uint8_t r, uint8_t g, uint8_t b) {
	// void draw_line(struct LedCanvas *c, int x0, int y0, int x1, int y1, uint8_t r, uint8_t g, uint8_t b);
	
	int xleft = 64/2 - 10;
	int yleft = 32/2;
	int xright = 64/2 + 10;
	int yright=  32/2;
	int xtop = 64/2;
	int ytop = 32/2 - 10;
	int xbot = 64/2;
	int ybot = 32/2 + 10;

	// Horizontal primary
	draw_line(canvas, xleft, yleft, xright, yright, r, g, b);
	draw_line(canvas, xleft, yleft+1, xright, yright+1, r, g, b); 
	draw_line(canvas, xleft, yleft-1, xright, yright-1, r, g, b); 

	// Vertical primary
	draw_line(canvas, xtop, ytop, xbot, ybot, r, g, b);
	draw_line(canvas, xtop+1, ytop, xbot+1, ybot, r, g, b); 
	draw_line(canvas, xtop-1, ytop, xbot-1, ybot, r, g, b); 

	// Top squiggle
	draw_line(canvas, xtop, ytop,   xtop+10, ytop, r, g, b);
	draw_line(canvas, xtop, ytop+1, xtop+10, ytop+1, r, g, b);
	draw_line(canvas, xtop, ytop+2, xtop+10, ytop+2, r, g, b);

	// Bottom squiggle
	draw_line(canvas, xbot, ybot,   xbot-10, ybot, r, g, b);
	draw_line(canvas, xbot, ybot-1, xbot-10, ybot-1, r, g, b);
	draw_line(canvas, xbot, ybot-2, xbot-10, ybot-2, r, g, b);

	// Left squiggle
	draw_line(canvas, xleft,   yleft,   xleft, yleft-10, r, g, b);
	draw_line(canvas, xleft+1, yleft, xleft+1, yleft-10, r, g, b);
	draw_line(canvas, xleft+2, yleft, xleft+2, yleft-10, r, g, b);

	// Right squiggle
	draw_line(canvas, xright, yright, xright, yright+10, r, g, b);
	draw_line(canvas, xright-1, yright, xright-1, yright+10, r, g, b);
	draw_line(canvas, xright-2, yright, xright-2, yright+10, r, g, b);

}

int main(int argc, char **argv) {
	struct RGBLedMatrix *matrix;
	struct LedCanvas *offscreen_canvas;
	int width, height;

	/* This supports all the led commandline options. Try --led-help */
	matrix = led_matrix_create_single(32, 64, "adafruit-hat");
	if (matrix == NULL)
		return 1;

	/* Let's do an example with double-buffering. We create one extra
	 * buffer onto which we draw, which is then swapped on each refresh.
	 * This is typically a good aproach for animations and such.
	 */
	offscreen_canvas = led_matrix_create_offscreen_canvas(matrix);

	led_canvas_get_size(offscreen_canvas, &width, &height);

	fprintf(stderr, "Size: %dx%d.\n", width, height);

	int xmin = 0;
	int xmax = 63;
	int ymin = 0;
	int ymax = 31;

	for (int i=0; i<16; i++) {
		printf("x=[%d,%d] y=[%d,%d]\n", xmin,xmax, ymin,ymax);
		for (int x=xmin; x<xmax; x++) {
			led_canvas_set_pixel(offscreen_canvas, x, ymin, 255, 255, 255);
			offscreen_canvas = led_matrix_swap_on_vsync(matrix, offscreen_canvas);  
		}
		xmin++;

		for (int y=ymin; y<ymax; y++) {
			led_canvas_set_pixel(offscreen_canvas, xmax, y, 255, 255, 255);
			offscreen_canvas = led_matrix_swap_on_vsync(matrix, offscreen_canvas);  
		}
		ymin++;

		for (int x=xmax; x>xmin; x--) {
			led_canvas_set_pixel(offscreen_canvas, x, ymax, 255, 255, 255);
			offscreen_canvas = led_matrix_swap_on_vsync(matrix, offscreen_canvas);  
		}
		xmax--;

		for (int y=ymax; y>ymin; y--) {
			led_canvas_set_pixel(offscreen_canvas, xmin, y, 255, 255, 255);
			offscreen_canvas = led_matrix_swap_on_vsync(matrix, offscreen_canvas);  
		}
		ymax--;
	}
	while (1) {
		for (int y=0; y<32; y++) {
			for (int x=0; x<64; x++) {
				led_canvas_set_pixel(offscreen_canvas, x, y, 255, 255, 255);
			}
		}
		swastique(offscreen_canvas, 255, 0, 0);
		offscreen_canvas = led_matrix_swap_on_vsync(matrix, offscreen_canvas);  
		usleep(500000);

		for (int y=0; y<32; y++) {
			for (int x=0; x<64; x++) {
				led_canvas_set_pixel(offscreen_canvas, x, y, 255, 0, 0);
			}
		}
		swastique(offscreen_canvas, 255, 255, 255); 
		offscreen_canvas = led_matrix_swap_on_vsync(matrix, offscreen_canvas);  
		usleep(500000);
	}

	/*
	while (1) {
		for (int i=0; i<10; i++) {
			printf("line %d\n", i);
			draw_line(offscreen_canvas, 0, 0, i, i*2, 255, 0, 255);
			offscreen_canvas = led_matrix_swap_on_vsync(matrix, offscreen_canvas);  
			usleep(5000000);
		}
	}
	*/

	/*
	 * Make sure to always call led_matrix_delete() in the end to reset the
	 * display. Installing signal handlers for defined exit is a good idea.
	 */
	led_matrix_delete(matrix);

	return 0;
}
