//////////////////////////////////////////////////////
// 
// Author: Oliver Blaser
// 
// Date: 22.09.2015
//
// Description: Diamond Miner library C-sourcefile
// 
//////////////////////////////////////////////////////

#include "DiamondMiner_0.1_lib.h"

// create objects
coordinate X;
coordinate Y;
variable var;
page print_page;

// create the field and set variables to default
void function::create_field() {

	// field
	for (Y.draw = 0; Y.draw <= (field_hight-1); Y.draw++) {
		for (X.draw = 0; X.draw <= (field_width-1); X.draw++) {
			var.field[X.draw][Y.draw] = c_to_explore;
		}
	}

	// border
	// vertical
	for (Y.draw = 1; Y.draw <= (field_hight-2); Y.draw++) {
		var.field[0][Y.draw] = c_wall;
		var.field[field_width-1][Y.draw] = c_wall;
	}

	// horizontal
	for (X.draw = 1; X.draw <= (field_width-2); X.draw++) {
		var.field[X.draw][0] = c_wall;
		var.field[X.draw][field_hight-1] = c_wall;
	}

	// corner
	var.field[0][0] = c_wall;
	var.field[0][field_hight-1] = c_wall;
	var.field[field_width-1][0] = c_wall;
	var.field[field_width - 1][field_hight - 1] = c_wall;

	// character
	var.field[1][1] = c_character;

	// set handle coordinates to 1,1
	X.handle = 1;
	Y.handle = 1;

	// set diamont- and dynamitecounter to 0
	var.cnt_diamond = 0;
	var.cnt_dynamite = 0;

	// start in game page
	var.page = 'game';

	// window title
	system("title Diamond Miner");
}

// create mine plan
void function::create_mine() {

	time_t t;

	time(&t);
	srand((unsigned int)t);

	for (Y.draw = 0; Y.draw <= (field_hight - 1); Y.draw++) {
		for (X.draw = 0; X.draw <= (field_width - 1); X.draw++) {
			var.mine[X.draw][Y.draw] = c_to_dig;
		}
	}

	// random walls
	for (int i = 0; i < (field_hight * field_width / 1000 * 380); i++) {
		var.mine[rand() % (field_width - 2) + 1][rand() % (field_hight - 2) + 1] = c_wall;
	}

	// random dynamite
	for (int i = 0; i < (field_hight * field_width / 1000 * 1); i++) {
		var.mine[rand() % (field_width - 2) + 1][rand() % (field_hight - 2) + 1] = c_dynamite;
	}

	// random diamonds
	for (int i = 0; i < (field_hight * field_width / 1000 * 10); i++) {
		var.mine[rand() % (field_width - 2) + 1][rand() % (field_hight - 2) + 1] = c_diamond;
	}

	// border
	// vertical
	for (Y.draw = 1; Y.draw <= (field_hight - 2); Y.draw++) {
		var.mine[0][Y.draw] = c_wall;
		var.mine[field_width - 1][Y.draw] = c_wall;
	}

	// horizontal
	for (X.draw = 1; X.draw <= (field_width - 2); X.draw++) {
		var.mine[X.draw][0] = c_wall;
		var.mine[X.draw][field_hight - 1] = c_wall;
	}

	// corner
	var.mine[0][0] = c_wall;
	var.mine[0][field_hight - 1] = c_wall;
	var.mine[field_width - 1][0] = c_wall;
	var.mine[field_width - 1][field_hight - 1] = c_wall;

	// first line to middle without walls
	for (X.draw = 1; X.draw <= (field_width - 2); X.draw++) {
		if (X.draw < 25) var.mine[X.draw][1] = c_to_dig;
	}

	// safepoint
	var.mine[1][1] = c_safepoint;
}

// calculate new position, or display information pages
int function::read_kb() {

	// read keyboardbutton
	clr_kbbuf;
	var.kbbut = _getch();

	switch (var.page) {

	// in gamepage
	case 'game':

		// up
		if (var.kbbut == 'w' || var.kbbut == 0x48) {
			if (Y.handle > 1 && var.mine[X.handle][Y.handle - 1] != c_wall) Y.handle--;
		}

		// down
		if (var.kbbut == 's' || var.kbbut == 0x50) {
			if (Y.handle < field_hight - 2 && var.mine[X.handle][Y.handle + 1] != c_wall) Y.handle++;
		}

		// right
		if (var.kbbut == 'd' || var.kbbut == 0x4D) {
			if (X.handle < field_width - 2 && var.mine[X.handle + 1][Y.handle] != c_wall) X.handle++;
		}

		// left
		if (var.kbbut == 'a' || var.kbbut == 0x4B) {
			if (X.handle > 1 && var.mine[X.handle - 1][Y.handle] != c_wall) X.handle--;
		}

		// store
		if (var.kbbut == 0x0D && X.handle == 1 && Y.handle == 1) {
			var.page = 'stor';
		}

		// pause
		if (var.kbbut == 'p' || var.kbbut == 0x1B) {
			var.page = 'paus';
		}

		// dynamite
		if (var.kbbut == 0x20 && var.cnt_dynamite > 0) {

			var.cnt_dynamite--;

			if (Y.handle > 1) var.mine[X.handle][Y.handle - 1] = ' ';
			if (Y.handle < field_hight - 2) var.mine[X.handle][Y.handle + 1] = ' ';
			if (X.handle > 1) var.mine[X.handle - 1][Y.handle] = ' ';
			if (X.handle < field_width - 2) var.mine[X.handle + 1][Y.handle] = ' ';
		}

		break;

	// in pausepage
	case 'paus':

		// continue
		if (var.kbbut == 'p' || var.kbbut == 0x1B) {
			var.page = 'game';
		}

		// restart
		if (var.kbbut == 'r') {
			return 0b10;
		}

		// exit
		if (var.kbbut == 'x') {
			return 0b00;
		}

		// about
		if (var.kbbut == 'a') {
			var.page = 'abot';
		}

		// instructions
		if (var.kbbut == 'i') {
			var.page = 'inst';
		}

		break;

	// in instructionpage
	case 'inst':

		// back
		if (var.kbbut == 0x1B) {
			var.page = 'paus';
		}

		break;

	// in aboutpage
	case 'abot':

		// back
		if (var.kbbut == 0x1B) {
			var.page = 'paus';
		}

		break;

	// in storepage
	case 'stor':

		// back
		if (var.kbbut == 0x1B) {
			var.page = 'game';
		}

		// buy
		if (var.kbbut == 0x20) {

			printf("Buy item: ");

			scanf_s("%d", &var.store_item);

			switch (var.store_item) {
			case 1:
				if (var.cnt_diamond >= 1) {
					var.cnt_diamond -= 1;
					var.cnt_dynamite += 2;
				}
				else {
					printf("You haven't enought diamonds");
					Sleep(2000);
				}
				break;

			default:
				var.page = 'stor';
				break;
			}
		}

		break;

	default:
		break;

	}

	return 0b11;
}

void function::clear_character_position() {

	if (var.page == 'game') {
		var.field[X.handle][Y.handle] = ' ';
		var.mine[X.handle][Y.handle] = ' ';
	}
}

void function::set_character_position() {

	if (var.page == 'game') {
		
		// count diamonds
		if (var.field[X.handle][Y.handle] == c_diamond) var.cnt_diamond++;

		// count dynamite
		if (var.field[X.handle][Y.handle] == c_dynamite) var.cnt_dynamite++;

		// character
		var.field[X.handle][Y.handle] = c_character;

		// safepoint
		if ((X.handle != 1) || (Y.handle != 1)) var.field[1][1] = c_safepoint;
	}
}

void function::print() {

	clr_scr;

	// game page
	if (var.page == 'game') print_page.game();

	// store
	if (var.page == 'stor') print_page.store();

	// pause page
	if (var.page == 'paus') print_page.pause();

	// about
	if (var.page == 'abot') print_page.about();

	// instructions
	if (var.page == 'inst') print_page.instructions();
}

void function::set_color() {

	if (var.page == 'game') col_game;
	if (var.page != 'game') col_others;
}

void page::game() {

	printf("\n\n ");

	for (Y.draw = 0; Y.draw <= (field_hight - 1); Y.draw++) {
		for (X.draw = 0; X.draw <= (field_width - 1); X.draw++) {
			printf("%c", var.field[X.draw][Y.draw]);
		}

		switch (Y.draw) {
		case 1:
			printf("  Diamond Miner");
			break;

		case 3:
			printf("        %c", c_diamont_game);
			break;

		case 4:
			printf("      %c   %c", c_diamont_game, c_diamont_game);
			break;

		case 5:
			printf("    %c       %c", c_diamont_game, c_diamont_game);
			break;

		case 6:
			if (var.cnt_diamond >= 1000 && var.cnt_diamond < 10000)
				printf("  %c   %d    %c", c_diamont_game, var.cnt_diamond, c_diamont_game);

			if (var.cnt_diamond >= 100 && var.cnt_diamond < 1000)
				printf("  %c    %d    %c", c_diamont_game, var.cnt_diamond, c_diamont_game);

			if (var.cnt_diamond >= 10 && var.cnt_diamond < 100)
				printf("  %c    %d     %c", c_diamont_game, var.cnt_diamond, c_diamont_game);

			if (var.cnt_diamond >= 0 && var.cnt_diamond < 10)
				printf("  %c     %d     %c", c_diamont_game, var.cnt_diamond, c_diamont_game);
			break;

		case 7:
			printf("   %c         %c", c_diamont_game, c_diamont_game);
			break;

		case 8:
			printf("    %c       %c", c_diamont_game, c_diamont_game);
			break;

		case 9:
			printf("     %c     %c", c_diamont_game, c_diamont_game);
			break;

		case 10:
			printf("      %c   %c", c_diamont_game, c_diamont_game);
			break;

		case 11:
			printf("       %c %c", c_diamont_game, c_diamont_game);
			break;

		case 12:
			printf("        %c", c_diamont_game);
			break;

		case 14:
			printf("  %c: %d", c_dynamite, var.cnt_dynamite);
			break;

		case 16:
			printf("  Press P for pause");
			break;

		default:
			printf(" ");
			break;
		}

		printf("\n ");
	}

	printf("\n\n");
}

void page::store() {

	printf("\n\n\tMiners store");

	printf("\n\n\n\t%c Diamonds:\t%d", c_diamond, var.cnt_diamond);
	printf("\n\t%c Dynamite:\t%d", c_dynamite, var.cnt_dynamite);

	printf("\n\n\n\tLot\tItem\t\t\tPrice");

	printf("\n\n\t2\t1 %c Dynamite\t\t1 %c", c_dynamite, c_diamond);
	printf("\n\tx\t2 coming soon\t\tx");

	printf("\n\n\t");
}

void page::pause() {

	printf("\n\n\tPaused");
	
	printf("\n\n\n\tP: continue");
	printf("\n\tR: restart");
	printf("\n\n\tI: instructions");
	printf("\n\tA: about");
	printf("\n\n\tX: exit");

	printf("\n\n");
	printf("\n\t    %c", c_diamont_pause);
	printf("\n\t  %c   %c", c_diamont_pause, c_diamont_pause);
	printf("\n\t%c       %c  %d", c_diamont_pause, c_diamont_pause, var.cnt_diamond);
	printf("\n\t %c     %c", c_diamont_pause, c_diamont_pause);
	printf("\n\t  %c   %c", c_diamont_pause, c_diamont_pause);
	printf("\n\t   %c %c", c_diamont_pause, c_diamont_pause);
	printf("\n\t    %c", c_diamont_pause);
	printf("\n\n\n\n");
}

void page::instructions() { 

	printf("\n\n\tInstructions");

	printf("\n\n\tMove with WASD or with arrows.");
	printf("\n\tTry to find all diamonds %c.", c_diamond);
	printf("\n\tUse dynamite %c with Space to break down walls.", c_dynamite);
	printf("\n\tGo to the store %c in the upper left corner with Enter", c_safepoint);

	printf("\n\n\tTo buy sth. in store press Space, select item (1, 2, ...) and\n\tconfirm with Enter.");
	printf("\n\tTo cancel buying enter any other number (999).");

	printf("\n\n\n\tTo go back from anywhere press ESC.");

	printf("\n\n\n");
}

void page::about() {

	printf("\n\n\tAbout");

	printf("\n\n\tProgrammed in September 2015.");

	printf("\n\n\n");
}

void function::lamp() {

	var.mine[1][1] = c_safepoint;

	if (Y.handle < field_hight - 2) var.field[X.handle][Y.handle + 2] = var.mine[X.handle][Y.handle + 2];

	var.field[X.handle - 1][Y.handle + 1] = var.mine[X.handle - 1][Y.handle + 1];
	var.field[X.handle][Y.handle + 1] = var.mine[X.handle][Y.handle + 1];
	var.field[X.handle + 1][Y.handle + 1] = var.mine[X.handle + 1][Y.handle + 1];

	if (X.handle > 1) var.field[X.handle - 2][Y.handle] = var.mine[X.handle - 2][Y.handle];
	var.field[X.handle - 1][Y.handle] = var.mine[X.handle - 1][Y.handle];
	var.field[X.handle + 1][Y.handle] = var.mine[X.handle + 1][Y.handle];
	if(X.handle < field_width - 2) var.field[X.handle + 2][Y.handle] = var.mine[X.handle + 2][Y.handle];

	var.field[X.handle - 1][Y.handle - 1] = var.mine[X.handle - 1][Y.handle - 1];
	var.field[X.handle][Y.handle - 1] = var.mine[X.handle][Y.handle - 1];
	var.field[X.handle + 1][Y.handle - 1] = var.mine[X.handle + 1][Y.handle - 1];

	if (Y.handle > 1) var.field[X.handle][Y.handle - 2] = var.mine[X.handle][Y.handle - 2];
}
