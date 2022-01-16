//////////////////////////////////////////////////////
// 
// Author:		Oliver Blaser
// 
// Date:		05.10.2015
//
// Description:	Defines for Diamond Miner
// 
//////////////////////////////////////////////////////

#ifndef defines_h

// define commands
#define clr_scr		system("cls");
#define clr_char	printf(" ");
#define clr_kbbuf	fflush(stdin);
#define wait_kb		system("pause > null");

// window
#define window_width	545
#define window_hight	450
#define window_pos_x	100
#define window_pos_y	100

// cursor
#define cursor_hight	10

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
#define c_to_explore	176
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

#define but_menu		0x6D	// m
#define but_restart		0x72	// r
#define but_exit		0x78	// x
#define but_store		but_enter
#define but_about		0x61	// a

#define but_TNT			but_space
#define but_C4			0x63	// c

// store
#define price_TNT		1
#define number_TNT		2

#define price_C4		3
#define number_C4		1

// return values
#define ret_exit		1
#define ret_restart		2
#define ret_game		3

// error codes
#define error_c_print	001
#define error_c_r_HID	002

#define defines_h
#endif

/*
Sounds:

C:\Windows\Media
ir_end		monster
tada		congratulations

C:\Windows\Media\Garden
Ping		diamond


*/
