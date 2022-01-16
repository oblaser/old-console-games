//////////////////////////////////////////////////////
// 
// Author: Oliver Blaser
// 
// Date: 22.09.2015
//
// Description: Diamond Miner library Headerfile
// 
//////////////////////////////////////////////////////

#ifndef DM_lib

// include some headers
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

// define commands
#define clr_scr		system("cls");
#define clr_char	printf(" ");
#define clr_kbbuf	fflush(stdin);
#define col_game	system("color 06");
#define col_others	system("color 02");
#define col_load	system("color 0C");

// define characters
#define c_diamond_pic	207

#define c_character		79
#define c_monster_a		245
#define c_monster_b		156

#define c_safepoint		35
#define c_diamond		207
#define c_TNT			244

#define c_to_explore	250
#define c_wall			219
#define c_to_dig		177
#define c_way			32

// define fieldsize
#define field_width		55	// inclusive border
#define field_hight		20	// inclusive border

// class for variables, use only one object
class variable {
public:
	unsigned char field[field_width][field_hight];
	unsigned char mine[field_width][field_hight];
	unsigned char kbbut;
	unsigned int page;
	unsigned int cnt_diamond;
	unsigned int cnt_TNT;
	unsigned int store_item;
	unsigned char mvm;
	int monster_level_a;
	int monster_level_b;
};

// class for functions, use only one object
class function {
public:
	void set_cursor(bool f_state, int f_size);
	void gotoxy(unsigned int f_goto_x, unsigned int f_goto_y);
	void print_pic_monster(unsigned int f_print_x, unsigned int f_print_y);
	void set_default();
	void create_field();
	void create_mine();
	int read_kb();
	void clear_character_position(int f_monster_level);
	void set_character_position(int f_monster_level);
	void print();
	void set_color();
	int torch();
	void move_monster();
};

// class for coordinates
class coordinate {
public:
	unsigned char draw;
	unsigned char handle;
	unsigned char monster_a;
	unsigned char monster_b;
};

// class for pages, use only one object
class page {
public:
	void game();
	void pause();
	void instructions();
	void about();
	void store();
};

#define DM_lib
#endif
