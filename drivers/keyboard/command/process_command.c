#include "drivers/keyboard/keyboard.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "drivers/io/io.h"
#include "drivers/vga/vga.h"
#include "kernel/kernel.h"
#include "drivers/disk/disk.h"
#include "pit/pit.h"

#include "process_command.h"
int we_call_disk = 0;

void init_process_command() {
    if(command_buffer[0] == '\0') {row_plus();	write_serial('\n');huguinx_print("# ");write_serial_string("# ");}
				else if(strncmp(command_buffer, "hello", 5) == 0) {row_plus();huguinx_print("HELLO FROM HUGUINX\n\n");write_serial_string("\nHELLO FROM HUGUINX\n\n");huguinx_print("# ");write_serial_string("# ");}
				else if(strncmp(command_buffer, "read1sector", 11) == 0) {
					char disk_buf[1024]; 
					disk_read_sector(0, 1, disk_buf);

					if (we_call_disk == 1) {
						for (int i = 0; i < 1024; i++) 
						{
							huguinx_perfectchar(disk_buf[i], 15);
							write_serial(disk_buf[i]);
						}
							row_plus();
							row_plus();
							huguinx_print("# ");
							write_serial_string("\n\n# ");
						} else {
							
						}
					}
				else if(strncmp(command_buffer, "read3sectors", 12) == 0) {
					char disk_buf2[2048]; 
					disk_read_sector(0, 3, disk_buf2);
					if (we_call_disk == 1) { 
						for (int i = 0; i < 2048; i++) {
							huguinx_perfectchar(disk_buf2[i], 15);
							write_serial(disk_buf2[i]);
						}
						row_plus();
						row_plus();
						huguinx_print("# "); 
						write_serial_string("\n\n# ");
					} else {
						
					}
				}
				else if(strncmp(command_buffer, "write1sector", 12) == 0) {
					char letra[300] = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
					/* PIT */
					/* Ask to the user how many sectors do you want to write, and up how many sectors do you want to read */
					for (int i = 0; i < 300; i++) {
						sleep(100);
						disk_write_sector(0, i, letra);
					}
				}
				else if(strncmp(command_buffer, "clear", 5) == 0) {huguinx_clear();row_plus();huguinx_print("# ");write_serial_string("# ");}
				else if(strncmp(command_buffer, "echo", 4) == 0) {row_plus();huguinx_print(command_buffer + 5);write_serial('\n');write_serial_string(command_buffer + 5);row_plus();row_plus();huguinx_print("# ");write_serial_string("\n\n# ");}
				else if(strncmp(command_buffer, "help", 4) == 0) {huguinx_clear();huguinx_print("HELP:\nwrite1sector - Writes the letter Z in the one sector\ninitdisk - INIT THE DISK DRIVER\nclear - Clears the screen <- this only works in VGA text mode\nread1sector - Reads 1 sector of the ATA/IDE Hard Drive\nwait1 - Waits 1 second <- this uses PIT\nread3sectors - Reads 3 sectors of the ATA/IDE Hard Drive\nhello - A simple hello for the huguinx operating system\necho - Prints the text that you want");row_plus();row_plus();huguinx_print("# ");}
				else if(strncmp(command_buffer, "wait1", 5) == 0) {sleep(1000);}
				else if(strncmp(command_buffer, "initdisk", 8) == 0) {we_call_disk = 1; disk_driver_init();}
				else {huguinx_logs("ERROR => COMMAND NOT RECOGNIZED");
    }
}