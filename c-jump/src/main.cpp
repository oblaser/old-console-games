//////////////////////////////////////////////////////
// 
// Author:		Oliver Blaser
// 
// Date:		01.01.2016
//
// Description:	Mainfile of C Jump
// 
//////////////////////////////////////////////////////

// includeing function
#include "function.h"

// mainloop conditions
unsigned int loop_cond;

int main() {

	start();

	// main loop
	while(1) {

		set_default();
		load_file();

		// game loop
		do {

			read_HID();
			loop_cond = set_positions();

			print();

			time_handler();

		} while (loop_cond != ret_exit);

	}

	return 0;
}
