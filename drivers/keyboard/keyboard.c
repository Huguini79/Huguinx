#include "keyboard.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "drivers/io/io.h"
#include "drivers/vga/vga.h"
#include "kernel/kernel.h"
#include "drivers/disk/disk.h"
#include "pit/pit.h"

#include "drivers/keyboard/command/process_command.h"

int shift_pressed = 0;

char command_buffer[1024]; // 1024 bytes (1 KB) Buffer

int pos = 0;

void add_character(char c) {
	command_buffer[pos++] = c;
	command_buffer[pos] = '\0';
}

void init_keyboard() {
			uint8_t scancode = insb(0x60);
			
			if(scancode == RIGHT_SHIFT_PRESSED_SCANCODE || scancode == LEFT_SHIFT_PRESSED_SCANCODE) {
				shift_pressed = 1;
			}
			if(scancode == RIGHT_SHIFT_RELEASED_SCANCODE || scancode == LEFT_SHIFT_RELEASED_SCANCODE) {
				shift_pressed = 0;
			}
			
 
			/* Special Scancodes */
			if(scancode == SPACE_SCANCODE) {huguinx_print(" ");write_serial(' ');add_character(' ');}
			if(scancode == ENTER_SCANCODE) {
				
				init_process_command();

				command_buffer[0] = '\0';
				pos = 0;
				
			}
			// if(scancode == BACKSPACE_SCANCODE) {};
			
			/* Numbers Scancodes */
			if(scancode == ONE_SCANCODE) {huguinx_print("1");write_serial('1');add_character('1');}
			if(scancode == TWO_SCANCODE) {huguinx_print("2");write_serial('2');add_character('2');}
			if(scancode == THREE_SCANCODE) {huguinx_print("3");write_serial('3');add_character('3');}
			if(scancode == FOUR_SCANCODE) {huguinx_print("4");write_serial('4');add_character('4');}
			if(scancode == FIVE_SCANCODE) {huguinx_print("5");write_serial('5');add_character('5');}
			if(scancode == SIX_SCANCODE) {huguinx_print("6");write_serial('6');add_character('6');}
			if(scancode == SEVEN_SCANCODE) {huguinx_print("7");write_serial('7');add_character('7');}
			if(scancode == EIGHT_SCANCODE) {huguinx_print("8");write_serial('8');add_character('8');}
			if(scancode == NINE_SCANCODE) {huguinx_print("9");write_serial('9');add_character('9');}
			if(scancode == ZERO_SCANCODE) {huguinx_print("0");write_serial('0');add_character('0');}
			
			/* A-Z Scancodes */
			if(scancode == A_SCANCODE) {huguinx_print(shift_pressed ? "A" : "a");write_serial_string(shift_pressed ? "A" : "a");add_character('a');}
			if(scancode == B_SCANCODE) {huguinx_print(shift_pressed ? "B" : "b");write_serial_string(shift_pressed ? "B" : "b");add_character('b');}
			if(scancode == C_SCANCODE) {huguinx_print(shift_pressed ? "C" : "c");write_serial_string(shift_pressed ? "C" : "c");add_character('c');}
			if(scancode == D_SCANCODE) {huguinx_print(shift_pressed ? "D" : "d");write_serial_string(shift_pressed ? "D" : "d");add_character('d');}
			if(scancode == E_SCANCODE) {huguinx_print(shift_pressed ? "E" : "e");write_serial_string(shift_pressed ? "E" : "e");add_character('e');}
			if(scancode == F_SCANCODE) {huguinx_print(shift_pressed ? "F" : "f");write_serial_string(shift_pressed ? "F" : "f");add_character('f');}
			if(scancode == G_SCANCODE) {huguinx_print(shift_pressed ? "G" : "g");write_serial_string(shift_pressed ? "G" : "g");add_character('g');}
			if(scancode == H_SCANCODE) {huguinx_print(shift_pressed ? "H" : "h");write_serial_string(shift_pressed ? "H" : "h");add_character('h');}
			if(scancode == I_SCANCODE) {huguinx_print(shift_pressed ? "I" : "i");write_serial_string(shift_pressed ? "I" : "i");add_character('i');}
			if(scancode == J_SCANCODE) {huguinx_print(shift_pressed ? "J" : "j");write_serial_string(shift_pressed ? "J" : "j");add_character('j');}
			if(scancode == K_SCANCODE) {huguinx_print(shift_pressed ? "K" : "k");write_serial_string(shift_pressed ? "K" : "k");add_character('k');}
			if(scancode == L_SCANCODE) {huguinx_print(shift_pressed ? "L" : "l");write_serial_string(shift_pressed ? "L" : "l");add_character('l');}
			if(scancode == M_SCANCODE) {huguinx_print(shift_pressed ? "M" : "m");write_serial_string(shift_pressed ? "M" : "m");add_character('m');}
			if(scancode == N_SCANCODE) {huguinx_print(shift_pressed ? "N" : "n");write_serial_string(shift_pressed ? "N" : "n");add_character('n');}
			if(scancode == O_SCANCODE) {huguinx_print(shift_pressed ? "O" : "o");write_serial_string(shift_pressed ? "O" : "o");add_character('o');}
			if(scancode == P_SCANCODE) {huguinx_print(shift_pressed ? "P" : "p");write_serial_string(shift_pressed ? "P" : "p");add_character('p');}
			if(scancode == Q_SCANCODE) {huguinx_print(shift_pressed ? "Q" : "q");write_serial_string(shift_pressed ? "Q" : "q");add_character('q');}
			if(scancode == R_SCANCODE) {huguinx_print(shift_pressed ? "R" : "r");write_serial_string(shift_pressed ? "R" : "r");add_character('r');}
			if(scancode == S_SCANCODE) {huguinx_print(shift_pressed ? "S" : "s");write_serial_string(shift_pressed ? "S" : "s");add_character('s');}
			if(scancode == T_SCANCODE) {huguinx_print(shift_pressed ? "T" : "t");write_serial_string(shift_pressed ? "T" : "t");add_character('t');}
			if(scancode == U_SCANCODE) {huguinx_print(shift_pressed ? "U" : "u");write_serial_string(shift_pressed ? "U" : "u");add_character('u');}
			if(scancode == V_SCANCODE) {huguinx_print(shift_pressed ? "V" : "v");write_serial_string(shift_pressed ? "V" : "v");add_character('v');}
			if(scancode == W_SCANCODE) {huguinx_print(shift_pressed ? "W" : "w");write_serial_string(shift_pressed ? "W" : "w");add_character('w');}
			if(scancode == X_SCANCODE) {huguinx_print(shift_pressed ? "X" : "x");write_serial_string(shift_pressed ? "X" : "x");add_character('x');}
			if(scancode == Y_SCANCODE) {huguinx_print(shift_pressed ? "Y" : "y");write_serial_string(shift_pressed ? "Y" : "y");add_character('y');}
			if(scancode == Z_SCANCODE) {huguinx_print(shift_pressed ? "Z" : "z");write_serial_string(shift_pressed ? "Z" : "z");add_character('z');}

		outb(0x20, 0x20);
}
