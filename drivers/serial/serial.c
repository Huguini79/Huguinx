/* Author: Huguini79 */
/* Serial Ports Driver implementation */

#include "serial.h"
#include "drivers/io/io.h"
#include "drivers/vga/vga.h"

#include "libc/string.h"
#include "libc/stdio.h"
#include "libc/stdlib.h"

int init_serial() {
	huguinx_print("[ OK ] SERIAL PORTS DRIVER\n");
	
	outb(COM1 + 1, 0x00); /* Disable interrupts */
	outb(COM1 + 3, 0x80); /* ENABLE DLAB (set baud rate divisor)*/
	outb(COM1 + 0, 0x03); /* Set divisor to 3 (lo byte) 38400 baud (hi byte) */
	outb(COM1 + 1, 0x00); /* (hi byte)*/
	outb(COM1 + 3, 0x03); /* 8 bits, no parity, one stop bit */
	outb(COM1 + 2, 0xC7); /* Enable FIFO, clear them, with 14-byte threshold */
	outb(COM1 + 4, 0x0B); /* IRQs enabled, RTS/DSR set */
	outb(COM1 + 4, 0x1E); /* Set in loopback mode, test the serial chip */
	outb(COM1 + 0, 0xAE); /* Test serial chip (send byte 0xAE and check if serial returns same byte) */

	/* Check if serial is faulty (i.e: not same byte as sent) */
	if(insb(COM1 + 0) != 0x0AE) {
		return 1;
	}

	/* If serial is not faulty set it in normal operation mode */
	/* (not-loopback with IRQs enable and OUT#1 and OUT#2 bits enabled) */
	outb(COM1 + 4, 0x0F);
	return 0;

}

int serial_received() {
	return insb(COM1 + 5) & 1;
}

char read_serial() {
	while (serial_received() == 0); /* Please, we have to get some data, not 0 */
	
	return insb(COM1);
	
}

int is_transmit_empty() {
	return insb(COM1 + 5) & 0x20;
}

void write_serial(char a) {
	while (is_transmit_empty() == 0); /* Please, we have to get some data, not 0 */

	outb(COM1, a);

}

void write_serial_string(const char* str) {
	size_t len = strlen(str);
	
	for(int i = 0; i < len; i++) {
		write_serial(str[i]);
	}
	
}
