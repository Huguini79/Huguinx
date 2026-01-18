// Author: Huguini79
// DISK Driver implementation

#include "disk.h"
#include "drivers/io/io.h"
#include "libc/string.h"
#include "libc/stdio.h"
#include "status.h"
#include "config.h"

struct disk disk;

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

void disk_search_and_init() {
	memset(&disk, 0, sizeof(disk));
	disk.type = HUGUINX_DISK_TYPE_REAL; // We set our primary disk
	disk.sector_size = HUGUINX_SECTOR_SIZE; // We define the size of the sectors
}

struct disk* disk_get(int index) {
	if (index != 0) {
		return 0;
	}

	return &disk;

}

int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buf) {
	if(idisk != &disk) {
		return -EIO;
	}

	return disk_read_sector(lba, total, buf); 

}