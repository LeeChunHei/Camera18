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

int main() {

	System::Init();

//	libsc::Button::Config config_button;
//	config_button.id = 0;
//	config_button.is_active_low = true;
//	config_button.is_use_pull_resistor = true;
//	libsc::Button button(config_button);

//Flash Init
	Flash::Config flash_config;
	Flash flash_(flash_config);
	flash = &flash_;

	//Led Init
	Led::Config config_led;
	config_led.id = 0;
	config_led.is_active_low = true;
	Led led1_(config_led);
	led1 = &led1_;
	config_led.id = 1;
	Led led2_(config_led);
	led2 = &led2_;
	config_led.id = 2;
	Led led3_(config_led);
	led3 = &led3_;
	config_led.id = 3;
	Led led4_(config_led);
	led4 = &led4_;

//	libsc::k60::TouchScreenLcd touch_lcd_;
//	touch_lcd = &touch_lcd_;

	//Battery Meter Init
	BatteryMeter::Config config_battery_meter;
	config_battery_meter.voltage_ratio = 0.4;
	BatteryMeter battery_meter_(config_battery_meter);
	battery_meter = &battery_meter_;

	//Passive Buzzer Init
//	PassiveBuzzer::Config config_passive_buzzer;
//	PassiveBuzzer buzzer_(config_passive_buzzer);
//	buzzer = &buzzer_;

//Servo Init
	FutabaS3010::Config config_servo;
	config_servo.id = 0;
	FutabaS3010 servo_(config_servo);
	servo = &servo_;

	//Bluetooth Init
	libsc::k60::JyMcuBt106::Config bt_config;
	bt_config.baud_rate = libbase::k60::Uart::Config::BaudRate::k115200;
	bt_config.id = 0;
	libsc::k60::JyMcuBt106 bt_(bt_config);
	bt = &bt_;

	//Motor Init
	libsc::AlternateMotor::Config motor_config;
	motor_config.id = 0;
	libsc::AlternateMotor left_motor_(motor_config);
	left_motor = &left_motor_;
	motor_config.id = 1;
	libsc::AlternateMotor right_motor_(motor_config);
	right_motor = &right_motor_;

	//Encoder Init
	libsc::DirEncoder::Config encoder_config;
	encoder_config.id = 0;
	libsc::DirEncoder left_encoder_(encoder_config);
	left_encoder = &left_encoder_;
	encoder_config.id = 1;
	libsc::DirEncoder right_encoder_(encoder_config);
	right_encoder = &right_encoder_;

	//Control Init
	util::Control car_(servo, left_encoder, right_encoder, left_motor, right_motor, 0, 0, 0, servo_left_bound, servo_right_bound);
	car = &car_;

	//Start up action
//	touch_lcd->Clear(TouchScreenLcd::BLACK);
//	util::PrintLogo();
//	touch_lcd->POINT_COLOR = TouchScreenLcd::GREEN;
//	touch_lcd->ShowString(0, 140, 480, 48, 48, "Camera 2018", 1);
//	touch_lcd->ShowString(0, 188, 480, 48, 48, "version 1.0", 1);
//	touch_lcd->ShowString(0, 236, 480, 48, 48, "Created by", 1);
//	touch_lcd->ShowString(0, 284, 480, 48, 48, "Lee Chun Hei(Leslie)", 1);
//	//Battery Check
//	float voltage = 0;
//	char buf[20] = { };
//	do {
//		voltage = battery_meter->GetVoltage();
//		touch_lcd->POINT_COLOR = voltage <= 7.4 ? Lcd::kRed : Lcd::kGreen;
//		sprintf(buf, "Voltage: %.2fV", voltage);
//		touch_lcd->ShowString((480 - strlen(buf) * 24) / 2, 332, 480, 48, 48, buf, 1);
//
//	} while (voltage <= 7.4 && !touch_lcd->Scan(0));
//	for (uint8_t i = 0; i < 10; i++)
//		touch_lcd->Scan(0);
//	if (voltage > 7.4) {
//		System::DelayMs(1500);
//	}

//	util::battery_test();

//	util::led_test();

//	util::servo_tune(); //left bound 750 center 1060 right bound 1380

//	lcd->SetRegion(Lcd::Rect(0, 0, 128, 160));
//	lcd->Clear(true);

//	//Start up action
//	console->Clear(true);
//	util::PrintLogo();
//	console->SetTextColor(Lcd::kGreen);
//	console->SetCursorRow(2);
//	console->WriteString("Camera 2018");
//	console->SetCursorRow(3);
//	console->WriteString("version 1.0");
//	console->SetCursorRow(7);
//	console->WriteString("Created by");
//	console->SetCursorRow(8);
//	console->WriteString("Lee Chun Hei");
//	console->SetCursorRow(9);
//	console->WriteString("(Leslie)");
//	System::DelayMs(1500);

//	libutil::Touch_Menu menu(touch_lcd, flash);
//	menu.AddItem("Tools", &menu.main_menu);	//index 0;
//	menu.AddItem("Camera Tuning", std::bind(&util::camera_tune), menu.main_menu.menu_items[0].sub_menu);
//	menu.AddItem("Servo Tuning", std::bind(&util::servo_tune), menu.main_menu.menu_items[0].sub_menu);
//	menu.AddItem("Battery test", std::bind(&util::battery_test), menu.main_menu.menu_items[0].sub_menu);
//	menu.AddItem("Led test", std::bind(&util::led_test), menu.main_menu.menu_items[0].sub_menu);
//	menu.AddItem("Camera contrast", &contrast, &menu.main_menu);
//	menu.AddItem("Corner window size", &corner_window_size, &menu.main_menu);
//	menu.AddItem("Corner min value", &corner_min, &menu.main_menu);
//	menu.AddItem("Corner max value", &corner_max, &menu.main_menu);
//	menu.AddItem("Camera contrast", &contrast, &menu.main_menu);
//	menu.AddItem("Corner window size", &corner_window_size, &menu.main_menu);
//	menu.AddItem("Corner min value", &corner_min, &menu.main_menu);
//	menu.AddItem("Corner max value", &corner_max, &menu.main_menu);
//	menu.AddItem("Camera contrast", &contrast, &menu.main_menu);
//	menu.AddItem("Corner window size", &corner_window_size, &menu.main_menu);
//	menu.AddItem("Corner min value", &corner_min, &menu.main_menu);
//	menu.AddItem("Corner max value", &corner_max, &menu.main_menu);
//	menu.AddItem("Camera contrast", &contrast, &menu.main_menu);
//	menu.AddItem("Corner window size", &corner_window_size, &menu.main_menu);
//	menu.AddItem("Corner min value", &corner_min, &menu.main_menu);
//	menu.AddItem("Corner max value", &corner_max, &menu.main_menu);
//	menu.EnterMenu(&menu.main_menu, 0, 0, 480, 800, 48);

	Ov7725::Config config_cam;
	config_cam.contrast = contrast;
	config_cam.fps = Ov7725::Config::Fps::kHigh;
	config_cam.id = 0;
	config_cam.h = 480;
	config_cam.w = 128;
	Ov7725 cam_(config_cam);
	cam = &cam_;

//	libutil::Menu menu(lcd, console, joystick, flash);
//	menu.AddItem("contrast", &contrast, 1, &menu.main_menu);
//	menu.AddItem("battery level", std::bind(&util::battery_test), &menu.main_menu);
//	menu.AddItem("servo tune", std::bind(&util::servo_tune), &menu.main_menu);
//	menu.AddItem("snake game", std::bind(&snake_game, joystick, lcd, console), &menu.main_menu);
//	menu.EnterMenu(&menu.main_menu);

	//Program ended action
//	touch_lcd->Clear(TouchScreenLcd::BLACK);
//	touch_lcd->POINT_COLOR = TouchScreenLcd::RED;
//	touch_lcd->ShowString(0, 0, 480, 800, 48, "Program Ended", 0);
//	Timer::TimerInt end_time = System::Time();
//	while (1) {
//		char buf[100] = { };
//		sprintf(buf, "Ended %d ms before", System::Time() - end_time);
//		touch_lcd->ShowString(0, 48, 480, 48, 48, buf, 0);
//	}
}
