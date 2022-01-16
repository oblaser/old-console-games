//////////////////////////////////////////////////////
// 
// Author:		Oliver Blaser
// 
// Date:		24.10.2015
//
// Description:	Functions for Diamond Miner
// 
//////////////////////////////////////////////////////

// includeing function.h
#include "function.h"

// coordinate objects
coordinate x;
coordinate y;

// file management
FILE * fp;

// controller object
XboxController * controller1;

/* --- variables --- */

// controller enable
bool con_en;
bool con_delay_en;

// save data
unsigned int save_data[save_elements];

// filename for save
char save_file_name[file_name_len];

// monster enable
bool monster_a1_en;
bool monster_b1_en;

// print once
bool print_once_game;

// page selector
unsigned int page;

// keyboardbutton
unsigned char kbbut;

// counter
unsigned int cnt_diamond;
unsigned int cnt_TNT;
unsigned int cnt_C4;
unsigned int cnt_map;

unsigned int total_diamond;

// field
unsigned char field[field_width][field_hight];

/* --- pictures --- */

// monster pic big
unsigned char pic_monster_big[8][9] = {
	{  32,  32, 186,  32, 186,  32, 186,  32,  32 },
	{  32, 177, 186, 177, 186, 177, 186, 177,  32 },
	{  32, 177, 177, 177, 186, 177, 177, 177,  32 },
	{ 177, 177,  79, 177, 177, 177,  79, 177, 177 },
	{  32, 177, 177, 177, 177, 177, 177, 177,  32 },
	{ 177, 177, 177,  32,  32,  32, 177, 177, 177 },
	{ 177,  32, 200, 205,  32, 205, 188,  32, 177 },
	{ 177,  32,  32,  32,  32,  32,  32,  32, 177 }
};

// pickax pic big
unsigned char pic_pickax_big[12][11] = {
	{  32,  32,  32,  95,  95,  95,  32,  32,  32,  32,  32 },
	{  32,  32,  60,  95,  95,  32,  92,  32,  32,  32,  32 },
	{  32,  32,  32,  32,  32,  92,  32,  92,  47, 179,  32 },
	{  32,  32,  32,  32,  32,  32,  92,  32,  92,  47,  32 },
	{  32,  32,  32,  32,  32,  32,  47,  92,  32,  92,  32 },
	{  32,  32,  32,  32,  32,  47,  32,  47,  92,  32,  92 },
	{  32,  32,  32,  32,  47,  32,  47,  32,  32,  92, 179 },
	{  32,  32,  32,  47,  32,  47,  32,  32,  32, 179, 179 },
	{  32,  32,  47,  32,  47,  32,  32,  32,  32,  92,  47 },
	{  32,  47,  32,  47,  32,  32,  32,  32,  32,  32,  32 },
	{  47,  32,  47,  32,  32,  32,  32,  32,  32,  32,  32 },
	{ 179,  47,  32,  32,  32,  32,  32,  32,  32,  32,  32 }
};

// diamond pic big
unsigned char pic_diamond_big[20][16] = {
	{  32,  32,  32,  32,  95,  95,  95,  95,  95,  95,  95,  95,  32,  32,  32,  32 },
	{  32,  32,  32,  47,  32,  32,  47,  32,  32,  92,  32,  32,  92,  32,  32,  32 },
	{  32,  32,  47,  32,  32,  47,  32,  32,  32,  32,  92,  32,  32,  92,  32,  32 },
	{  32,  47,  32,  32,  47,  32,  32,  32,  32,  32,  32,  92,  32,  32,  92,  32 },
	{  47,  95,  95,  47,  95,  95,  95,  95,  95,  95,  95,  95,  92,  95,  95,  92 },
	{  92,  32,  32,  92,  32,  32,  32,  32,  32,  32,  32,  32,  47,  32,  32,  47 },
	{  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32 },
	{  32,  92,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  47,  32 },
	{  32,  32,  32,  32,  92,  32,  32,  32,  32,  32,  32,  47,  32,  32,  32,  32 },
	{  32,  32,  92,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  47,  32,  32 },

	{  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32 },
	{  32,  32,  32,  92,  32,  92,  32,  32,  32,  32,  47,  32,  47,  32,  32,  32 },
	{  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32 },
	{  32,  32,  32,  32,  92,  32,  32,  32,  32,  32,  32,  47,  32,  32,  32,  32 },
	{  32,  32,  32,  32,  32,  32,  92,  32,  32,  47,  32,  32,  32,  32,  32,  32 },
	{  32,  32,  32,  32,  32,  92,  32,  32,  32,  32,  47,  32,  32,  32,  32,  32 },
	{  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32 },
	{  32,  32,  32,  32,  32,  32,  92,  92,  47,  47,  32,  32,  32,  32,  32,  32 },
	{  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32 },
	{  32,  32,  32,  32,  32,  32,  32,  92,  47,  32,  32,  32,  32,  32,  32,  32 },
};

// text DIAMOND
unsigned char pic_diamond_text[5][28] = {
	{ 219, 219,  32,  32, 219,  32,  32, 219,  32,  32, 219,  32,  32,  32, 219,  32,  32, 219,  32,  32, 219,  32,  32, 219,  32, 219, 219,  32 },
	{ 219,  32, 219,  32, 219,  32, 219,  32, 219,  32, 219, 219,  32, 219, 219,  32, 219,  32, 219,  32, 219, 219,  32, 219,  32, 219,  32, 219 },
	{ 219,  32, 219,  32, 219,  32, 219,  32, 219,  32, 219, 219, 219, 219, 219,  32, 219,  32, 219,  32, 219,  32, 219, 219,  32, 219,  32, 219 },
	{ 219,  32, 219,  32, 219,  32, 219, 219, 219,  32, 219,  32, 219,  32, 219,  32, 219,  32, 219,  32, 219,  32, 219, 219,  32, 219,  32, 219 },
	{ 219, 219,  32,  32, 219,  32, 219,  32, 219,  32, 219,  32,  32,  32, 219,  32,  32, 219,  32,  32, 219,  32,  32, 219,  32, 219, 219,  32 },
};

// text MINER
unsigned char pic_miner_text[5][20] = {
	{ 219,  32,  32,  32, 219,  32, 219,  32, 219,  32,  32, 219,  32, 219, 219, 219,  32, 219, 219,  32 },
	{ 219, 219,  32, 219, 219,  32, 219,  32, 219, 219,  32, 219,  32, 219,  32,  32,  32, 219,  32, 219 },
	{ 219, 219, 219, 219, 219,  32, 219,  32, 219,  32, 219, 219,  32, 219, 219,  32,  32, 219, 219,  32 },
	{ 219,  32, 219,  32, 219,  32, 219,  32, 219,  32, 219, 219,  32, 219,  32,  32,  32, 219,  32, 219 },
	{ 219,  32,  32,  32, 219,  32, 219,  32, 219,  32,  32, 219,  32, 219, 219, 219,  32, 219,  32, 219 },
};

// store pic
unsigned char pic_store[3][3] = {
	{  32,  32,  32 },
	{  47, 238,  92 },
	{ 179, 186, 179 }
};

// monster one
unsigned char pic_monster_a[3][3] = {
	{  32,  95,  32 },
	{  47,  79,  92 },
	{ 193, 238, 193 }
};

// monster two
unsigned char pic_monster_b[3][3] = {
	{  32, 186,  32 },
	{  32,  79,  32 },
	{  47, 238,  92 }
};

// miner
unsigned char pic_miner[3][3] = {
	{  32,  79,  32 },
	{ 196, 197, 196 },
	{  47, 238,  92 }
};

// wall
unsigned char pic_wall[3][3] = {
	{ 219, 219, 219 },
	{ 219, 219, 219 },
	{ 219, 219, 219 }
};

// way
unsigned char pic_way[3][3] = {
	{  32,  32,  32 },
	{  32,  32,  32 },
	{  32,  32,  32 }
};

// TNT
unsigned char pic_TNT[3][3] = {
	{ 207, 207, 207 },
	{  84,  78,  84 },
	{ 207, 207, 207 }
};

// diamond
unsigned char pic_diamond[3][3] = {
	{  47, 238,  92 },
	{  92,  32,  47 },
	{  32,  86,  32 }
};

// error
unsigned char pic_error[3][3] = {
	{ 33,  33,  33 },
	{ 33,  63,  33 },
	{ 33,  33,  33 }
};

// to dig
unsigned char pic_to_dig[3][3] = {
	{ 176, 176, 176 },
	{ 176, 176, 176 },
	{ 176, 176, 176 }
};

// slime
unsigned char pic_slime[3][3] = {
	{ 126, 126, 126 },
	{ 126, 126, 126 },
	{ 126, 126, 126 }
};

// C4
unsigned char pic_C4[3][3] = {
	{ 35,  35,  35 },
	{ 35,  67,  52 },
	{ 35,  35,  35 }
};

// map 
unsigned char pic_map[3][3] = {
	{ 195, 194, 196 },
	{ 192, 197, 191 },
	{ 218, 217, 179 }
};

/*
// 
unsigned char pic_[3][3] = {
	{  32,  32,  32 },
	{  32,  32,  32 },
	{  32,  32,  32 }
};
*/

/* --- functions --- */

// functions of controller class
XboxController::XboxController(int f_playerNum) {
	conNum = f_playerNum - 1;
}

XINPUT_STATE XboxController::getState() {

	ZeroMemory(&conState, sizeof(XINPUT_STATE));

	XInputGetState(conNum, &conState);

	return conState;
}

bool XboxController::connected() {

	ZeroMemory(&conState, sizeof(XINPUT_STATE));

	DWORD f_result = XInputGetState(conNum, &conState);

	if (f_result == ERROR_SUCCESS) return 1;
	else return 0;
}

void XboxController::vibrate(int f_L_val, int f_R_val) {

	XINPUT_VIBRATION vibration;

	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	vibration.wLeftMotorSpeed = f_L_val;
	vibration.wRightMotorSpeed = f_R_val;

	XInputSetState(conNum, &vibration);
}

void delete_con() {

	delete(controller1);
}

/* --- std func --- */

// cursor settings function
unsigned int set_cursor(bool f_state, int f_size) {

	CONSOLE_CURSOR_INFO cursor_info;
	HANDLE  cursor_out;

	cursor_info.bVisible = f_state;

	if (f_state) cursor_info.dwSize = f_size;
	else cursor_info.dwSize = 1;

	cursor_out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(cursor_out, &cursor_info);

	return 0;
}

// set cursor to x y
unsigned int gotoxy(unsigned int f_goto_x, unsigned int f_goto_y) {

	COORD coord;

	coord.X = f_goto_x;
	coord.Y = f_goto_y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	return 0;
}

// print on x y
unsigned int printxy(char f_string[], unsigned int f_print_x, unsigned int f_print_y) {

	gotoxy(f_print_x, f_print_y);
	
	printf(f_string);

	return 0;
}

// convert kb-scancode to decimal
unsigned int convert_kb_dec(unsigned char f_kbbut) {

	switch (f_kbbut) {

	case 0x30:
		return 0;
		break;

	case 0x31:
		return 1;
		break;

	case 0x32:
		return 2;
		break;

	case 0x33:
		return 3;
		break;

	case 0x34:
		return 4;
		break;

	case 0x35:
		return 5;
		break;

	case 0x36:
		return 6;
		break;

	case 0x37:
		return 7;
		break;

	case 0x38:
		return 8;
		break;

	case 0x39:
		return 9;
		break;

	default:
		return 99;
		break;
	}
}

// clear dialog box
unsigned int clr_dialog_box() {

	for (x.draw = dialog_x0; x.draw < dialog_x0 + dialog_width; x.draw++) {
		for (y.draw = dialog_y0; y.draw < dialog_y0 + dialog_hight; y.draw++) {
			printxy(" ", x.draw, y.draw);
		}
	}

	return 0;
}

// error
unsigned int error(unsigned int f_error_nr) {

	while (1) {

		clr_scr;

		gotoxy(5, 5);
		printf("Error %d", f_error_nr);
		
		printxy("Please contact the developper.", 5, 7);
		
		getchar();
	}
}

/* --- extern files --- */

unsigned int create_file(char f_file_name[]) {

	if (f_file_name[0] != c_no_file) {

		// fill data array
		for (int i = 0; i < save_elements; i++) save_data[i] = 0;

		// create file
		if (fopen_s(&fp, f_file_name, "w") == 0) {

			// write in file
			if (fwrite(save_data, sizeof(int), save_elements, fp) != save_elements) error(err_create_f);

			// close file
			fclose(fp);
		}
		else error(err_open_f);
	}

	return 0;
}

unsigned int load_value(char f_value_name[], char f_file_name[]) {

	if (f_file_name[0] != c_no_file) {

		// open file to read
		if (fopen_s(&fp, f_file_name, "r") == 0) {

			// read file
			if (fread(save_data, sizeof(int), save_elements, fp) != save_elements) error(err_read_f);

			// close file
			fclose(fp);
		}
		else {

			create_file(f_file_name);

			// open the new file to read
			if (fopen_s(&fp, f_file_name, "r") == 0) {

				// read file
				if (fread(save_data, sizeof(int), save_elements, fp) != save_elements) error(err_read_f);

				// close file
				fclose(fp);
			}
			else {
				error(err_read_f);
			}
		}

		for (int i = 0; i < 4; i++) {
			if (save_data[i] != save_data[i + 4] / 2) error(err_damaged_f);
		}

		if (f_value_name == "diamond") return save_data[0];
		if (f_value_name == "TNT") return save_data[1];
		if (f_value_name == "C4") return save_data[2];
		if (f_value_name == "map") return save_data[3];
		else error(err_value_name);
	}

	return 0;
}

unsigned int save_value(char f_file_name[]) {

	if (f_file_name[0] != c_no_file) {

		save_data[0] = cnt_diamond;
		save_data[1] = cnt_TNT;
		save_data[2] = cnt_C4;
		save_data[3] = cnt_map;

		for (int i = 0; i < 4; i++) {
			save_data[i + 4] = save_data[i] * 2;
		}

		// open file
		if (fopen_s(&fp, f_file_name, "w") == 0) {

			// write in file
			if (fwrite(save_data, sizeof(int), save_elements, fp) != save_elements) error(err_write_f);

			// close file
			fclose(fp);
		}
		else error(err_open_f);
	}

	return 0;
}

/* --- print pics --- */

unsigned int print_pic_monster_big(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 8; y.draw++) {
		for (x.draw = 0; x.draw < 9; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_monster_big[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_pickax_big(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 12; y.draw++) {
		for (x.draw = 0; x.draw < 11; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_pickax_big[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_diamond_big(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 20; y.draw++) {
		for (x.draw = 0; x.draw < 16; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_diamond_big[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_diamond_text(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 5; y.draw++) {
		for (x.draw = 0; x.draw < 28; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_diamond_text[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_miner_text(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 5; y.draw++) {
		for (x.draw = 0; x.draw < 20; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_miner_text[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_store(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 3; y.draw++) {
		for (x.draw = 0; x.draw < 3; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_store[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_monster_a(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 3; y.draw++) {
		for (x.draw = 0; x.draw < 3; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_monster_a[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_monster_b(unsigned int f_print_x, unsigned int f_print_y) {

for (y.draw = 0; y.draw < 3; y.draw++) {
	for (x.draw = 0; x.draw < 3; x.draw++) {
		gotoxy(x.draw + f_print_x, y.draw + f_print_y);
		printf("%c", pic_monster_b[y.draw][x.draw]);
	}
}

return 0;
}

unsigned int print_pic_miner(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 3; y.draw++) {
		for (x.draw = 0; x.draw < 3; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_miner[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_wall(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 3; y.draw++) {
		for (x.draw = 0; x.draw < 3; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_wall[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_way(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 3; y.draw++) {
		for (x.draw = 0; x.draw < 3; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_way[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_TNT(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 3; y.draw++) {
		for (x.draw = 0; x.draw < 3; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_TNT[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_diamond(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 3; y.draw++) {
		for (x.draw = 0; x.draw < 3; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_diamond[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_error(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 3; y.draw++) {
		for (x.draw = 0; x.draw < 3; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_error[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_to_dig(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 3; y.draw++) {
		for (x.draw = 0; x.draw < 3; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_to_dig[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_slime(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 3; y.draw++) {
		for (x.draw = 0; x.draw < 3; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_slime[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_C4(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 3; y.draw++) {
		for (x.draw = 0; x.draw < 3; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_C4[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_map(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 3; y.draw++) {
		for (x.draw = 0; x.draw < 3; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_map[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_select(unsigned int f_pic, unsigned int f_print_x, unsigned int f_print_y) {

	// calculate effective pic-pos
	f_print_x = (f_print_x + 1) * 3;
	f_print_y = (f_print_y + 1) * 3 - 1;

	// print pic in coution to value in field[][]
	switch (f_pic) {

	case c_miner:
		print_pic_miner(f_print_x, f_print_y);
		break;

	case c_monster_a1:
		print_pic_monster_a(f_print_x, f_print_y);
		break;

	case c_monster_b1:
		print_pic_monster_b(f_print_x, f_print_y);
		break;

	case c_diamond:
		print_pic_diamond(f_print_x, f_print_y);
		break;

	case c_TNT:
		print_pic_TNT(f_print_x, f_print_y);
		break;

	case c_wall:
		print_pic_wall(f_print_x, f_print_y);
		break;

	case c_way:
		print_pic_way(f_print_x, f_print_y);
		break;

	case c_to_dig:
		print_pic_to_dig(f_print_x, f_print_y);
		break;

	case c_slime:
		print_pic_slime(f_print_x, f_print_y);
		break;

	case c_C4:
		print_pic_C4(f_print_x, f_print_y);
		break;

	case c_store:
		print_pic_store(f_print_x, f_print_y);
		break;

	default:
		print_pic_error(f_print_x, f_print_y);
		error(err_pic);
		break;
	}

	return 0;
}

unsigned int print_counters() {

	gotoxy(4, 19);
	if (cnt_diamond < 10) printf("%d%c", cnt_diamond, c_border_hor);
	else printf("%d", cnt_diamond);

	gotoxy(8, 19);
	if (cnt_TNT < 10) printf("%d%c", cnt_TNT, c_border_hor);
	else printf("%d", cnt_TNT);

	gotoxy(12, 19);
	if (cnt_C4 < 10) printf("%d%c", cnt_C4, c_border_hor);
	else printf("%d", cnt_C4);

	gotoxy(16, 19);
	if (cnt_map < 10) printf("%d%c", cnt_map, c_border_hor);
	else printf("%d", cnt_map);

	return 0;
}

unsigned int print_border() {

	for (x.draw = 0; x.draw < 100; x.draw++) {
		for (y.draw = 0; y.draw < 25; y.draw++) {

			gotoxy(x.draw, y.draw);

			// corner
			if ((y.draw == 1 && (x.draw == 2 || x.draw == 18 || x.draw == 21 || x.draw == 60)) ||
				(y.draw == 17 && (x.draw == 2 || x.draw == 18)) ||
				(y.draw == 19 && (x.draw == 2 || x.draw == 6 || x.draw == 10 || x.draw == 14 || x.draw == 18)) ||
				(y.draw == 23 && (x.draw == 2 || x.draw == 6 || x.draw == 10 || x.draw == 14 || x.draw == 18 || x.draw == 21 || x.draw == 60))
				) {

				printf("%c", c_corner);
			}

			// border horizontal
			if ((y.draw == 1 && ((x.draw > 2 && x.draw < 18) || (x.draw > 21 && x.draw < 60))) ||
				(y.draw == 17 && (x.draw > 2 && x.draw < 18)) ||
				(y.draw == 19 && ((x.draw > 2 && x.draw < 6) || (x.draw > 6 && x.draw < 10) || (x.draw > 10 && x.draw < 14) || (x.draw > 14 && x.draw < 18))) ||
				(y.draw == 23 && ((x.draw > 2 && x.draw < 6) || (x.draw > 6 && x.draw < 10) || (x.draw > 10 && x.draw < 14) || (x.draw > 14 && x.draw < 18) || (x.draw > 21 && x.draw < 60)))
				) {

				printf("%c", c_border_hor);
			}

			// border vertical
			if ((x.draw == 2 && ((y.draw >  1 && y.draw < 17) || (y.draw > 19 && y.draw < 23))) ||
				(x.draw == 6 && (y.draw > 19 && y.draw < 23)) ||
				(x.draw == 10 && (y.draw > 19 && y.draw < 23)) ||
				(x.draw == 14 && (y.draw > 19 && y.draw < 23)) ||
				(x.draw == 18 && ((y.draw >  1 && y.draw < 17) || (y.draw > 19 && y.draw < 23))) ||
				(x.draw == 21 && (y.draw >  1 && y.draw < 23)) ||
				(x.draw == 60 && (y.draw >  1 && y.draw < 23))
				) {

				printf("%c", c_border_ver);
			}
		}
	}

	print_pic_diamond(3, 20);
	print_pic_TNT(7, 20);
	print_pic_C4(11, 20);
	print_pic_map(15, 20);

	return 0;
}

/* --- default --- */

// set values to default
unsigned int set_default() {

	controller1 = new XboxController(1);

	// turn off cursor
	set_cursor(0, cursor_hight);

	// set color
	//system("color 06");

	// window size and position
	set_window_default;

	// page default
	page = 'star';

	// print once
	print_once_game = 1;

	// miner position
	x.start_pos = field_width / 2;
	y.start_pos = field_hight / 2;

	x.miner = x.start_pos;
	y.miner = y.start_pos;

	// set window title
	system("title Diamond Miner");

	// clear counters
	cnt_diamond = 0;
	cnt_TNT = 0;
	cnt_C4 = 0;
	cnt_map = 0;

	// monster enable
	monster_a1_en = 1;
	monster_b1_en = 1;

	// actual file
	for (int i = 0; i < file_name_len; i++) save_file_name[i] = 0;

	return 0;
}

/* --- create --- */

// create field
unsigned int create_field() {

	// initialisize random function
	time_t f_rand;
	time(&f_rand);
	srand((unsigned int)f_rand);

	// to dig
	for (x.draw = 0; x.draw < field_width; x.draw++) {
		for (y.draw = 0; y.draw < field_hight; y.draw++) {
			field[x.draw][y.draw] = c_to_dig;
		}
	}

	// random TNT
	for (int i = 0; i < (field_hight * field_width / 1000 * tousnd_TNT); i++) {
		field[rand() % (field_width - 3) + 2][rand() % (field_hight - 3) + 2] = c_TNT;
	}

	// random walls
	for (int i = 0; i < (field_hight * field_width / 1000 * tousnd_wall); i++) {
		field[rand() % (field_width - 3) + 2][rand() % (field_hight - 3) + 2] = c_wall;
	}

	// random monsters
	x.monster_a1 = rand() % (field_width - 3) + 2;
	y.monster_a1 = rand() % (field_hight - 3) + 2;

	field[x.monster_a1][y.monster_a1] = c_monster_a1;

	x.monster_b1 = rand() % (field_width - 3) + 2;
	y.monster_b1 = rand() % (field_hight - 3) + 2;

	field[x.monster_b1][y.monster_b1] = c_monster_b1;

	// random diamond
	unsigned int f_x_diamond;
	unsigned int f_y_diamond;

	for (int i = 0; i < (field_hight * field_width / 1000 * tousnd_diamond); i++) {

		f_x_diamond = rand() % (field_width - 3) + 2;
		f_y_diamond = rand() % (field_hight - 3) + 2;

		if (field[f_x_diamond][f_y_diamond] != c_monster_a1 && field[f_x_diamond][f_y_diamond] != c_monster_b1)
			field[f_x_diamond][f_y_diamond] = c_diamond;
	}

	// vertical border
	for (y.draw = 1; y.draw <= field_hight - 2; y.draw++) {
		field[1][y.draw] = c_wall;
		field[field_width - 2][y.draw] = c_wall;
	}

	// horizontal border
	for (x.draw = 1; x.draw <= field_width - 2; x.draw++) {
		field[x.draw][1] = c_wall;
		field[x.draw][field_hight - 2] = c_wall;
	}

	// fill outside with c_way
	for (x.draw = 0; x.draw < field_width; x.draw++) {
		field[x.draw][0] = c_way;
		field[x.draw][field_hight - 1] = c_way;
	}

	for (y.draw = 0; y.draw < field_hight; y.draw++) {
		field[0][y.draw] = c_way;
		field[field_width - 1][y.draw] = c_way;
	}

	// no walls around start position
	for (x.draw = x.start_pos - 1; x.draw <= x.start_pos + 1; x.draw++) {
		for (y.draw = y.start_pos - 1; y.draw <= y.start_pos + 1; y.draw++) {
			if (field[x.draw][y.draw] == c_wall && x.start_pos > 2 && x.start_pos < field_width - 3 && y.start_pos > 2 && y.start_pos < field_hight - 3)
				field[x.draw][y.draw] = c_to_dig;
		}
	}

	// stores
	field[x.start_pos][4] = c_store;
	field[x.start_pos][field_hight - 5] = c_store;
	field[4][y.start_pos] = c_store;
	field[field_width - 5][y.start_pos] = c_store;

	// count total diamonds
	for (x.draw = 0; x.draw < field_width; x.draw++) {
		for (y.draw = 0; y.draw < field_hight; y.draw++) {
			if (field[x.draw][y.draw] == c_diamond) total_diamond++;
		}
	}

	return 0;
}

/* --- pages --- */

// start
unsigned int page_start() {

	unsigned char f_but = 0;

	clr_scr;

	print_pic_diamond_text(4, 1);
	print_pic_miner_text(37, 1);

	print_pic_pickax_big(10, 7);

	print_pic_monster_big(35, 10);

	printxy("Press Enter to start in keyboard mode", 4, 21);
	printxy("Press Space to start in controller mode", 4, 23);

	clr_kbbuf;
	
	f_but = _getch();

	switch (f_but) {

	case but_kb_mode:
		con_en = 0;
		break;

	case but_con_mode:
		con_en = 1;
		break;

	default:
		break;
	}

	clr_scr;

	print_border();

	page = 'game';
	
	return 0;
}

// game
unsigned int page_game() {

	// print once
	if (print_once_game) {

		clr_scr;

		print_border();

		if(con_en) printxy("Press start to view menu", dialog_x0 + 1, dialog_y0 + 1);
		else printxy("Press Esc to view menu", dialog_x0 + 1, dialog_y0 + 1);

		gotoxy(dialog_x0 + 1, dialog_y0 + dialog_hight - 4);
		printf("Actual file: %s", save_file_name);

		print_once_game = 0;
	}
	
	// print field
	int a = x.miner - 2;
	int b = y.miner - 2;
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			print_pic_select(field[a + i][b + j], i, j);
		}
	}
	
	print_counters();

	// print miner coordinates
	
	gotoxy(dialog_x0 + 1, dialog_y0 + dialog_hight - 1);
	if (x.miner - 1 < 10) printf("X:  %d", x.miner - 1);
	else printf("X: %d", x.miner - 1);

	gotoxy(dialog_x0 + 8, dialog_y0 + dialog_hight - 1);
	if ((field_hight - 4) - (y.miner - 2) < 10) printf("Y:  %d", (field_hight - 4) - (y.miner - 2));
	else printf("Y: %d", (field_hight - 4) - (y.miner - 2));

	// to scroll left
	printxy(" ", 0, 0);

	return 0;
}

/*
// print field array
unsigned int page_game() {

	for (x.draw = 0; x.draw < field_width; x.draw++) {
		for (y.draw = 0; y.draw < field_hight; y.draw++) {
			gotoxy(x.draw, y.draw);
			printf("%c", field[x.draw][y.draw]);
		}
	}

	gotoxy(0, 0);
	printf("%d", cnt_diamond);

	gotoxy(5, 0);
	printf("%d", cnt_TNT);

	gotoxy(10, 0);
	printf("%d", cnt_C4);

	return 0;
}
*/

// menu
unsigned int page_menu() {

	clr_dialog_box();

	printxy("Press R to restart", dialog_x0 + 1, dialog_y0 + 1);

	printxy("Press S to save game", dialog_x0 + 1, dialog_y0 + 3);

	printxy("Press L to load game", dialog_x0 + 1, dialog_y0 + 5);
	
	printxy("Press A to view about", dialog_x0 + 1, dialog_y0 + 8);

	printxy("Press X to exit", dialog_x0 + 1, dialog_y0 + 10);

	

	printxy("Return with Esc", dialog_x0 + 1, dialog_y0 + dialog_hight - 1);

	return 0;
}

// about
unsigned int page_about() {

	clr_dialog_box();

	gotoxy(dialog_x0 + 1, dialog_y0 + 1);
	printf("Diamond Miner %s", release_version);

	printxy("Controlls:", dialog_x0 + 1, dialog_y0 + 3);
	printxy("move  WASD   stick l", dialog_x0 + 1, dialog_y0 + 4);
	printxy("move  arrows DPAD", dialog_x0 + 1, dialog_y0 + 5);
	printxy("TNT   Space  X", dialog_x0 + 1, dialog_y0 + 6);
	printxy("C4    C      B", dialog_x0 + 1, dialog_y0 + 7);
	printxy("map   M      Y", dialog_x0 + 1, dialog_y0 + 8);
	printxy("store Enter  A", dialog_x0 + 1, dialog_y0 + 9);

	printxy("If you find all diamonds, you will", dialog_x0 + 1, dialog_y0 + 12);
	printxy("win one C4.", dialog_x0 + 1, dialog_y0 + 13);

	printxy("Return with Esc", dialog_x0 + 1, dialog_y0 + dialog_hight - 1);

	return 0;
}

// store
unsigned int page_store() {

	unsigned char f_line;

	print_pic_select(c_store, 2, 2);

	clr_dialog_box();

	f_line = 1;
	printxy("Pos", dialog_x0 + 1, dialog_y0 + f_line);
	printxy("Item", dialog_x0 + 6, dialog_y0 + f_line);
	printxy("Price", dialog_x0 + 20, dialog_y0 + f_line);

	// 1 TNT
	f_line = 3;

	printxy("1", dialog_x0 + 1, dialog_y0 + f_line);

	gotoxy(dialog_x0 + 6, dialog_y0 + f_line);
	printf("%dx TNT", number_TNT);

	gotoxy(dialog_x0 + 20, dialog_y0 + f_line);
	printf("%dx diamond", price_TNT);

	// 2 C4
	f_line = 4;

	printxy("2", dialog_x0 + 1, dialog_y0 + f_line);

	gotoxy(dialog_x0 + 6, dialog_y0 + f_line);
	printf("%dx C4", number_C4);

	gotoxy(dialog_x0 + 20, dialog_y0 + f_line);
	printf("%dx diamond", price_C4);

	// 3 map
	f_line = 5;

	printxy("3", dialog_x0 + 1, dialog_y0 + f_line);

	gotoxy(dialog_x0 + 6, dialog_y0 + f_line);
	printf("%dx map", number_map);

	gotoxy(dialog_x0 + 20, dialog_y0 + f_line);
	printf("%dx diamond", price_map);

	// instructions
	printxy("Enter the number you want to buy", dialog_x0 + 1, dialog_y0 + dialog_hight - 3);

	printxy("Return with Esc", dialog_x0 + 1, dialog_y0 + dialog_hight - 1);

	print_counters();

	return 0;
}

// map
unsigned int page_map() {

	clr_scr;

	for (x.draw = 0; x.draw < field_width; x.draw++) {
		for (y.draw = 0; y.draw < field_hight; y.draw++) {
			gotoxy(x.draw + 5, y.draw + 1);

			if (field[x.draw][y.draw] == c_way) printf("%c", c_way);
			if (field[x.draw][y.draw] == c_wall) printf("%c", c_wall);
			if (field[x.draw][y.draw] == c_miner) printf("%c", c_miner);
			else printf("%c", c_to_dig);
		}
	}

	for (y.draw = 0; y.draw < field_hight; y.draw++) {
		printxy(" ", x.draw + 5, y.draw + 1);
	}

	return 0;
}

// congratulation
unsigned int page_congratulation() {

	MoveWindow(GetConsoleWindow(), window_pos_x, window_pos_y, 545, 560, 1);

	cnt_C4 += 1;

	if (save_file_name[0] == 0) save_file_name[0] = 'x';

	save_value(save_file_name);

	clr_scr;

	printxy("Congratulation!", 24, 2);
	printxy("You've found all diamonds and won one C4", 19, 4);
	
	print_pic_diamond_big(23, 6);

	printxy("Press X to exit", 3, 25);
	printxy("Press R to restart", 3, 27);

	gotoxy(3, 30);
	printf("Progress saved in file %s", save_file_name);

	return 0;
}

// load
unsigned int page_load() {

	clr_dialog_box();

	printxy("Load file:", dialog_x0 + 1, dialog_y0 + 1);

	printxy("Confirm with Enter", dialog_x0 + 1, dialog_y0 + 3);

	printxy("Current progress will be lost!", dialog_x0 + 1, dialog_y0 + 5);

	//printxy("", dialog_x0 + 1, dialog_y0 + 0);

	gotoxy(dialog_x0 + 1, dialog_y0 + dialog_hight - 1);
	printf("Return by enter %c", c_no_file);

	return 0;
}

// save
unsigned int page_save() {

	clr_dialog_box();

	printxy("Save to file:", dialog_x0 + 1, dialog_y0 + 1);
	gotoxy(dialog_x0 + 1, dialog_y0 + 2);
	printf("(max. %d letters)", file_name_len - 1);

	printxy("Confirm with Enter", dialog_x0 + 1, dialog_y0 + 4);

	//printxy("", dialog_x0 + 1, dialog_y0 + 0);

	gotoxy(dialog_x0 + 1, dialog_y0 + dialog_hight - 1);
	printf("Return by enter %c", c_no_file);

	return 0;
}

/* --- print --- */

// print page
unsigned int print() {

	// set window size
	if (page == 'map') MoveWindow(GetConsoleWindow(), window_pos_x, window_pos_y, 545, 950, 1);
	else set_window_default;

	switch (page) {

	case 'star':
		page_start();
		break;

	case 'game':
		page_game();
		break;

	case 'menu':
		page_menu();
		break;

	case 'abot':
		page_about();
		break;

	case 'stor':
		page_store();
		break;

	case 'cong':
		page_congratulation();
		break;

	case 'map':
		page_map();
		break;

	case 'load':
		page_load();
		break;

	case 'save':
		page_save();
		break;

	default:
		error(err_print);
		break;
	}

	// for better move feeling
	if (con_en) {
		Sleep(print_delay);
		if (con_delay_en) Sleep(con_delay);
	}

	else Sleep(print_delay);

	return 0;
}

/* --- functions in read_HID --- */

unsigned int HID_move_miner() {

	// up
	if (kbbut == but_up || kbbut == 'w') {
		if (y.miner > 1 && field[x.miner][y.miner - 1] != c_wall) y.miner--;
	}

	// down
	if (kbbut == but_down || kbbut == 's') {
		if (y.miner < field_hight - 2 && field[x.miner][y.miner + 1] != c_wall) y.miner++;
	}

	// right
	if (kbbut == but_right || kbbut == 'd') {
		if (x.miner < field_width - 2 && field[x.miner + 1][y.miner] != c_wall) x.miner++;
	}

	// left
	if (kbbut == but_left || kbbut == 'a') {
		if (x.miner > 1 && field[x.miner - 1][y.miner] != c_wall) x.miner--;
	}

	return 0;
}

unsigned int HID_TNT() {

	cnt_TNT--;

	if (field[x.miner - 1][y.miner] == c_diamond) total_diamond--;
	if (field[x.miner + 1][y.miner] == c_diamond) total_diamond--;
	if (field[x.miner][y.miner - 1] == c_diamond) total_diamond--;
	if (field[x.miner][y.miner + 1] == c_diamond) total_diamond--;

	if (x.miner > 2) field[x.miner - 1][y.miner] = c_way;
	if (x.miner < field_width - 3) field[x.miner + 1][y.miner] = c_way;
	if (y.miner > 2) field[x.miner][y.miner - 1] = c_way;
	if (y.miner < field_hight - 3) field[x.miner][y.miner + 1] = c_way;

	return 0;
}

unsigned int HID_C4() {

	cnt_C4--;

	for (unsigned int f_x = x.miner - 2; f_x <= x.miner + 2; f_x++) {
		for (unsigned int f_y = y.miner - 2; f_y <= y.miner + 2; f_y++) {

			if (field[f_x][f_y] == c_monster_a1) monster_a1_en = 0;
			if (field[f_x][f_y] == c_monster_b1) {
				monster_b1_en = 0;
				cnt_diamond += 1;
			}

			if (f_x > 1 && f_x < field_width - 2 && f_y > 1 && f_y < field_hight - 2) field[f_x][f_y] = c_way;
		}
	}

	return 0;
}

unsigned int HID_store() {

	if (convert_kb_dec(kbbut) == 1 && cnt_diamond >= price_TNT) {
		cnt_diamond -= price_TNT;
		cnt_TNT += number_TNT;
	}

	if (convert_kb_dec(kbbut) == 2 && cnt_diamond >= price_C4) {
		cnt_diamond -= price_C4;
		cnt_C4 += number_C4;
	}

	if (convert_kb_dec(kbbut) == 3 && cnt_diamond >= price_map) {
		cnt_diamond -= price_map;
		cnt_map += number_map;
	}

	return 0;
}

unsigned int HID_load() {

	char f_file_name[file_name_len];

	gotoxy(dialog_x0 + 12, dialog_y0 + 1);
	set_cursor(1, cursor_hight);

	scanf_s("%s", f_file_name);

	set_cursor(0, cursor_hight);

	if (f_file_name[0] != c_no_file) {

		for (int i = 0; i < file_name_len; i++) save_file_name[i] = f_file_name[i];

		cnt_diamond = load_value("diamond", f_file_name);
		cnt_TNT = load_value("TNT", f_file_name);
		cnt_C4 = load_value("C4", f_file_name);
		cnt_map = load_value("map", f_file_name);
	}

	print_counters();

	page = 'menu';

	return 0;
}

unsigned int HID_save() {

	char f_file_name[file_name_len];

	gotoxy(dialog_x0 + 15, dialog_y0 + 1);
	set_cursor(1, cursor_hight);

	scanf_s("%s", f_file_name);

	set_cursor(0, cursor_hight);

	if (f_file_name[0] != c_no_file)
		for (int i = 0; i < file_name_len; i++) save_file_name[i] = f_file_name[i];

	save_value(f_file_name);

	page = 'menu';

	return 0;
}

unsigned int HID_controller() {

	con_delay_en = 0;

	while (1) {

		// stick
		if (controller1->getState().Gamepad.sThumbLY > con_stick_th) return but_up;
		if (controller1->getState().Gamepad.sThumbLY < con_stick_th_) return but_down;
		if (controller1->getState().Gamepad.sThumbLX > con_stick_th) return but_right;
		if (controller1->getState().Gamepad.sThumbLX < con_stick_th_) return but_left;

		// buttons
		if (controller1->getState().Gamepad.wButtons & con_menu) return but_menu;
		if (controller1->getState().Gamepad.wButtons & con_store) return but_store;
		if (controller1->getState().Gamepad.wButtons & con_C4) return but_C4;
		if (controller1->getState().Gamepad.wButtons & con_TNT) return but_TNT;
		if (controller1->getState().Gamepad.wButtons & con_map) return but_map;

		if (controller1->getState().Gamepad.wButtons & con_up) {
			con_delay_en = 1;
			return but_up;
		}

		if (controller1->getState().Gamepad.wButtons & con_down) {
			con_delay_en = 1;
			return but_down;
		}

		if (controller1->getState().Gamepad.wButtons & con_right) {
			con_delay_en = 1;
			return but_right;
		}

		if (controller1->getState().Gamepad.wButtons & con_left) {
			con_delay_en = 1;
			return but_left;
		}


	}

	return 0;
}

/* --- read HID --- */

// read HID
unsigned int read_HID() {

	// read kbbutton
	clr_kbbuf;
	if (page != 'save' && page != 'load') {
		if (con_en && (page == 'game' || page == 'map')) kbbut = HID_controller();
		else kbbut = _getch();
	}

	if (page != 'game') print_once_game = 1;

	switch (page) {

	case 'game':

		// move miner
		HID_move_miner();

		// TNT
		if (kbbut == but_TNT && cnt_TNT > 0) {
			HID_TNT();
		}

		// C4
		if (kbbut == but_C4 && cnt_C4 > 0) {
			HID_C4();
		}

		// view map
		if (kbbut == but_map && cnt_map > 0) {
			cnt_map--;
			page = 'map';
		}

		// menu
		if (kbbut == but_menu) {
			page = 'menu';
			return 0;
		}

		// store
		if (kbbut == but_store && (
			(x.miner == x.start_pos && y.miner == 4) || (x.miner == x.start_pos && y.miner == field_hight - 5) ||
			(x.miner == 4 && y.miner == y.start_pos) || (x.miner == field_width - 5 && y.miner == y.start_pos) 
			)) {
			page = 'stor';
			return 0;
		}

		return ret_game;

		break;

	case 'menu':
		
		// return
		if (kbbut == but_esc) page = 'game';

		// about & instructions
		if (kbbut == but_about) page = 'abot';

		// restart
		if (kbbut == but_restart) return ret_restart;

		// exit
		if (kbbut == but_exit) return ret_exit;

		// load
		if (kbbut == but_load) page = 'load';

		// save
		if (kbbut == but_save) page = 'save';

		break;

	case 'abot':

		// return
		if (kbbut == but_esc) page = 'menu';

		break;

	case 'stor':

		// buy
		HID_store();

		// return
		if (kbbut == but_esc) page = 'game';

		break;

	case 'cong':

		// restart
		if (kbbut == but_restart) return ret_restart;

		// exit
		if (kbbut == but_exit) return ret_exit;

		break;

	case 'map':
		page = 'game';
		break;

	case 'load':
		HID_load();
		break;

	case 'save':
		HID_save();
		break;

	default:
		error(err_read_HID);
		break;
	}

	return 0;
}

/* --- set positions --- */

unsigned int set_positions() {

	// stores
	field[x.start_pos][4] = c_store;
	field[x.start_pos][field_hight - 5] = c_store;
	field[4][y.start_pos] = c_store;
	field[field_width - 5][y.start_pos] = c_store;

	// handle monster a1
	if (monster_a1_en) {

		// set monsters
		field[x.monster_a1][y.monster_a1] = c_monster_a1;

		// monster eats diamond
		if (field[x.miner][y.miner] == c_monster_a1 && cnt_diamond >= 1) cnt_diamond -= 1;
	}

	// handle monster a1
	if (monster_b1_en) {

		// set monsters
		field[x.monster_b1][y.monster_b1] = c_monster_b1;

		// monster eats diamond
		if (field[x.miner][y.miner] == c_monster_b1 && cnt_diamond == 1) cnt_diamond -= 1;
		if (field[x.miner][y.miner] == c_monster_b1 && cnt_diamond >= 2) cnt_diamond -= 2;
	}

	// count diamonds
	if (field[x.miner][y.miner] == c_diamond) {
		cnt_diamond++;
		total_diamond--;
	}

	if (total_diamond <= 0) page = 'cong';

	// count TNT
	if (field[x.miner][y.miner] == c_TNT) cnt_TNT++;

	// clear old miner
	switch (kbbut) {

	case but_up:
		if (field[x.miner][y.miner + 1] == c_miner) field[x.miner][y.miner + 1] = c_way;
		break;

	case but_down:
		if (field[x.miner][y.miner - 1] == c_miner) field[x.miner][y.miner - 1] = c_way;
		break;

	case but_right:
		if (field[x.miner - 1][y.miner] == c_miner) field[x.miner - 1][y.miner] = c_way;
		break;

	case but_left:
		if (field[x.miner + 1][y.miner] == c_miner) field[x.miner + 1][y.miner] = c_way;
		break;

	case 'w':
		if (field[x.miner][y.miner + 1] == c_miner) field[x.miner][y.miner + 1] = c_way;
		break;

	case 's':
		if (field[x.miner][y.miner - 1] == c_miner) field[x.miner][y.miner - 1] = c_way;
		break;

	case 'd':
		if (field[x.miner - 1][y.miner] == c_miner) field[x.miner - 1][y.miner] = c_way;
		break;

	case 'a':
		if (field[x.miner + 1][y.miner] == c_miner) field[x.miner + 1][y.miner] = c_way;
		break;

	default:
		break;
	}
	
	// set miner
	field[x.miner][y.miner] = c_miner;

	return 0;
}

/* --- monster move --- */

unsigned int move_monster_a1() {

	// initialisize random function
	time_t f_rand;
	time(&f_rand);
	srand((unsigned int)f_rand);

	// clear old monster
	if (monster_a1_en) field[x.monster_a1][y.monster_a1] = c_slime;

	// move x or y
	if (rand() % 100 + 1 > 50) {

		// move + or -
		if (rand() % 100 + 1 > 50) {
			if (field[x.monster_a1 + 1][y.monster_a1] != c_wall && field[x.monster_a1 + 1][y.monster_a1] != c_diamond &&
				field[x.monster_a1 + 1][y.monster_a1] != c_TNT && field[x.monster_a1 + 1][y.monster_a1] != c_store &&
				x.monster_a1 < field_width - 3) x.monster_a1++;
		}
		else {
			if (field[x.monster_a1 - 1][y.monster_a1] != c_wall && field[x.monster_a1 - 1][y.monster_a1] != c_diamond &&
				field[x.monster_a1 - 1][y.monster_a1] != c_TNT && field[x.monster_a1 - 1][y.monster_a1] != c_store &&
				x.monster_a1 > 2) x.monster_a1--;
		}
	}
	else {

		// move + or -
		if (rand() % 100 + 1 > 50) {
			if (field[x.monster_a1][y.monster_a1 + 1] != c_wall && field[x.monster_a1][y.monster_a1 + 1] != c_diamond &&
				field[x.monster_a1][y.monster_a1 + 1] != c_TNT && field[x.monster_a1][y.monster_a1 + 1] != c_store &&
				y.monster_a1 < field_hight - 3) y.monster_a1++;
		}
		else {
			if (field[x.monster_a1][y.monster_a1 - 1] != c_wall && field[x.monster_a1][y.monster_a1 - 1] != c_diamond &&
				field[x.monster_a1][y.monster_a1 - 1] != c_TNT && field[x.monster_a1][y.monster_a1 - 1] != c_store &&
				y.monster_a1 > 2) y.monster_a1--;
		}
	}

	return 0;
}

unsigned int move_monster_b1() {

	// initialisize random function
	time_t f_rand;
	time(&f_rand);
	srand((unsigned int)f_rand);

	// clear old monster
	if (monster_b1_en) field[x.monster_b1][y.monster_b1] = c_slime;

	// move x or y
	if (rand() % 100 + 1 > 50) {

		// move + or -
		if (rand() % 100 + 1 > 50) {
			if (field[x.monster_b1 + 1][y.monster_b1] != c_wall && field[x.monster_b1 + 1][y.monster_b1] != c_diamond &&
				field[x.monster_b1 + 1][y.monster_b1] != c_TNT && field[x.monster_b1 + 1][y.monster_b1] != c_store &&
				x.monster_b1 < field_width - 3) x.monster_b1++;
		}
		else {
			if (field[x.monster_b1 - 1][y.monster_b1] != c_wall && field[x.monster_b1 - 1][y.monster_b1] != c_diamond &&
				field[x.monster_b1 - 1][y.monster_b1] != c_TNT && field[x.monster_b1 - 1][y.monster_b1] != c_store &&
				x.monster_b1 > 2) x.monster_b1--;
		}
	}
	else {

		// move + or -
		if (rand() % 100 + 1 > 50) {
			if (field[x.monster_b1][y.monster_b1 + 1] != c_wall && field[x.monster_b1][y.monster_b1 + 1] != c_diamond &&
				field[x.monster_b1][y.monster_b1 + 1] != c_TNT && field[x.monster_b1][y.monster_b1 + 1] != c_store &&
				y.monster_b1 < field_hight - 3) y.monster_b1++;
		}
		else {
			if (field[x.monster_b1][y.monster_b1 - 1] != c_wall && field[x.monster_b1][y.monster_b1 - 1] != c_diamond &&
				field[x.monster_b1][y.monster_b1 - 1] != c_TNT && field[x.monster_b1][y.monster_b1 - 1] != c_store &&
				y.monster_b1 > 2) y.monster_b1--;
		}
	}

	return 0;
}

unsigned int move_others() {

	static bool f_move_once = 1;

	if (f_move_once) {
		
		f_move_once = 0;

		move_monster_a1();
		move_monster_b1();
	}
	else f_move_once = 1;

	return 0;
}
