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
#define clr_kbbuf	fflush(stdin);
#define col_game	system("color 06");
#define col_others	system("color 0E");

// define characters
#define c_diamont_game	'*'
#define c_diamont_pause	'*'

#define c_character	1
#define c_safepoint '#'
#define c_diamond	5
#define c_dynamite	20

#define c_to_explore	206
#define c_wall			219
#define c_to_dig		177

// define fieldsize
#define field_width	55	// inclusive border
#define field_hight	20	// inclusive border

// class for variables, use only one object
class variable {
public:
	unsigned char field[field_width][field_hight];
	unsigned char mine[field_width][field_hight];
	unsigned char kbbut;
	unsigned int page;
	unsigned int cnt_diamond;
	unsigned int cnt_dynamite;
	unsigned int store_item;
};

// class for functions, use only one object
class function {
public:
	void create_field();
	void create_mine();
	int read_kb();
	void clear_character_position();
	void set_character_position();
	void print();
	void set_color();
	void lamp();
};

// class for coordinates
class coordinate {
public:
	unsigned char draw;
	unsigned char handle;
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
