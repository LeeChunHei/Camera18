/*
 * global.cpp
 *
 *  Created on: Jul 20, 2017
 *      Author: LeeChunHei
 */

#include <global.h>

//Global pointer
JyMcuBt106 *bt = nullptr;
St7735r *lcd = nullptr;

//Global variable
uint8_t contrast = 0x40;
uint8_t corner_window_size = 7;	//the square for detection would be in size corener_range*2+1
uint8_t corner_min = 36;
uint8_t corner_max = 72;
Byte cam_buff[7680] = { };
