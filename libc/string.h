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

#endif
