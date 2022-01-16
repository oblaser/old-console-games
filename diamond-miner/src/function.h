//////////////////////////////////////////////////////
// 
// Author:		Oliver Blaser
// 
// Date:		24.10.2015
//
// Description:	Functions for Diamond Miner
// 
//////////////////////////////////////////////////////

#ifndef functions_h

// includeing libraries
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// includeing files
#include "defines.h"

// class for coordinates
class coordinate {
public:
	unsigned int draw;
	unsigned int miner;
	unsigned int start_pos;
	unsigned int monster_a1;
	unsigned int monster_b1;
};

/* --- std func --- */

// cursor settings function
unsigned int set_cursor(bool f_state, int f_size);

// set cursor to x y
unsigned int gotoxy(unsigned int f_goto_x, unsigned int f_goto_y);

// print on x y
unsigned int printxy(char f_string[], unsigned int f_print_x, unsigned int f_print_y);

// convert kb-scancode to decimal
unsigned int convert_kb_dec(unsigned char f_kbbut);

// clear dialog box
unsigned int clr_dialog_box();

// error
unsigned int error(unsigned int f_error_nr);

/* --- extern files --- */

unsigned int create_file(char f_file_name[]);

unsigned int load_value(char f_value_name[], char f_file_name[]);

unsigned int save_value(char f_file_name[]);

/* --- print pics --- */

unsigned int print_pic_monster_big(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_pickax_big(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_diamond_big(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_diamond_text(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_miner_text(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_store(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_monster_one(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_monster_two(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_miner(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_wall(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_way(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_TNT(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_diamond(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_error(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_to_dig(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_slime(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_C4(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_map(unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_pic_select(unsigned int f_pic, unsigned int f_print_x, unsigned int f_print_y);

unsigned int print_counters();

unsigned int print_border();

// unsigned int print_pic_(unsigned int f_print_x, unsigned int f_print_y);

/* --- default --- */

// set values to default
unsigned int set_default();

/* --- create --- */

// create field
unsigned int create_field();

/* --- pages --- */

// start
unsigned int page_start();

// game
unsigned int page_game();

// menu
unsigned int page_menu();

// about
unsigned int page_about();

// store
unsigned int page_store();

// map
unsigned int page_map();

// congratulation
unsigned int page_congratulation();

// load
unsigned int page_load();

// save
unsigned int page_save();

/* --- print --- */

unsigned int print();

/* --- functions in read_HID --- */

unsigned int HID_move_miner();

unsigned int HID_TNT();

unsigned int HID_C4();

unsigned int HID_store();

unsigned int HID_load();

unsigned int HID_save();

/* --- read HID --- */

unsigned int read_HID();

/* --- set positions --- */

unsigned int set_positions();

/* --- monster move --- */

unsigned int move_monster_a1();

unsigned int move_monster_b1();

unsigned int move_others();

#define functions_h
#endif
