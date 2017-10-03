/*
 * util.h
 *
 *  Created on: Jul 18, 2017
 *      Author: LeeChunHei
 */

#ifndef INC_UTIL_UTIL_H_
#define INC_UTIL_UTIL_H_

#include <global.h>

namespace util {

void battery_test();
void led_test();
void servo_tune();
void camera_tune();
//return value 2 is out of bound
uint8_t camera_point_check(const Byte* buff, int16_t x, int16_t y);
//return true for black and false for white
bool simple_camera_point_check(const Byte* buff, int16_t x, int16_t y);
void PrintLogo();

}



#endif /* INC_UTIL_UTIL_H_ */
