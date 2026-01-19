#include "movemer.h"
#include "drivers/vga/vga.h"
#include "pit/pit.h"

void player_move() {
	sleep_for_game(500);
}

void movemer_init() {
	for (int i = 0; i < 100; i++) {
		sleep_for_game(200);
	}
}
