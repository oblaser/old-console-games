//////////////////////////////////////////////////////
// 
// Author:		Oliver Blaser
// 
// Date:		05.10.2015
//
// Description:	Mainfile of Diamond Miner
// 
//////////////////////////////////////////////////////

// includeing function
#include "function.h"

// mainloop conditions
unsigned int loop_cond;

int main() {

	// restart loop
	do {

		set_default();
		create_field();
		set_positions();
		print();

		// game loop
		do {

			print();

			loop_cond = read_HID();
			if (loop_cond == ret_game) {
				move_others();
				set_positions();
			}

		} while (loop_cond != ret_exit && loop_cond != ret_restart);

	} while (loop_cond != ret_exit);

	return 0;
}
