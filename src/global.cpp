/*
 * global.cpp
 *
 *  Created on: Jul 20, 2017
 *      Author: LeeChunHei
 */

#include <global.h>

//Global pointer
Led *led1 = nullptr;
Led *led2 = nullptr;
Led *led3 = nullptr;
Led *led4 = nullptr;
libsc::k60::TouchScreenLcd* touch_lcd = nullptr;
libsc::St7735r* lcd = nullptr;
libsc::LcdConsole* console = nullptr;
BatteryMeter *battery_meter = nullptr;
PassiveBuzzer *buzzer = nullptr;
Ov7725 *cam = nullptr;
FutabaS3010 *servo = nullptr;
AlternateMotor *left_motor = nullptr;
AlternateMotor *right_motor = nullptr;
DirEncoder *left_encoder = nullptr;
DirEncoder *right_encoder = nullptr;
JyMcuBt106 *bt = nullptr;
//util::BTComm *bt = nullptr;
Flash *flash = nullptr;
//Pit *pit = nullptr;
util::Control *car = nullptr;
libsc::Joystick* joystick = nullptr;

//Global variable
uint8_t contrast = 0x40;
uint8_t corner_window_size = 11;
uint8_t corner_min = 0;
uint8_t corner_max = 0;
const uint16_t cam_height = 60;
const uint16_t cam_width = 80;
const uint16_t servo_right_bound = 1380;
const uint16_t servo_center = 1060;
const uint16_t servo_left_bound = 750;
