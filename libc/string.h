// Author: Huguini79
// STRING IMPLEMENTATION
#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

static inline int strlen(const char* str) {
	size_t len = 0;

	while (str[len]) {
		len++;
	}

	return len;

}

static inline int strnlen(const char* ptr, int max) {
    int i = 0;

    for (int i = 0; i < max; i++) {
        if (ptr[i] == 0) {
            break;
        }
    }

    return i;
    
}

static void* memset(void *ptr, int c, size_t size) {
	char* c_ptr = (char*) ptr;
	for(int i = 0; i < size; i++) {
		c_ptr[i] = (char) c;
	}
	
	return ptr;
	
}

static int strncmp(const char* str1, const char* str2, int n)
{
    unsigned char u1, u2;

    while(n-- > 0)
    {
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;
        if (u1 != u2)
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }

    return 0;
}

static inline bool isdigit(char c) {
    return c >= 48 && c <= 57;
}

static inline int tonumericdigit(char c) {
    return c - 48;
}

static int memcmp(void* s1, void* s2, int count) {
    char* c1 = s1;
    char* c2 = s2;

    while (count-- > 0) {
        if(*c1++ != *c2++) {
            return c1[-1] < c2[-1] ? -1 : 1;
        }
    }

    return 0;

}

#endif
