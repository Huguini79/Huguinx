#include "keyboard.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "drivers/io/io.h"
#include "drivers/vga/vga.h"

int shift_pressed = 0;

void init_keyboard() {
	while(1) {
		uint8_t status = insb(0x64);
		
		if (status & 0x01) {
			uint8_t scancode = insb(0x60);
			
			if(scancode == RIGHT_SHIFT_PRESSED_SCANCODE || scancode == LEFT_SHIFT_PRESSED_SCANCODE) {
				shift_pressed = 1;
				continue;
			}
			if(scancode == RIGHT_SHIFT_RELEASED_SCANCODE || scancode == LEFT_SHIFT_RELEASED_SCANCODE) {
				shift_pressed = 0;
				continue;
			}
			
			/* Special Scancodes */
			if(scancode == SPACE_SCANCODE) {huguinx_print(" ");}
			if(scancode == ENTER_SCANCODE) {row_plus();	huguinx_print("root@huguinx# ");}
			// if(scancode == BACKSPACE_SCANCODE) {};
			
			/* Numbers Scancodes */
			if(scancode == ONE_SCANCODE) {huguinx_print("1");}
			if(scancode == TWO_SCANCODE) {huguinx_print("2");}
			if(scancode == THREE_SCANCODE) {huguinx_print("3");}
			if(scancode == FOUR_SCANCODE) {huguinx_print("4");}
			if(scancode == FIVE_SCANCODE) {huguinx_print("5");}
			if(scancode == SIX_SCANCODE) {huguinx_print("6");}
			if(scancode == SEVEN_SCANCODE) {huguinx_print("7");}
			if(scancode == EIGHT_SCANCODE) {huguinx_print("8");}
			if(scancode == NINE_SCANCODE) {huguinx_print("9");}
			if(scancode == ZERO_SCANCODE) {huguinx_print("0");}
			
			/* A-Z Scancodes */
			if(scancode == A_SCANCODE) {huguinx_print(shift_pressed ? "A" : "a");}
			if(scancode == B_SCANCODE) {huguinx_print(shift_pressed ? "B" : "b");}
			if(scancode == C_SCANCODE) {huguinx_print(shift_pressed ? "C" : "b");}
			if(scancode == D_SCANCODE) {huguinx_print(shift_pressed ? "D" : "d");}
			if(scancode == E_SCANCODE) {huguinx_print(shift_pressed ? "E" : "e");}
			if(scancode == F_SCANCODE) {huguinx_print(shift_pressed ? "F" : "f");}
			if(scancode == G_SCANCODE) {huguinx_print(shift_pressed ? "G" : "g");}
			if(scancode == H_SCANCODE) {huguinx_print(shift_pressed ? "H" : "h");}
			if(scancode == I_SCANCODE) {huguinx_print(shift_pressed ? "I" : "i");}
			if(scancode == J_SCANCODE) {huguinx_print(shift_pressed ? "J" : "j");}
			if(scancode == K_SCANCODE) {huguinx_print(shift_pressed ? "K" : "k");}
			if(scancode == L_SCANCODE) {huguinx_print(shift_pressed ? "L" : "l");}
			if(scancode == M_SCANCODE) {huguinx_print(shift_pressed ? "M" : "m");}
			if(scancode == N_SCANCODE) {huguinx_print(shift_pressed ? "N" : "n");}
			if(scancode == O_SCANCODE) {huguinx_print(shift_pressed ? "O" : "o");}
			if(scancode == P_SCANCODE) {huguinx_print(shift_pressed ? "P" : "p");}
			if(scancode == Q_SCANCODE) {huguinx_print(shift_pressed ? "Q" : "q");}
			if(scancode == R_SCANCODE) {huguinx_print(shift_pressed ? "R" : "r");}
			if(scancode == S_SCANCODE) {huguinx_print(shift_pressed ? "S" : "s");}
			if(scancode == T_SCANCODE) {huguinx_print(shift_pressed ? "T" : "t");}
			if(scancode == U_SCANCODE) {huguinx_print(shift_pressed ? "U" : "u");}
			if(scancode == V_SCANCODE) {huguinx_print(shift_pressed ? "V" : "v");}
			if(scancode == W_SCANCODE) {huguinx_print(shift_pressed ? "W" : "w");}
			if(scancode == X_SCANCODE) {huguinx_print(shift_pressed ? "X" : "x");}
			if(scancode == Y_SCANCODE) {huguinx_print(shift_pressed ? "Y" : "y");}
			if(scancode == Z_SCANCODE) {huguinx_print(shift_pressed ? "Z" : "z");}
		}
		
	}
}
