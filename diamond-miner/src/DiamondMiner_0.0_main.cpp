//////////////////////////////////////////////////////
// 
// Author: Oliver Blaser
// 
// Date: 21.09.2015
//
// Description: Diamond Miner main-file
// 
//////////////////////////////////////////////////////

#include "DiamondMiner_0.0_lib.h"

int main() {

	// create object
	function func;

	// mainloop conditionvariable
	unsigned char ml_cond = 0;

	// mainloop
	do {

		// create & display field
		func.create_field();
		func.set_color();
		func.print();

		do {

			func.clear_character_position();
			
			ml_cond = func.read_kb();
			
			func.set_character_position();

			func.set_color();
			func.print();
		} while (ml_cond & 0b01);

	} while (ml_cond & 0b10);

	return 0;
}
