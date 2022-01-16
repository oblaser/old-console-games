//////////////////////////////////////////////////////
// 
// Author: Oliver Blaser
// 
// Date: 22.09.2015
//
// Description: Diamond Miner main-file
// 
//////////////////////////////////////////////////////

#include "DiamondMiner_0.2_lib.h"

// create object
function func;

void load();

int main() {

	// mainloop conditionvariable
	unsigned char mainloop = 0;
	int monster_level = 0;

	func.set_cursor(0, 0);
	load();

	// mainloop
	do {

		// create & display field
		func.set_default();
		func.create_field();
		func.create_mine();
		func.set_color();
		func.torch();
		func.print();

		do {

			func.clear_character_position(monster_level);
			
			mainloop = func.read_kb();
			
			if (mainloop == 1) func.move_monster();

			monster_level = func.torch();
			func.set_character_position(monster_level);

			func.set_color();
			func.print();

		} while (mainloop != 2 && mainloop != 3);

	} while (mainloop != 3);

	return 0;
}

void load() {

	unsigned char f_Y = 2;
	unsigned char f_with = 60;

	clr_scr;
	col_load;

	for (int i = 0; i < f_with; i++) {

		func.print_pic_monster(0 + i, f_Y);

		// clear start
		for (int j = 0; j < 8; j++) {
			for (int a = 0; a < 9; a++) {
				func.gotoxy(a, j + f_Y);
				clr_char;
			}
		}

		// clear end
		for (int j = 0; j < 8; j++) {
			for (int a = 0; a < 9; a++) {
				func.gotoxy(a + f_with, j + f_Y);
				clr_char;
			}
		}

		// clear back
		for (int j = 0; j < 8; j++) {
			func.gotoxy(i - 1, j + f_Y);
			clr_char;
		}

		Sleep(90);
	}

	clr_scr;
	Sleep(500);
}
