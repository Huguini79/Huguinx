module main

#flag -I/libc/
#include "stdio.h"

fn C.huguinx_print(str &char);

fn hola_desde_vlang() {
	C.huguinx_print(c"HOLA DESDE VLANG, ESTO NO ES C");
}
