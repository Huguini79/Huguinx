// Author: Huguini79
// STRING IMPLEMENTATION
#ifndef STRING_H
#define STRING_H

static inline int strlen(const char* str) {
	size_t len = 0;

	while (str[len]) {
		len++;
	}

	return len;

}

#endif
