// Author: Huguini79
// STDIO implementation
#ifndef STDIO_H
#define STDIO_H

#include "drivers/vga/vga.h"

#include "libc/string.h"

static void huguinx_print(const char* str) {
	// WE GET THE SIZE OF THE STR
	size_t len = strlen(str);

	// WE WRITE ALL THE STR CHARACTER BY CHARACTER
	for (int i = 0; i < len; i++) {
		huguinx_perfectchar(str[i], 15);
	}

}

#endif
