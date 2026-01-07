// Author: Huguini79
// Keyboard driver implementation
#ifndef KEYBOARD_H
#define KEYBOARD_H

/* Keyboard Scancodes */

/* Special Scancodes */
#define ESC_SCANCODE 0x01
#define SINGLE_QUOTE_SCANCODE 0x28
#define ALT_SCANCODE 0x38
#define ENTER_SCANCODE 0x1C
#define SEMICOLON_SCANCODE 0x27
#define COMMA_SCANCODE 0x33
#define SPOT_SCANCODE 0x34
#define EQUALS_SCANCODE 0x0D
#define SLASH_SCANCODE 0x35
#define LEFT_SHIFT_SCANCODE 0x2A
#define RIGHT_SHIFT_SCANCODE 0x36
#define NUMBER_LOCK_SCANCODE 0x45

/* Numbers Scancodes (0-9)*/
#define ZERO_SCANCODE 0x0B
#define ONE_SCANCODE 0x02
#define TWO_SCANCODE 0x03
#define THREE_SCANCODE 0x04
#define FOUR_SCANCODE 0x05
#define FIVE_SCANCODE 0x06
#define SIX_SCANCODE 0x07
#define SEVEN_SCANCODE 0x08
#define EIGHT_SCANCODE 0x09
#define NINE_SCANCODE 0x0A

/* A-Z Scancodes */
#define A_SCANCODE 0x1E
#define B_SCANCODE 0x30
#define C_SCANCODE 0x2E
#define D_SCANCODE 0x20
#define E_SCANCODE 0x12
#define F_SCANCODE 0x21
#define G_SCANCODE 0x22
#define H_SCANCODE 0x23
#define I_SCANCODE 0x17
#define J_SCANCODE 0x24
#define K_SCANCODE 0x25
#define L_SCANCODE 0x26
#define M_SCANCODE 0x32
#define N_SCANCODE 0x31
#define O_SCANCODE 0x18
#define P_SCANCODE 0x19
#define Q_SCANCODE 0x10
#define R_SCANCODE 0x13
#define S_SCANCODE 0x1F
#define T_SCANCODE 0x14
#define U_SCANCODE 0x16
#define V_SCANCODE 0x2F
#define W_SCANCODE 0x11
#define X_SCANCODE 0x2D
#define Y_SCANCODE 0x15
#define Z_SCANCODE 0x2C

void init_Keyboard();

#endif
