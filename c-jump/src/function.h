//////////////////////////////////////////////////////
// 
// Author:		Oliver Blaser
// 
// Date:		16.06.2016
//
// Description:	Functions for C Jump
// 
//////////////////////////////////////////////////////

#ifndef functions_h

// includeing libraries
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

////////////////////////////////////////////////////////////////////////////////////////
#include <Xinput.h>
#pragma comment(lib, "XInput.lib")
////////////////////////////////////////////////////////////////////////////////////////

#include <powrprof.h>
#pragma comment(lib, "powrprof.lib")

// includeing files
#include "defines.h"

// class for coordinates
class coordinate {
public:
	unsigned int draw;
	unsigned int quid;
	unsigned int attack;
	unsigned int move_bar;
};

////////////////////////////////////////////////////////////////////////////////////////
// controller class
class XboxController {
private:
	XINPUT_STATE conState;
public:
	int conNum;
	XboxController(int f_playerNum);
	XINPUT_STATE getState();
	bool connected();
	void vibrate(int f_L_val, int f_R_val);
};

void delete_con();
////////////////////////////////////////////////////////////////////////////////////////

// CPU informations
typedef struct _PROCESSOR_POWER_INFORMATION {
	ULONG  Number;
	ULONG  MaxMhz;
	ULONG  CurrentMhz;
	ULONG  MhzLimit;
	ULONG  MaxIdleState;
	ULONG  CurrentIdleState;
} PROCESSOR_POWER_INFORMATION, *PPROCESSOR_POWER_INFORMATION;

unsigned int get_CPU_freq(unsigned int f_CPU_num);

/* --- std func --- */

// cursor settings function
unsigned int set_cursor(bool f_state, int f_size);

// set cursor to x y
unsigned int gotoxy(unsigned int f_goto_x, unsigned int f_goto_y);

// print on x y
unsigned int printxy(char f_string[], unsigned int f_print_x, unsigned int f_print_y);

// error
unsigned int error(unsigned int f_error_nr);

// print pic
unsigned int print_pic_quid_text(unsigned int f_print_x, unsigned int f_print_y);
unsigned int print_pic(unsigned int f_select, unsigned int f_print_x, unsigned int f_print_y);
unsigned int print_pic_quid(unsigned int f_print_x, unsigned int f_print_y);

// print counters
unsigned int print_counters(bool f_select);

// load file
unsigned int load_file();

// save file
unsigned int save_file();

// create a bar-structure in the field array
unsigned int create_bar(unsigned int f_select, unsigned int f_x, unsigned int f_y);

// start conditions
unsigned int start();

// set values to default
unsigned int set_default();

// read HID
unsigned int read_HID();

// quid speed
unsigned int quid_speed(unsigned int f_jump_cnt);

// shift down the array and create new bars
unsigned int shift_down();

// set quids x position
unsigned int quid_overflow();

// set positions
unsigned int set_positions();

// pages
unsigned int page_start();
unsigned int page_game();

// print page
unsigned int print();

// 10ms "interrupt"
unsigned int interrupt_10ms();

// handle with time
unsigned int time_handler();

#define functions_h
#endif
