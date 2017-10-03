/*
 * main.cpp
 *
 *  Created on: Jul 18, 2017
 *      Author: LeeChunHei
 */

#include <global.h>

//Required DON'T DELETE IT !!!
namespace libbase {
namespace k60 {
Mcg::Config Mcg::GetMcgConfig() {
	Mcg::Config config;
	config.external_oscillator_khz = 50000;
	config.core_clock_khz = 200000;
	config.flexbus_clock_khz = 200000;
	return config;
}
}
}

uint16_t camera_buffer_index = 0;
bool bluetooth_listener(const Byte *data, const size_t size) {
//	Byte* temp = &cam_buff[camera_buffer_index];
//	temp = new Byte;
//	*temp = data[0];
	for (uint8_t i = 0; i < size; i++) {
		cam_buff[camera_buffer_index] = data[i];
		camera_buffer_index++;
	}
}

#include <../inc/algorithm/edge_corner_evaluate.h>

int main() {

	System::Init();

	//Bluetooth Init
	libsc::k60::JyMcuBt106::Config bt_config;
	bt_config.baud_rate = libbase::k60::Uart::Config::BaudRate::k115200;
	bt_config.id = 0;
	bt_config.rx_isr = &bluetooth_listener;
	libsc::k60::JyMcuBt106 bt_(bt_config);
	bt = &bt_;

	//Lcd Init
	libsc::St7735r::Config lcd_config;
	libsc::St7735r lcd_(lcd_config);
	lcd = &lcd_;
	lcd->Clear(Lcd::kRed);

	Timer::TimerInt algo_start_time;
	while (1) {
		if (camera_buffer_index >= 7680) {
//			for (uint8_t y = 0; y < 160; y++) {
//				for (uint8_t x = 0; x < 128; x++) {
//					lcd->SetRegion(Lcd::Rect(x, y, 1, 1));
//					lcd->FillColor(util::simple_camera_point_check(cam_buff, x, y) ? Lcd::kBlue : Lcd::kWhite);
//				}
//			}
			algo_start_time = System::TimeIn125us();
			algo();
			Byte send_time = System::TimeIn125us() - algo_start_time;
			Byte result = left_edge.size();
			bt->SendBuffer(&result, 1);
			System::DelayMs(1);
			result = right_edge.size();
			bt->SendBuffer(&result, 1);
			System::DelayMs(1);
			result = corner_pos[0].x;
			bt->SendBuffer(&result, 1);
			System::DelayMs(1);
			result = corner_pos[0].y;
			bt->SendBuffer(&result, 1);
			System::DelayMs(1);
			result = corner_pos[1].x;
			bt->SendBuffer(&result, 1);
			System::DelayMs(1);
			result = corner_pos[1].y;
			bt->SendBuffer(&result, 1);
			System::DelayMs(1);
			bt->SendBuffer(&send_time, 1);
			System::DelayMs(1);
			for (uint8_t i = 0; i < left_edge.size(); i++) {
				result = left_edge[i].x;
				bt->SendBuffer(&result, 1);
				System::DelayMs(1);
				result = left_edge[i].y;
				bt->SendBuffer(&result, 1);
				System::DelayMs(1);
			}
			for (uint8_t i = 0; i < right_edge.size(); i++) {
				result = right_edge[i].x;
				bt->SendBuffer(&result, 1);
				System::DelayMs(1);
				result = right_edge[i].y;
				bt->SendBuffer(&result, 1);
				System::DelayMs(1);
			}
			corner_pos[0].x = 0;
			corner_pos[0].y = 0;
			corner_pos[1].x = 0;
			corner_pos[1].y = 0;
			right_edge.clear();
			left_edge.clear();
			camera_buffer_index = 0;
		}
		System::DelayMs(10);
	}
	
}
