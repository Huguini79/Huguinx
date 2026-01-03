// Author: Huguini79
// VGA driver
#include "vga.h"

#include <stdint.h>
#include <stddef.h>

struct vga* vga;

void huguinx_init_screen() {
	// WE INIT THE SCREEN
	vga->video_mem = (uint16_t*)(0xB8000); // 0xB8000 address

	// WE SET THE X AND Y POSITION TO 0
	huguinx_clear();

}

uint16_t huguinx_create_char(char c, char color) {
	// WE CREATE A CHARACTER TO PUT IT IN THE VGA video mem
	return (color << 8) | c;
}

void huguinx_xychar(int x, int y, char c, char color) {
	// WE PUT A CHARACTER IN THE VGA video mem
	vga->video_mem[(y * VGA_WIDTH) + x] = huguinx_create_char(c, color);

}

void huguinx_perfectchar(char c, char color) {
	if (c == '\n') {
		// WE INCREMENT THE Y POSITION AND SET THE X POSITION TO 0
		vga->row += 1;
		vga->col = 0;
	}

	// WE PUT THE CHARACTER
	huguinx_xychar(vga->col, vga->row, c, color);

	// WE INCREMENT THE X POSITION TO SIMULATE WRITING
	vga->col += 1;

	// WE COMPARE THE X AND Y POSITIONS WITH THE VGA POSITIONS

	// X POSITION IS BIGGER THAN VGA_WIDTH POSITION
	if (vga->col >= VGA_WIDTH) {
		// WE INCREMENT THE Y POSITION AND WE SET THE X POSITION TO 0
		vga->row += 1;
		vga->col = 0;
	}

	// Y POSITION IS BIGGER THAN VGA_HEIGHT POSITION
	if (vga->row >= VGA_HEIGHT) {
		// WE CLEAR THE SCREEN
		huguinx_clear();
	}

}

void huguinx_clear() {
	// WE SET X AND Y POSITIONS TO 0
	vga->row = 0;
	vga->col = 0;

	// WE CREATE A LOOP TO WRITE SPACES WITH NO COLOR IN ALL THE SCREEN
	for (int y = 0; y < VGA_HEIGHT; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			huguinx_xychar(x, y, ' ', 0);
		}
	}

}

