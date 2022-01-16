//////////////////////////////////////////////////////
// 
// Author:		Oliver Blaser
// 
// Date:		26.12.2015
//
// Description:	Defines for Quid
// 
//////////////////////////////////////////////////////

#ifndef defines_h

#define release_version	"1.5.1"

// window
#define window_width	300
#define window_height	670
#define window_pos_x	50
#define window_pos_y	50

#define field_width		30
#define field_height	37

// cursor
#define cursor_hight	10

// save data
#define file_name		"data.quid"
#define save_number		10

// times * 10 ms
#define t_quid_min		3
#define t_wait_button	3
#define t_attack		3
#define t_move_bar		9

// characters
#define c_bar_solid		219
#define c_bar_move		64	// 178
#define c_bar_break		206
#define c_bar_once		177
#define c_bar_trans		32

#define c_quid			35
#define c_attack		254


// diverses
#define quid_max_jump	13
#define no_bar_max		8

// keys
#define	MSB_short		0x8000

#define KB_move_l		0x41	// a
#define KB_move_l_alt	0x25	// arrow L
#define KB_move_r		0x44	// d
#define KB_move_r_alt	0x27	// arrow R
#define KB_attack		0x20	// space
#define KB_start		0x0D	// enter

#define XI_attack		XINPUT_GAMEPAD_A		// X
#define XI_start		XINPUT_GAMEPAD_START	// options

#define XI_stick_th		7000
#define XI_stick_th_	-7000

// last button
#define but_left		1
#define but_right		2
#define but_attack		3
#define but_start		4

// error codes
#define err_bars		1
#define err_page_print	2
#define err_page_HID	3
#define err_read_f		4
#define err_write_f		5
#define err_open_f	6

// return codes
#define ret_exit		1

// define commands
#define clr_scr				system("cls");
#define clr_char			printf(" ");
#define clr_kbbuf			fflush(stdin);
#define wait_kb				getchar();	// system("pause > dmdat");
#define set_window_default	MoveWindow(GetConsoleWindow(), window_pos_x, window_pos_y, window_width, window_height, 1);
//							MoveWindow(window_handle, x, y, width, height, redraw_window);

#define defines_h
#endif
