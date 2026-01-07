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

static void* memset(void *ptr, int c, size_t size) {
	char* c_ptr = (char*) ptr;
	for(int i = 0; i < size; i++) {
		c_ptr[i] = (char) c;
	}
	
	return ptr;
	
}



#endif
