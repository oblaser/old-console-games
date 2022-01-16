//////////////////////////////////////////////////////
// 
// Author:		Oliver Blaser
// 
// Date:		01.01.2016
//
// Description:	Functions for C Jump
// 
//////////////////////////////////////////////////////

// includeing function.h
#include "function.h"

// coordinate objects
coordinate x;
coordinate y;

// file management
FILE * fp;

// time handling
clock_t t_old;
clock_t t_new;

// controller object
XboxController * controller1;

/* --- variables --- */

// save array
unsigned int save_data[save_number];

// select page
unsigned int page;

// set directions of moving objects
signed int quid_dir;
signed int move_bar_dir;

// score
unsigned int score;
unsigned int h_score;
unsigned int quantity_bars;

// last butten that was pressed
unsigned int last_but;

// enable
bool print_once;
bool print_en;
bool quid_move_en;
bool move_bar_en;
bool rand_create_en;
bool attack_rdy;
bool bar_move_en;
bool quid_overflow_l;
bool quid_overflow_r;

// counter
unsigned int quid_jump_cnt;
unsigned int cnt_no_bar;

// no bars at the same x pos
unsigned int x_bar_old;

// timer variables
unsigned int tmr_quid;
unsigned int tmr_wait_button;
unsigned int tmr_attack;
unsigned int tmr_move_bar;

// times * 10 ms
unsigned int t_quid_min;
unsigned int t_wait_button;
unsigned int t_attack;
unsigned int t_move_bar;

// field
unsigned char field[field_height + 2][field_width + 1];

/* --- pictures --- */

// title text
unsigned char pic_quid_text[8][23] = {
	{  32,  95,  95,  32,  32,  32,  32,  95,  95,  95,  95,  95,  95,  95,  95,  95,  95,  95,  95,  95,  95,  95,  95 },
	{  47,  32,  32,  92,  32,  32,  32,  32, 124,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32 },
	{ 124,  32,  32,  32,  32,  32,  32,  32, 124,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  95,  32 },
	{ 124,  32,  32,  32,  32,  32,  32,  32, 124,  32, 124,  32, 124,  32, 124,  47,  92,  47,  92,  32, 124,  32,  92 },
	{ 124,  32,  32,  32,  32,  32,  32,  32, 124,  32, 124,  32, 124,  32, 124,  32, 124,  32, 124,  32, 124,  32, 124 },
	{  92,  95,  95,  47,  32,  32,  92,  95,  47,  32,  92,  95,  47,  32, 124,  32, 124,  32, 124,  32, 124,  95,  47 },
	{  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32, 124,  32,  32 },
	{  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32, 124,  32,  32 },
};

// bar solid
unsigned char pic_bar_solid[5] = { c_bar_solid, c_bar_solid, c_bar_solid, c_bar_solid, c_bar_solid };

// bar break
unsigned char pic_bar_break[5] = { c_bar_break, c_bar_break, c_bar_break, c_bar_break, c_bar_break };

// bar move
unsigned char pic_bar_move[5] = { c_bar_move, c_bar_move, c_bar_move, c_bar_move, c_bar_move };

// bar once
unsigned char pic_bar_once[5] = { c_bar_once, c_bar_once, c_bar_once, c_bar_once, c_bar_once };

// bar transparent
unsigned char pic_bar_trans[5] = { c_bar_trans, c_bar_trans, c_bar_trans, c_bar_trans, c_bar_trans };

// Quid L
unsigned char pic_quid[5][5] = {
	{ 218, 196, 196, 196, 191 },
	{ 179,  79,  32,  79, 179 },
	{ 179,  32, 167,  32, 179 },
	{ 195, 194, 196, 194, 180 },
	{ 217, 217,  32, 192, 192 }
};

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

// CPU informations
unsigned int get_CPU_freq(unsigned int f_CPU_num){
	
	// get the number or processors 
	SYSTEM_INFO si = { 0 };
	::GetSystemInfo(&si);

	// allocate buffer to get info for each processor
	const int size = si.dwNumberOfProcessors * sizeof(PROCESSOR_POWER_INFORMATION);
	LPBYTE pBuffer = new BYTE[size];

	NTSTATUS status = ::CallNtPowerInformation(ProcessorInformation, NULL, 0, pBuffer, size);

	if (STATUS_SUCCESS == status) {

		// list each processor frequency 
		PPROCESSOR_POWER_INFORMATION ppi = (PPROCESSOR_POWER_INFORMATION)pBuffer;

		DWORD nIndex = f_CPU_num;

		if (f_CPU_num > si.dwNumberOfProcessors - 1) {
			delete[]pBuffer;
			return NO_CPU;
		}

		delete[]pBuffer;
		return (ppi->CurrentMhz);

	}
	else {
		delete[]pBuffer;
	}

	return 0;
}

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

// error
unsigned int error(unsigned int f_error_nr) {

	clr_scr;

	gotoxy(5, 5);
	printf("Error %d", f_error_nr);

	printxy("Please contact the developper.", 5, 7);

	while (1);
}

/* --- print pics --- */

unsigned int print_pic_quid_text(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 8; y.draw++) {
		for (x.draw = 0; x.draw < 23; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_quid_text[y.draw][x.draw]);
		}
	}

	return 0;
}

unsigned int print_pic_bar(unsigned int f_select, unsigned int f_print_x, unsigned int f_print_y) {

	y.draw = 0;

	switch (f_select) {

	case c_bar_solid:

		for (x.draw = 0; x.draw < 5; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_bar_solid[x.draw]);
		}

		break;

	case c_bar_break:

		for (x.draw = 0; x.draw < 5; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_bar_break[x.draw]);
		}

		break;

	case c_bar_move:

		printxy("       ", f_print_x - 1, f_print_y - 1);
		printxy(" ", f_print_x - 1, f_print_y);
		printxy(" ", f_print_x + 5, f_print_y);

		for (x.draw = 0; x.draw < 5; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_bar_move[x.draw]);
		}

		break;

	case c_bar_once:

		for (x.draw = 0; x.draw < 5; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_bar_once[x.draw]);
		}

		break;

	case c_bar_trans:

		for (x.draw = 0; x.draw < 5; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_bar_trans[x.draw]);
		}

		break;

	default:
		break;
	}
	
	return 0;
}

unsigned int print_pic_quid(unsigned int f_print_x, unsigned int f_print_y) {

	for (y.draw = 0; y.draw < 5; y.draw++) {
		for (x.draw = 0; x.draw < 5; x.draw++) {
			gotoxy(x.draw + f_print_x, y.draw + f_print_y);
			printf("%c", pic_quid[y.draw][x.draw]);
		}
	}

	return 0;
}

// print counters
unsigned int print_counters(bool f_select) {

	if (f_select) {
		gotoxy(8, 1);
		printf("%d", h_score);
	}

	else {
		gotoxy(1, 1);
		printf("%d", score);
	}

	return 0;
}

// load file
unsigned int load_file() {

	// check if file exists
	if (fopen_s(&fp, file_name, "r") == 0) {

		// load values
		if (fread(save_data, sizeof(int), save_number, fp) != save_number) error(err_read_f);

		fclose(fp);
	}

	// create file
	else {

		// fill data array
		for (int i = 0; i < save_number; i++) save_data[i] = '\n';
		save_data[0] = 0;

		// open file
		if (fopen_s(&fp, file_name, "w") == 0) {

			// write in file
			if (fwrite(save_data, sizeof(int), save_number, fp) != save_number) error(err_write_f);

			// close file
			fclose(fp);
		}

		else error(err_open_f);

		// open file
		if (fopen_s(&fp, file_name, "r") == 0) {

			// load values
			if (fread(save_data, sizeof(int), save_number, fp) != save_number) error(err_read_f);

			fclose(fp);
		}

		else error(err_open_f);
	}

	h_score = save_data[0];

	return 0;
}

// save file
unsigned int save_file() {

	if (score > h_score) h_score = score;

	save_data[0] = h_score;

	// open file
	if (fopen_s(&fp, file_name, "w") == 0) {

		// write in file
		if (fwrite(save_data, sizeof(int), save_number, fp) != save_number) error(err_write_f);

		// close file
		fclose(fp);
	}

	else error(err_open_f);

	return 0;
}

// create a bar-structure in the field array
unsigned int create_bar(unsigned int f_select, unsigned int f_x, unsigned int f_y) {

	if (f_select != 0) {

		field[f_y - 1][f_x] = c_bar_trans;
		field[f_y][f_x] = f_select;
	}

	if (f_select == 0) {
		field[f_y][f_x] = f_select;
	}

	return 0;
}

// start conditions
unsigned int start() {

	controller1 = new XboxController(1);

	// turn off cursor
	set_cursor(0, cursor_hight);

	// set color
	system("color 2E");

	// window size and position
	set_window_default;

	// set window title
	system("title C Jump");

	// times
	t_quid_min = get_CPU_freq(0) / 890;
	t_wait_button = 3; get_CPU_freq(0) / 890;
	t_attack = get_CPU_freq(0) / 890;
	t_move_bar = get_CPU_freq(0) / 297;

	return 0;
}

// set values to default
unsigned int set_default() {

	// time handler
	t_old = clock() / 10;

	// select page
	page = 'star';

	// set print enables
	if(page == 'star') print_once = 1;
	else print_once = 0;
	print_en = 1;

	// set attack ready bit
	attack_rdy = 1;

	// clear timers
	tmr_wait_button = 0;
	tmr_quid = 0;
	tmr_attack = 0;

	// quid position
	x.quid = 18;
	y.quid = 23;
	quid_dir = 1;

	move_bar_dir = 1;
	move_bar_en = 1;

	rand_create_en = 1;

	// quid jump counter
	quid_jump_cnt = quid_max_jump;

	// random bars
	cnt_no_bar = no_bar_max;

	// field
	for (y.draw = 0; y.draw < field_height + 1; y.draw++) {
		for (x.draw = 0; x.draw < field_width + 1; x.draw++) {
			field[y.draw][x.draw] = 0;
		}
	}

	create_bar(c_bar_solid, 5, 37);
	create_bar(c_bar_solid, 14, 37);
	create_bar(c_bar_solid, 23, 37);

	create_bar(c_bar_solid, 3, 28);
	create_bar(c_bar_solid, 11, 25);
	create_bar(c_bar_solid, 24, 18);
	create_bar(c_bar_solid, 6, 13);
	create_bar(c_bar_solid, 16, 8);
	create_bar(c_bar_solid, 1, 5);

	return 0;
}

// read HID
unsigned int read_HID() {

	if (tmr_wait_button == 0) {
		
		last_but = 0;

		switch (page) {

		case 'star':
			
			if ((GetAsyncKeyState(KB_start) & MSB_short) || (controller1->getState().Gamepad.wButtons & XI_start)) {
				page = 'game';
				print_en = 1;
				last_but = but_start;
				tmr_wait_button = t_wait_button;
			}
			
			break;

		case 'game':

			if ((GetAsyncKeyState(KB_move_l) & MSB_short) || (GetAsyncKeyState(KB_move_l_alt) & MSB_short) ||
				(controller1->getState().Gamepad.sThumbLX < XI_stick_th_) || (controller1->getState().Gamepad.wButtons & XI_move_l)) {

				x.quid--;
				print_en = 1;
				last_but = but_left;
				tmr_wait_button = t_wait_button;
			}

			if ((GetAsyncKeyState(KB_move_r) & MSB_short) || (GetAsyncKeyState(KB_move_r_alt) & MSB_short) ||
				(controller1->getState().Gamepad.sThumbLX > XI_stick_th) || (controller1->getState().Gamepad.wButtons & XI_move_r)) {

				x.quid++;
				print_en = 1;
				last_but = but_right;
				tmr_wait_button = t_wait_button;
			}

			if (((GetAsyncKeyState(KB_attack) & MSB_short) || (controller1->getState().Gamepad.wButtons & XI_attack)) && 
				attack_rdy) {

				x.attack = x.quid + 2;
				y.attack = y.quid - 1;
				attack_rdy = 0;
				last_but = but_attack;
				tmr_wait_button = t_wait_button;
			}

			break;

		default:
			error(err_page_HID);
			break;
		}
	}

	return 0;
}

// quid speed
unsigned int quid_speed(unsigned int f_jump_cnt) {

	switch (f_jump_cnt) {

	case 0:
		return t_quid_min * 5;
		break;

	case 1:
		return t_quid_min * 4;
		break;

	case 2:
		return t_quid_min * 3;
		break;

	case 3:
		return t_quid_min * 3;
		break;

	case 4:
		return t_quid_min * 3;
		break;

	case 5:
		return t_quid_min * 2;
		break;

	case 6:
		return t_quid_min * 2;
		break;

	case 7:
		return t_quid_min * 2;
		break;

	case 8:
		return t_quid_min * 2;
		break;

	default:
		return t_quid_min;
		break;
	}

	return 0;
}

// shift down the array and create new bars
unsigned int shift_down() {

	unsigned int f_x_bar;
	unsigned int f_y_bar;

	// initialisize random function
	time_t f_rand_init;
	time(&f_rand_init);
	srand((unsigned int)f_rand_init);

	// random filled next line
	if (rand_create_en) {

		for (y.draw = 0; y.draw <= 2; y.draw++) {
			for (x.draw = 1; x.draw <= field_width; x.draw++) {
				field[y.draw][x.draw] = 0;
			}
		}

		if (score < 500) quantity_bars = 30;
		if (score > 500) quantity_bars = 50;
		if (score > 1000) quantity_bars = 70;
		if (score > 1500) quantity_bars = 100;
		if (score > 2000) quantity_bars = 130;
		if (score > 2500) quantity_bars = 170;

		// set position
		f_x_bar = rand() % quantity_bars + 1;
		f_y_bar = 2;

		while(f_x_bar > x_bar_old - 4 && f_x_bar < x_bar_old + 9) f_x_bar = rand() % 26 + 1;

		x_bar_old = f_x_bar;

		// create bar, yes, no
		if (cnt_no_bar < no_bar_max && f_x_bar > 26) {

			// no bar

			cnt_no_bar++;
		}

		else {

			// witchone
			switch (rand() % 10) {

				// bar once
			case 0:
				create_bar(c_bar_once, f_x_bar, f_y_bar);
				cnt_no_bar = 0;
				break;

			case 1:
				if (score > 1500) create_bar(c_bar_once, f_x_bar, f_y_bar);
				else create_bar(c_bar_solid, f_x_bar, f_y_bar);

				cnt_no_bar = 0;
				break;

				// bar move
			case 2:
				if (score > 1000 && bar_move_en) {
					create_bar(c_bar_move, f_x_bar, f_y_bar);
					x.move_bar = f_x_bar;
					y.move_bar = f_y_bar;
					move_bar_dir = 1;
					bar_move_en = 0;
				}

				else create_bar(c_bar_solid, f_x_bar, f_y_bar);
				
				cnt_no_bar = 0;

				break;

			case 3:
				if (bar_move_en) {
					create_bar(c_bar_move, f_x_bar, f_y_bar);
					x.move_bar = f_x_bar;
					y.move_bar = f_y_bar;
					move_bar_dir = 1;
					bar_move_en = 0;
				}

				else create_bar(c_bar_once, f_x_bar, f_y_bar);
				
				cnt_no_bar = 0;

				break;

				// bar break
			case 4:
				if (cnt_no_bar < no_bar_max) {
					create_bar(c_bar_break, f_x_bar, f_y_bar);
					cnt_no_bar++;
				}

				else {
					create_bar(c_bar_solid, f_x_bar, f_y_bar);
					cnt_no_bar = 0;
				}

				break;

			case 5:
				if (cnt_no_bar < no_bar_max) {
					create_bar(c_bar_break, f_x_bar, f_y_bar);
					cnt_no_bar++;
				}

				else {
					create_bar(c_bar_solid, f_x_bar, f_y_bar);
					cnt_no_bar = 0;
				}

				break;

				// bar solid
			default:
				create_bar(c_bar_solid, f_x_bar, f_y_bar);
				cnt_no_bar = 0;
				break;
			}
		}
		

		rand_create_en = 0;
	}

	else {
		rand_create_en = 1;
		cnt_no_bar++;
	}

	// shift process
	y.move_bar++;

	for (y.draw = field_height + 1; y.draw >= 2; y.draw--) {
		for (x.draw = 1; x.draw <= field_width; x.draw++) {
			field[y.draw][x.draw] = field[y.draw - 1][x.draw];
		}
	}

	// increment score
	score++;

	return 0;
}

// set quids x position
unsigned int quid_overflow() {

	quid_overflow_l = 0;
	quid_overflow_r = 0;

	if (x.quid < 1) {
		x.quid = 26;
		quid_overflow_l = 1;
	}

	if (x.quid > 26) {
		x.quid = 1;
		quid_overflow_r = 1;
	}

	return 0;
}

// set positions
unsigned int set_positions() {

	// moveing bars
	bar_move_en = 1;
	for (int i = 3; i <= field_height; i++) {
		for (int j = 1; j <= field_width - 4; j++) {
			if (field[i][j] == c_bar_move) bar_move_en = 0;
		}
	}

	if (tmr_move_bar == 0 && !bar_move_en) {

		x.move_bar += move_bar_dir;

		if (x.move_bar < 1) {
			x.move_bar = 1;
			move_bar_dir = 1;
		}

		if (x.move_bar > field_width - 4) {
			x.move_bar = field_width - 4;
			move_bar_dir = -1;
		}

		field[y.move_bar][x.move_bar] = c_bar_move;

		field[y.move_bar][x.move_bar - 1] = 0;
		field[y.move_bar][x.move_bar + 1] = 0;
		field[y.move_bar - 1][x.move_bar] = 0;

		tmr_move_bar = t_move_bar;

		print_en = 1;
	}

	// attack
	if (!attack_rdy && tmr_attack == 0) {
		y.attack--;
		print_en = 1;
		tmr_attack = t_attack;

		if (y.attack < 3) attack_rdy = 1;
	}

	// quid
	quid_overflow();

	if (tmr_quid == 0) {

		if (quid_jump_cnt <= 0) quid_dir = 1;

		// detect bars
		quid_move_en = 1;

		for (int i = -4; i <= 4; i++) {
			switch (field[y.quid + 5][x.quid + i]) {

			case c_bar_solid:
				quid_move_en = 0;
				if (quid_dir > 0) quid_jump_cnt = quid_max_jump;
				break;

			case c_bar_move:
				quid_move_en = 0;
				if (quid_dir > 0) quid_jump_cnt = quid_max_jump;
				break;

			case c_bar_break:
				if (quid_dir > 0) create_bar(c_bar_trans, x.quid + i, y.quid + 5);
				break;

			case c_bar_once:
				quid_move_en = 0;
				
				if (quid_dir > 0) {
					if (quid_dir > 0) quid_jump_cnt = quid_max_jump;
					create_bar(c_bar_trans, x.quid + i, y.quid + 5);
				}

				break;

			default:
				break;
			}
		}

		// set position for quid
		if (quid_move_en) {
			y.quid += quid_dir;
			quid_jump_cnt += quid_dir;
		}

		else {
			quid_dir = -1;

			y.quid += quid_dir;
			quid_jump_cnt += quid_dir;
		}

		// jump up -> shift down
		if (y.quid < 13) {
			shift_down();
			y.quid = 13;
		}

		// fall down -> game over
		if (y.quid > field_height - 4) {

			y.quid = field_height - 4;
			save_file();
			
			return ret_exit;
		}

		print_en = 1;

		tmr_quid = quid_speed(quid_jump_cnt);
	}

	return 0;
}

// pages
unsigned int page_start() {

	if (print_once) {

		clr_scr;

		print_counters(0);
		print_counters(1);

		printxy("C Jump", 25, 1);

		print_pic_quid_text(4, 5);
		gotoxy(21, 6);
		printf("%s", release_version);

		//print_pic_quid(24, 5);

		printxy("Action  Keyboard  Controller", 2, 30);
		printxy("move    A / D     left stick", 2, 32);
		printxy("attack  Space     A", 2, 33);
		printxy("start   Enter     Start", 2, 34);

		print_once = 0;
	}

	return 0;
}

unsigned int page_game() {

	if (!print_once) {

		clr_scr;

		score = 0;

		print_counters(1);

		printxy("C Jump", 25, 1);

		print_once = 1;
	}

	print_counters(0);


	// quid clear on overflow
	if (quid_overflow_l) {
		for (int i = 0; i < 5; i++) {
			printxy("     ", 1, y.quid + i);
		}
	}

	if (quid_overflow_r) {
		for (int i = 0; i < 5; i++) {
			printxy("     ", 26, y.quid + i);
		}
	}

	// bars
	for (int i = 3; i <= field_height+1; i++) {
		for (int j = 1; j <= field_width - 4; j++) {
			print_pic_bar(field[i][j], j, i);
		}
	}

	// attack
	if (!attack_rdy) {
		gotoxy(x.attack, y.attack);
		printf("%c", c_attack);
		gotoxy(x.attack, y.attack + 1);
		printf(" ");
	}

	else {
		gotoxy(x.attack, y.attack + 1);
		printf(" ");
	}

	// quid
	// clear left
	if (last_but == but_right || last_but == but_attack) {
		x.draw = x.quid - 1;
		for (y.draw = y.quid - 1; y.draw <= y.quid + 5; y.draw++) {
			printxy(" ", x.draw, y.draw);
		}
	}

	// clear right
	if (last_but == but_left || last_but == but_attack) {
		x.draw = x.quid + 5;
		for (y.draw = y.quid - 1; y.draw <= y.quid + 5; y.draw++) {
			printxy(" ", x.draw, y.draw);
		}
	}

	// clear over
	if (quid_dir > 0) {
		y.draw = y.quid - 1;
		for (x.draw = x.quid; x.draw < x.quid + 5; x.draw++) {
			printxy(" ", x.draw, y.draw);
		}
	}

	// clear under
	else {
		y.draw = y.quid + 5;
		for (x.draw = x.quid; x.draw < x.quid + 5; x.draw++) {
			printxy(" ", x.draw, y.draw);
		}
	}

	// print quid
	print_pic_quid(x.quid, y.quid);

	// clear last line
	for (x.draw = 0; x.draw < field_width; x.draw++) printxy(" ", x.draw, field_height + 1);

	return 0;
}

// print page
unsigned int print() {

	if (print_en) {

		switch (page) {

		case 'star':
			page_start();
			break;

		case 'game':
			page_game();
			break;

		default:
			error(err_page_print);
			break;
		}

		print_en = 0;
	}

	gotoxy(0, 0);

	return 0;
}

// 10ms "interrupt"
unsigned int interrupt_10ms() {

	if (tmr_quid > 0) tmr_quid--;
	if (tmr_attack > 0) tmr_attack--;
	if (tmr_wait_button > 0) tmr_wait_button--;
	if (tmr_move_bar > 0) tmr_move_bar--;

	return 0;
}

// handle with time
unsigned int time_handler() {

	t_new = clock() / 10;

	if (t_new > t_old) interrupt_10ms();

	t_old = t_new;

	return 0;
}
