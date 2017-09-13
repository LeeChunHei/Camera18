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
//#include <../inc/util/bluetooth.h>

//Battery Meter Header File
#include <libsc/battery_meter.h>

//Flash Header File
#include <libbase/k60/flash.h>

//Pit Header File
#include <libbase/k60/pit.h>

//Speed Control Header File
#include <../inc/util/control.h>

//Menu Header File
#include <libutil/normal_menu.h>
#include <libutil/touch_menu.h>

//Util Header File
#include <../inc/util/util.h>

//Snake Game Header File
#include <../inc/game/snake_game.h>

//namespace
using namespace libsc;
using namespace libsc::k60;
using namespace libbase::k60;
using namespace libutil;
using namespace std;

//Struct
struct coor {
	uint8_t x;
	uint8_t y;
};

//Global pointer
extern Led *led1;
extern Led *led2;
extern Led *led3;
extern Led *led4;
extern libsc::k60::TouchScreenLcd* touch_lcd;
extern libsc::St7735r* lcd;
extern libsc::LcdConsole* console;
extern BatteryMeter *battery_meter;
extern PassiveBuzzer *buzzer;
extern Ov7725 *cam;
extern FutabaS3010 *servo;
extern AlternateMotor *left_motor;
extern AlternateMotor *right_motor;
extern DirEncoder *left_encoder;
extern DirEncoder *right_encoder;
extern JyMcuBt106 *bt;
//extern util::BTComm *bt;
extern Flash *flash;
extern util::Control *car;
extern libsc::Joystick* joystick;

//Global variable
extern uint8_t contrast;
extern uint8_t corner_window_size;
extern uint8_t corner_min;
extern uint8_t corner_max;
extern const uint16_t cam_height;
extern const uint16_t cam_width;
extern const uint16_t servo_right_bound;
extern const uint16_t servo_center;
extern const uint16_t servo_left_bound;



#endif /* INC_GLOBAL_H_ */
