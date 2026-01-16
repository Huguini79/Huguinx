// Author: Huguini79
// DISK Driver implementation

#include "disk.h"
#include "drivers/io/io.h"

int disk_read_sector(int lba, int total, void* buf) {
	outb(0x1F6, (lba >> 24) | 0xE0); // Select master drive and pass part of the LBA
	outb(0x1F2, total); // The total sectors that we want to read
	outb(0x1F3, (unsigned char)(lba & 0xff)); // LBA Low
	outb(0x1F4, (unsigned char)(lba >> 8)); // LBA Mid
	outb(0x1F5, (unsigned char)(lba >> 16)); // LBA High
	outb(0x1F7, 0x20); // Read command <- Because in 0x1F7 we set the mode of operation (read command ....................)

	/* Poll until we are ready to read */
	/* (Also we can use interrupts <- idt) */

	unsigned short* ptr = (unsigned short*) buf;

	for (int b = 0; b < total; b++) {
		// Wait for the buffer to be ready
		char c = insb(0x1F7);

		while (!(c & 0x08)) {
			c = insb(0x1F7);
		}

		/* Read two bytes at a time into the buffer from the ATA controller */
		/* (Copy from hard disk to memory) */
		for (int i = 0; i < 256; i++) {
			*ptr = insw(0x1F0);
			ptr++;
		}

	}

	return 0;

}


