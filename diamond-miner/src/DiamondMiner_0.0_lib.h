//////////////////////////////////////////////////////
// 
// Author: Oliver Blaser
// 
// Date: 21.09.2015
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

#define c_field		176
#define c_border_v	219
#define c_border_h	219
#define c_corner_ul	219
#define c_corner_ur	219
#define c_corner_dl	219
#define c_corner_dr	219

// define fieldsize
#define field_width	55	// inclusive border
#define field_hight	20	// inclusive border

// class for variables, use only one object
class variable {
public:
	unsigned char field[field_width][field_hight];
	unsigned char kbbut;
	unsigned int page;
	unsigned int cnt_diamond;
};

// class for functions, use only one object
class function {
public:
	void create_field();
	int read_kb();
	void clear_character_position();
	void set_character_position();
	void print();
	void set_color();
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
};

#define DM_lib
#endif
