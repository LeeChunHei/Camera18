/*
 * global.h
 *
 *  Created on: Jul 18, 2017
 *      Author: LeeChunHei
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <cassert>
#include <cstring>
#include <string>
#include <libbase/k60/mcg.h>
#include <libsc/system.h>
#include <functional>
#include <vector>

//led Header File
#include <libsc/led.h>

//Joystick Header File
#include <libsc/joystick.h>

//LCD Header File

#include <libsc/k60/touchscreen_lcd.h>
#include <libsc/st7735r.h>
#include <libsc/lcd_console.h>
#include <libsc/lcd_typewriter.h>

//Buzzer Header File
#include <libsc/passive_buzzer.h>

//Camera Header File
#include<libsc/k60/ov7725.h>

//Servo Header File
#include<libsc/futaba_s3010.h>

//Motor Header File
#include<libsc/alternate_motor.h>
#include<libsc/motor.h>

//Dir Encoder Header File
#include<libsc/dir_encoder.h>

//Bluetooth Header File
#include <libsc/k60/jy_mcu_bt_106.h>

//Util Header File
#include <../inc/util/util.h>

//namespace
using namespace libsc;
using namespace libsc::k60;
using namespace libbase::k60;
using namespace libutil;
using namespace std;

//Struct
struct coor {
	int16_t x;
	int16_t y;
};

//Global pointer
extern JyMcuBt106 *bt;
extern St7735r *lcd;

//Global variable
extern uint8_t contrast;
extern uint8_t corner_window_size;
extern uint8_t corner_min;
extern uint8_t corner_max;
#define cam_height 160
#define cam_width 128

extern Byte cam_buff[7680];
extern vector<coor> left_edge;
extern vector<coor> right_edge;
extern coor corner_pos[2];	//index 0 is left corner coor, 1 is right corner

#endif /* INC_GLOBAL_H_ */
