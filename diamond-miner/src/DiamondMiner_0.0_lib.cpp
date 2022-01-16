//////////////////////////////////////////////////////
// 
// Author: Oliver Blaser
// 
// Date: 21.09.2015
//
// Description: Diamond Miner library C-sourcefile
// 
//////////////////////////////////////////////////////

#include "DiamondMiner_0.0_lib.h"

// create objects
coordinate X;
coordinate Y;
variable var;
page print_page;

// create the field with border and "dirt" and set variables to default
void function::create_field() {

	// field
	for (Y.draw = 0; Y.draw <= (field_hight-1); Y.draw++) {
		for (X.draw = 0; X.draw <= (field_width-1); X.draw++) {
			var.field[X.draw][Y.draw] = c_field;
		}
	}

	// border
	// vertical
	for (Y.draw = 1; Y.draw <= (field_hight-2); Y.draw++) {
		var.field[0][Y.draw] = c_border_v;
		var.field[field_width-1][Y.draw] = c_border_v;
	}

	// horizontal
	for (X.draw = 1; X.draw <= (field_width-2); X.draw++) {
		var.field[X.draw][0] = c_border_h;
		var.field[X.draw][field_hight-1] = c_border_h;
	}

	// corner
	var.field[0][0] = c_corner_ul;
	var.field[0][field_hight-1] = c_corner_dl;
	var.field[field_width-1][0] = c_corner_ur;
	var.field[field_width - 1][field_hight - 1] = c_corner_dr;

	// character
	var.field[1][1] = 1;

	// set handle coordinates to 1,1
	X.handle = 1;
	Y.handle = 1;

	// set diamontcounter to 0
	var.cnt_diamond = 0;

	// start in game page
	var.page = 'game';

	// window title
	system("title Diamond Miner");
}

// calculate new position, or display information pages
int function::read_kb() {

	// read keyboardbutton
	clr_kbbuf;
	var.kbbut = _getch();

	// up
	if ((var.kbbut == 'w' || var.kbbut == 0x48) && var.page == 'game') {
		if(Y.handle > 1) Y.handle--;
	}

	// down
	if ((var.kbbut == 's' || var.kbbut == 0x50) && var.page == 'game') {
		if (Y.handle < field_hight - 2) Y.handle++;
	}

	// right
	if ((var.kbbut == 'd' || var.kbbut == 0x4D) && var.page == 'game') {
		if (X.handle < field_width - 2) X.handle++;
	}

	// left
	if ((var.kbbut == 'a' || var.kbbut == 0x4B) && var.page == 'game') {
		if (X.handle > 1) X.handle--;
	}

	// pause
	if (var.kbbut == 'p') {
		if(var.page == 'game') var.page = 'paus';
		else var.page = 'game';
	}

	// restart
	if (var.kbbut == 'r' && (var.page == 'game' || var.page == 'paus')) {
		return 0b10;
	}

	// exit
	if (var.kbbut == 'x' && var.page == 'paus') {
		return 0b00;
	}

	// about
	if (var.kbbut == 'a' && var.page == 'paus') {
		var.page = 'abot';
	}

	// instructions
	if (var.kbbut == 'i' && var.page == 'paus') {
		var.page = 'inst';
	}

	// back
	if (var.kbbut == 0x08 && (var.page == 'inst' || var.page == 'abot')) {
		var.page = 'paus';
	}

	return 0b11;
}

void function::clear_character_position() {

	if (var.page == 'game') {
		var.field[X.handle][Y.handle] = ' ';
	}
}

void function::set_character_position() {

	if (var.page == 'game') {
		
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

		case 15:
			printf("  Press P for pause");
			break;

		case 17:
			printf("  Press R to restart");
			break;

		default:
			printf(" ");
			break;
		}

		printf("\n ");
	}

	printf("\n\n");
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
	printf("\n\tTry to find all diamonds.");

	printf("\n\n\n\tBack with backspace");

	printf("\n\n\n");
}

void page::about() {

	printf("\n\n\tAbout");

	printf("\n\n\tProgrammed in September 2015.");

	printf("\n\n\n\tBack with backspace");

	printf("\n\n\n");
}
