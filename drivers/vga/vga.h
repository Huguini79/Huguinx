// Author: Huguini79
// VGA Driver for text mode 80x25

#ifndef VGA_H
#define VGA_H

// 80x25
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#include <stdint.h>
#include <stddef.h>

// VGA Structure
struct vga {
	uint16_t* video_mem; // VGA video mem (0xB8000)
	uint16_t row; // VGA row (y)
	uint16_t col; // VGA col (x)
};

// VGA functions
void huguinx_init_screen(); // WE INIT THE VGA SCREEN
uint16_t huguinx_create_char(char c, char color); // WE CREATE A CHARACTER
void huguinx_xychar(int x, int y, char c, char color); // WE SET A CHARACTER WITH A SPECIFIC VGA COLOR
void huguinx_perfectchar(char c, char color); // WE SET AUTOMATICALLY A CHARACTER IN THE NEXT X AND Y POSITION USING THE huguinx_xychar FUNCTION
void huguinx_clear(); // WE CLEAR THE SCREEN
void huguinx_logs(const char* str);

#endif
