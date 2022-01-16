//////////////////////////////////////////////////////
// 
// Author:		Oliver Blaser
// 
// Date:		24.10.2015
//
// Description:	Defines for Diamond Miner
// 
//////////////////////////////////////////////////////

#ifndef defines_h

#define release_version	"1.1.3"

// window
#define window_width	545
#define window_hight	450
#define window_pos_x	50
#define window_pos_y	50

// cursor
#define cursor_hight	10

// save data
#define save_elements	20
#define file_name_len	100
#define c_no_file		45

// thousandth of walls and diamonds
#define tousnd_diamond	10
#define tousnd_wall		450
#define tousnd_TNT		1

// field
#define field_hight		(4 + 50)
#define field_width		(4 + 50)

// field array
#define c_miner			79
#define c_monster_a1	245
#define c_monster_b1	156

#define c_store			35

#define c_diamond		207
#define c_TNT			244
#define c_C4			184

#define c_wall			219
#define c_to_dig		176
#define c_way			32
#define c_slime			126

#define c_error			33

// dialog box
#define dialog_x0		22
#define dialog_y0		2

#define dialog_width	38
#define dialog_hight	21

// borders
#define c_corner		254
#define c_border_ver	186
#define c_border_hor	205

// keys
#define but_up			0x48
#define but_down		0x50
#define but_right		0x4D
#define but_left		0x4B

#define but_enter		0x0D
#define but_esc			0x1B
#define but_space		0x20

#define but_menu		but_esc
#define but_restart		0x72	// r
#define but_exit		0x78	// x
#define but_store		but_enter
#define but_about		0x61	// a
#define but_map			0x6D	// m
#define but_load		0x6C	// l
#define but_save		0x73	// s

#define but_TNT			but_space
#define but_C4			0x63	// c

// store
#define price_TNT		1
#define number_TNT		2

#define price_C4		3
#define number_C4		1

#define price_map		5
#define number_map		1

// return values
#define ret_exit		1
#define ret_restart		2
#define ret_game		3

// error codes
#define err_print		1
#define err_read_HID	2
#define err_pic			3
#define err_open_f		4
#define err_create_f	5
#define err_write_f		6
#define err_read_f		7
#define err_value_name	8
#define err_damaged_f	9

// define commands
#define clr_scr				system("cls");
#define clr_char			printf(" ");
#define clr_kbbuf			fflush(stdin);
#define wait_kb				getchar();	// system("pause > dmdat");
#define set_window_default	MoveWindow(GetConsoleWindow(), window_pos_x, window_pos_y, window_width, window_hight, 1);
//							MoveWindow(window_handle, x, y, width, height, redraw_window);

#define defines_h
#endif
