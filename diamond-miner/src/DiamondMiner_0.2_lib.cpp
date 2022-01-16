//////////////////////////////////////////////////////
// 
// Author: Oliver Blaser
// 
// Date: 22.09.2015
//
// Description: Diamond Miner library C-sourcefile
// 
//////////////////////////////////////////////////////

#include "DiamondMiner_0.2_lib.h"

// create objects
coordinate X;
coordinate Y;
variable var;
page print_page;

void function::set_cursor(bool f_state, int f_size) {

	CONSOLE_CURSOR_INFO cursor_info;
	HANDLE  cursor_out;

	cursor_info.bVisible = f_state;

	if (f_state) cursor_info.dwSize = f_size;
	else cursor_info.dwSize = 1;

	cursor_out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(cursor_out, &cursor_info);
}

void function::gotoxy(unsigned int f_goto_x, unsigned int f_goto_y) {

	COORD coord;

	coord.X = f_goto_x;
	coord.Y = f_goto_y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// monster pic
unsigned char pic_monster[8][9] = {
	{ 32,  32, 186,  32, 186,  32, 186,  32,  32 },
	{ 32, 219, 186, 219, 186, 219, 186, 219,  32 },
	{ 32, 219, 219, 219, 186, 219, 219, 219,  32 },
	{ 219, 219,  79, 219, 219, 219,  79, 219, 219 },
	{ 32, 219, 219, 219, 219, 219, 219, 219,  32 },
	{ 219, 219, 219,  32,  32,  32, 219, 219, 219 },
	{ 219,  32, 200, 205,  32, 205, 188,  32, 219 },
	{ 219,  32,  32,  32,  32,  32,  32,  32, 219 }
};

void function::print_pic_monster(unsigned int f_print_x, unsigned int f_print_y) {

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 9; x++) {
			gotoxy(x + f_print_x, y + f_print_y);
			printf("%c", pic_monster[y][x]);
		}
	}
}

//  set variables to default
void function::set_default() {

	// character
	var.field[1][1] = c_character;

	// set handle coordinates to 1,1
	X.handle = 1;
	Y.handle = 1;

	// set diamont- and TNTcounter to 0
	var.cnt_diamond = 0;
	var.cnt_TNT = 0;

	// start in game page
	var.page = 'game';

	// window title
	system("title Diamond Miner");

	// cursor off
	CONSOLE_CURSOR_INFO info;
	HANDLE  out;

	info.bVisible = 0;
	info.dwSize = 1;

	out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(out, &info);

	// set monsterlevels to default
	var.monster_level_a = 0;
	var.monster_level_b = 0;
}

// create the field
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

	// random TNT
	for (int i = 0; i < (field_hight * field_width / 1000 * 1); i++) {
		var.mine[rand() % (field_width - 2) + 1][rand() % (field_hight - 2) + 1] = c_TNT;
	}

	// random monsters
	X.monster_a = rand() % (field_width - 2) + 1;
	Y.monster_a = rand() % (field_hight - 2) + 1;

	var.mine[X.monster_a][Y.monster_a] = c_monster_a;

	X.monster_b = rand() % (field_width - 2) + 1;
	Y.monster_b = rand() % (field_hight - 2) + 1;

	var.mine[X.monster_b][Y.monster_b] = c_monster_a;       // ????????????????????????????????????????????????????????????????????????????????????????

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

		// TNT
		if (var.kbbut == 0x20 && var.cnt_TNT > 0) {

			var.cnt_TNT--;

			if (Y.handle > 1) var.mine[X.handle][Y.handle - 1] = ' ';
			if (Y.handle < field_hight - 2) var.mine[X.handle][Y.handle + 1] = ' ';
			if (X.handle > 1) var.mine[X.handle - 1][Y.handle] = ' ';
			if (X.handle < field_width - 2) var.mine[X.handle + 1][Y.handle] = ' ';
		}

		if (var.kbbut != 'p' && var.kbbut != 0x1B && var.kbbut != 0x0D) return 1;

		break;

	// in pausepage
	case 'paus':

		// continue
		if (var.kbbut == 'p' || var.kbbut == 0x1B) {
			var.page = 'game';
		}

		// restart
		if (var.kbbut == 'r') {
			return 2;
		}

		// exit
		if (var.kbbut == 'x') {
			return 3;
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
					var.cnt_TNT += 2;
				}
				else {
					printf("\tYou haven't enought diamonds!!!");
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

	return 0;
}

void function::clear_character_position(int f_monster_level) {

	if (var.page == 'game') {

		// characters way
		var.field[X.handle][Y.handle] = c_way;
		var.mine[X.handle][Y.handle] = c_way;

		// monsters way
		if (f_monster_level & 0b01) var.field[X.monster_a][Y.monster_a] = c_way;
		else var.mine[X.monster_a][Y.monster_a] = c_to_dig;

		if (f_monster_level & 0b10) var.field[X.monster_b][Y.monster_b] = c_way;
		else var.mine[X.monster_b][Y.monster_b] = c_to_dig;
	}
}

void function::set_character_position(int f_monster_level) {

	if (var.page == 'game') {
		
		// handle with monsters
		if (X.handle == X.monster_a && Y.handle == Y.monster_a && var.cnt_diamond >= 1) var.cnt_diamond -= 1;

		if (X.handle == X.monster_b && Y.handle == Y.monster_b && var.cnt_diamond >= 2) var.cnt_diamond -= 2;
		if (X.handle == X.monster_b && Y.handle == Y.monster_b && var.cnt_diamond == 1) var.cnt_diamond -= 1;

		// monster
		if (f_monster_level & 0b01) var.field[X.monster_a][Y.monster_a] = c_monster_a;
		else var.mine[X.monster_a][Y.monster_a] = c_monster_a;

		if (f_monster_level & 0b10) var.field[X.monster_b][Y.monster_b] = c_monster_b;
		else var.mine[X.monster_b][Y.monster_b] = c_monster_b;

		// count diamonds
		if (var.field[X.handle][Y.handle] == c_diamond) var.cnt_diamond++;

		// count TNT
		if (var.field[X.handle][Y.handle] == c_TNT) var.cnt_TNT++;

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
			printf("        %c", c_diamond_pic);
			break;

		case 4:
			printf("      %c   %c", c_diamond_pic, c_diamond_pic);
			break;

		case 5:
			printf("    %c       %c", c_diamond_pic, c_diamond_pic);
			break;

		case 6:
			if (var.cnt_diamond >= 1000 && var.cnt_diamond < 10000)
				printf("  %c   %d    %c", c_diamond_pic, var.cnt_diamond, c_diamond_pic);

			if (var.cnt_diamond >= 100 && var.cnt_diamond < 1000)
				printf("  %c    %d    %c", c_diamond_pic, var.cnt_diamond, c_diamond_pic);

			if (var.cnt_diamond >= 10 && var.cnt_diamond < 100)
				printf("  %c    %d     %c", c_diamond_pic, var.cnt_diamond, c_diamond_pic);

			if (var.cnt_diamond >= 0 && var.cnt_diamond < 10)
				printf("  %c     %d     %c", c_diamond_pic, var.cnt_diamond, c_diamond_pic);
			break;

		case 7:
			printf("   %c         %c", c_diamond_pic, c_diamond_pic);
			break;

		case 8:
			printf("    %c       %c", c_diamond_pic, c_diamond_pic);
			break;

		case 9:
			printf("     %c     %c", c_diamond_pic, c_diamond_pic);
			break;

		case 10:
			printf("      %c   %c", c_diamond_pic, c_diamond_pic);
			break;

		case 11:
			printf("       %c %c", c_diamond_pic, c_diamond_pic);
			break;

		case 12:
			printf("        %c", c_diamond_pic);
			break;

		case 14:
			printf("  %c: %d", c_TNT, var.cnt_TNT);
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
	printf("\n\t%c TNT:\t\t%d", c_TNT, var.cnt_TNT);

	printf("\n\n\n\tPos.\tItem\t\t\tPrice");

	printf("\n\n\t1:\t2x %c TNT\t\t1 %c", c_TNT, c_diamond);
	printf("\n\t2:\t1x nothong\t\t-");

	printf("\n\n\t");
}

void page::pause() {

	for (int i = 1; i < field_hight + 3; i++) {

		switch (i) {

		case 3:
			printf("\tPaused");
			break;

		case 6:
			printf("\tP: continue");
			break;

		case 7:
			printf("\tR: restart");
			break;

		case 9:
			printf("\tI: instructions");
			break;

		case 10:
			printf("\tA: about");
			break;

		case 12:
			printf("\tX: exit");
			break;

		case 15:
			printf("\t%c %d", c_diamond, var.cnt_diamond);
			break;

		case 17:
			printf("\t%c %d", c_TNT, var.cnt_TNT);
			break;

		default:
			break;
		}

		printf("\n");
	}

	/*
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
	*/
}

void page::instructions() { 

	printf("\n\n\tInstructions");

	printf("\n\n\tMove with WASD or with arrows.");
	printf("\n\tTry to find all diamonds %c.", c_diamond);
	printf("\n\tUse TNT %c with Space to break down walls.", c_TNT);
	printf("\n\tGo to the store %c in the upper left corner with Enter", c_safepoint);

	printf("\n\n\tTo buy sth. in store press Space, select item (1, 2, ...) and\n\tconfirm with Enter.");
	printf("\n\tTo cancel buying enter any other number (999).");

	printf("\n\n\tTake care of the monsters! %c %c", c_monster_a, c_monster_b);

	printf("\n\n\n\tTo go back from anywhere press ESC.");

	printf("\n\n\n");
}

void page::about() {

	printf("\n\n\tAbout");

	printf("\n\n\tProgrammed in September 2015.");

	printf("\n\n\n");
}

int function::torch() {

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

	/*
	for (Y.draw = 0; Y.draw <= (field_hight - 1); Y.draw++) {
		for (X.draw = 0; X.draw <= (field_width - 1); X.draw++) {
			var.field[X.draw][Y.draw] = var.mine[X.draw][Y.draw];
		}
	}
	*/

	// set monster levels
	if (var.mine[X.handle][Y.handle + 2] == c_monster_a ||
		var.mine[X.handle - 1][Y.handle + 1] == c_monster_a ||
		var.mine[X.handle][Y.handle + 1] == c_monster_a ||
		var.mine[X.handle + 1][Y.handle + 1] == c_monster_a ||
		var.mine[X.handle - 2][Y.handle] == c_monster_a ||
		var.mine[X.handle - 1][Y.handle] == c_monster_a ||
		var.mine[X.handle + 1][Y.handle] == c_monster_a ||
		var.mine[X.handle + 2][Y.handle] == c_monster_a ||
		var.mine[X.handle - 1][Y.handle - 1] == c_monster_a ||
		var.mine[X.handle][Y.handle - 1] == c_monster_a ||
		var.mine[X.handle + 1][Y.handle - 1] == c_monster_a ||
		var.mine[X.handle][Y.handle - 2]
		) return 0b01;

	if (var.mine[X.handle][Y.handle + 2] == c_monster_b ||
		var.mine[X.handle - 1][Y.handle + 1] == c_monster_b ||
		var.mine[X.handle][Y.handle + 1] == c_monster_b ||
		var.mine[X.handle + 1][Y.handle + 1] == c_monster_b ||
		var.mine[X.handle - 2][Y.handle] == c_monster_b ||
		var.mine[X.handle - 1][Y.handle] == c_monster_b ||
		var.mine[X.handle + 1][Y.handle] == c_monster_b ||
		var.mine[X.handle + 2][Y.handle] == c_monster_b ||
		var.mine[X.handle - 1][Y.handle - 1] == c_monster_b ||
		var.mine[X.handle][Y.handle - 1] == c_monster_b ||
		var.mine[X.handle + 1][Y.handle - 1] == c_monster_b ||
		var.mine[X.handle][Y.handle - 2]
		) return 0b10;

	return 0;
}

void function::move_monster() {

	time_t mv_m;

	time(&mv_m);
	srand((unsigned int)mv_m);

	if (var.mvm) {

		var.mvm = 0;

		// monster a
		if (rand() % 100 + 1 > 50) {

			if (rand() % 100 + 1 > 50) {
				if (var.mine[X.monster_a + 1][Y.monster_a] != c_wall && var.mine[X.monster_a + 1][Y.monster_a] != c_diamond && var.mine[X.monster_a + 1][Y.monster_a] != c_TNT) X.monster_a++;
			}
			else {
				if (var.mine[X.monster_a - 1][Y.monster_a] != c_wall && var.mine[X.monster_a - 1][Y.monster_a] != c_diamond && var.mine[X.monster_a - 1][Y.monster_a] != c_TNT) X.monster_a--;
			}
		}
		else {

			if (rand() % 100 + 1 > 50) {
				if (var.mine[X.monster_a][Y.monster_a + 1] != c_wall && var.mine[X.monster_a][Y.monster_a + 1] != c_diamond && var.mine[X.monster_a][Y.monster_a + 1] != c_TNT) Y.monster_a++;
			}
			else {
				if (var.mine[X.monster_a][Y.monster_a - 1] != c_wall && var.mine[X.monster_a][Y.monster_a - 1] != c_diamond && var.mine[X.monster_a][Y.monster_a - 1] != c_TNT) Y.monster_a--;
			}
		}

		// monster b
		if (rand() % 100 + 1 > 50) {

			if (rand() % 100 + 1 > 50) {
				if (var.mine[X.monster_b + 1][Y.monster_b] != c_wall && var.mine[X.monster_b + 1][Y.monster_b] != c_diamond && var.mine[X.monster_b + 1][Y.monster_b] != c_TNT) X.monster_b++;
			}
			else {
				if (var.mine[X.monster_b - 1][Y.monster_b] != c_wall && var.mine[X.monster_b - 1][Y.monster_b] != c_diamond && var.mine[X.monster_b - 1][Y.monster_b] != c_TNT) X.monster_b--;
			}
		}
		else {

			if (rand() % 100 + 1 > 50) {
				if (var.mine[X.monster_b][Y.monster_b + 1] != c_wall && var.mine[X.monster_b][Y.monster_b + 1] != c_diamond && var.mine[X.monster_b][Y.monster_b + 1] != c_TNT) Y.monster_b++;
			}
			else {
				if (var.mine[X.monster_b][Y.monster_b - 1] != c_wall && var.mine[X.monster_b][Y.monster_b - 1] != c_diamond && var.mine[X.monster_b][Y.monster_b - 1] != c_TNT) Y.monster_b--;
			}
		}

	}
	else var.mvm = 1;
}
