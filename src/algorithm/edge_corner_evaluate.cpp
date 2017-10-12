/*
 * edge_corner_evaluate.cpp
 *
 *  Created on: Sep 13, 2017
 *      Author: LeeChunHei
 */

#include <../inc/algorithm/edge_corner_evaluate.h>

vector<coor> left_edge;
vector<coor> right_edge;
coor corner_pos[2] = { };	//index 0 is left corner coor, 1 is right corner

enum dir {
	up, up_left, left, down_left, down, down_right, right, up_right
};

#define up 0
#define up_left 1
#define left 2
#define down_left 3
#define down 4
#define down_right 5
#define right 6
#define up_right 7

int8_t left_edge_dir = up;
int8_t right_edge_dir = up;
uint8_t right_corner_points = 0;
uint8_t left_corner_points = 0;

bool find_left_edge() {
	if (!left_edge.size())
		return false;
	coor prev_left_edge = left_edge.back();
	uint8_t x = prev_left_edge.x;
	uint8_t y = prev_left_edge.y;
	switch (left_edge_dir) {
	case up:
		y--;
		break;
	case up_left:
		x--;
		y--;
		break;
	case left:
		x--;
		break;
	case down_left:
		x--;
		y++;
		break;
	case down:
		y++;
		break;
	case down_right:
		x++;
		y++;
		break;
	case right:
		x++;
		break;
	case up_right:
		x++;
		y--;
		break;
	}
	bool search_clockwise;
	switch (util::camera_point_check(cam_buff, x, y)) {
	case 1:
		search_clockwise = true;
		break;
	case 2:
		return false;
		break;
	default:
		search_clockwise = false;
		break;
	}
	for (uint8_t i = 0; i < 7; i++) {
		uint8_t prev_x = x;
		uint8_t prev_y = y;
		switch (left_edge_dir) {
		case up:
			search_clockwise ? x++ : x--;
			break;
		case up_left:
			search_clockwise ? x++ : y++;
			break;
		case left:
			search_clockwise ? y-- : y++;
			break;
		case down_left:
			search_clockwise ? y-- : x++;
			break;
		case down:
			search_clockwise ? x-- : x++;
			break;
		case down_right:
			search_clockwise ? x-- : y--;
			break;
		case right:
			search_clockwise ? y++ : y--;
			break;
		case up_right:
			search_clockwise ? y++ : x--;
			break;
		}
		switch (util::camera_point_check(cam_buff, x, y)) {
		case 0:
			if (search_clockwise) {
				coor edge;
				edge.x = x;
				edge.y = y;
				left_edge.push_back(edge);
				return true;
			}
			break;
		case 1:
			if (!search_clockwise) {
				coor edge;
				edge.x = prev_x;
				edge.y = prev_y;
				left_edge.push_back(edge);
				return true;
			}
			break;
		case 2:
			return false;
			break;
		}
		search_clockwise ? left_edge_dir-- : left_edge_dir++;
		if (left_edge_dir < 0) {
			left_edge_dir = up_right;
		} else if (left_edge_dir > up_right) {
			left_edge_dir = up;
		}
	}
	return false;
}

bool find_right_edge() {
	if (!right_edge.size())
		return false;
	coor prev_right_edge = right_edge.back();
	uint8_t x = prev_right_edge.x;
	uint8_t y = prev_right_edge.y;
	switch (right_edge_dir) {
	case up:
		y--;
		break;
	case up_left:
		x--;
		y--;
		break;
	case left:
		x--;
		break;
	case down_left:
		x--;
		y++;
		break;
	case down:
		y++;
		break;
	case down_right:
		x++;
		y++;
		break;
	case right:
		x++;
		break;
	case up_right:
		x++;
		y--;
		break;
	}
	bool search_clockwise;
	switch (util::camera_point_check(cam_buff, x, y)) {
	case 1:
		search_clockwise = false;
		break;
	case 2:
		return false;
		break;
	default:
		search_clockwise = true;
		break;
	}
	for (uint8_t i = 0; i < 7; i++) {
		uint8_t prev_x = x;
		uint8_t prev_y = y;
		switch (right_edge_dir) {
		case up:
			search_clockwise ? x++ : x--;
			break;
		case up_left:
			search_clockwise ? x++ : y++;
			break;
		case left:
			search_clockwise ? y-- : y++;
			break;
		case down_left:
			search_clockwise ? y-- : x++;
			break;
		case down:
			search_clockwise ? x-- : x++;
			break;
		case down_right:
			search_clockwise ? x-- : y--;
			break;
		case right:
			search_clockwise ? y++ : y--;
			break;
		case up_right:
			search_clockwise ? y++ : x--;
			break;
		}
		switch (util::camera_point_check(cam_buff, x, y)) {
		case 0:
			if (!search_clockwise) {
				coor edge;
				edge.x = x;
				edge.y = y;
				right_edge.push_back(edge);
				return true;
			}
			break;
		case 1:
			if (search_clockwise) {
				coor edge;
				edge.x = prev_x;
				edge.y = prev_y;
				right_edge.push_back(edge);
				return true;
			}
			break;
		case 2:
			return false;
			break;
		}
		search_clockwise ? right_edge_dir-- : right_edge_dir++;
		if (right_edge_dir < 0) {
			right_edge_dir = up_right;
		} else if (right_edge_dir > up_right) {
			right_edge_dir = up;
		}
	}
	return false;
}

bool find_left_corner() {
	coor new_edge = left_edge.back();
	coor old_edge = left_edge[left_edge.size() - 2];
	int16_t new_x = new_edge.x, new_y = new_edge.y;
	int16_t old_x = old_edge.x, old_y = old_edge.y;
	if (left_corner_points) {
		switch (left_edge_dir) {
		case up:
			for (int i = new_x - corner_window_size; i <= new_x + corner_window_size; i++)
				left_corner_points += util::simple_camera_point_check(cam_buff, i, new_y - corner_window_size);
			for (int i = old_x - corner_window_size; i <= old_x + corner_window_size; i++)
				left_corner_points -= util::simple_camera_point_check(cam_buff, i, old_y + corner_window_size);
			break;
		case up_left:
			for (int i = new_x - corner_window_size + 1; i <= new_x + corner_window_size; i++)
				left_corner_points += util::simple_camera_point_check(cam_buff, i, new_y - corner_window_size);
			for (int j = new_y - corner_window_size; j <= new_y + corner_window_size; j++)
				left_corner_points += util::simple_camera_point_check(cam_buff, new_x - corner_window_size, j);
			for (int i = old_x - corner_window_size; i <= old_x + corner_window_size; i++)
				left_corner_points -= util::simple_camera_point_check(cam_buff, i, old_y + corner_window_size);
			for (int j = old_y - corner_window_size; j < old_y + corner_window_size; j++)
				left_corner_points -= util::simple_camera_point_check(cam_buff, old_x + corner_window_size, j);
			break;
		case left:
			for (int j = new_y - corner_window_size; j <= new_y + corner_window_size; j++)
				left_corner_points += util::simple_camera_point_check(cam_buff, new_x - corner_window_size, j);
			for (int j = old_y - corner_window_size; j <= old_y + corner_window_size; j++)
				left_corner_points -= util::simple_camera_point_check(cam_buff, old_x + corner_window_size, j);
			break;
		case down_left:
			for (int i = new_x - corner_window_size; i <= new_x + corner_window_size; i++)
				left_corner_points += util::simple_camera_point_check(cam_buff, i, new_y + corner_window_size);
			for (int j = new_y - corner_window_size; j < new_y + corner_window_size; j++)
				left_corner_points += util::simple_camera_point_check(cam_buff, new_x - corner_window_size, j);
			for (int i = old_x - corner_window_size; i < old_x + corner_window_size; i++)
				left_corner_points -= util::simple_camera_point_check(cam_buff, i, old_y - corner_window_size);
			for (int j = old_y - corner_window_size; j <= old_y + corner_window_size; j++)
				left_corner_points -= util::simple_camera_point_check(cam_buff, old_x + corner_window_size, j);
			break;
		case down:
			for (int i = new_x - corner_window_size; i <= new_x + corner_window_size; i++)
				left_corner_points += util::simple_camera_point_check(cam_buff, i, new_y + corner_window_size);
			for (int i = old_x - corner_window_size; i <= old_x + corner_window_size; i++)
				left_corner_points -= util::simple_camera_point_check(cam_buff, i, old_y - corner_window_size);
			break;
		case down_right:
			for (int i = new_x - corner_window_size; i < new_x + corner_window_size; i++)
				left_corner_points += util::simple_camera_point_check(cam_buff, i, new_y + corner_window_size);
			for (int j = new_y - corner_window_size; j <= new_y + corner_window_size; j++)
				left_corner_points += util::simple_camera_point_check(cam_buff, new_x + corner_window_size, j);
			for (int i = old_x - corner_window_size + 1; i <= old_x + corner_window_size; i++)
				left_corner_points -= util::simple_camera_point_check(cam_buff, i, old_y - corner_window_size);
			for (int j = old_y - corner_window_size; j <= old_y + corner_window_size; j++)
				left_corner_points -= util::simple_camera_point_check(cam_buff, old_x - corner_window_size, j);
			break;
		case right:
			for (int j = new_y - corner_window_size; j <= new_y + corner_window_size; j++)
				left_corner_points += util::simple_camera_point_check(cam_buff, new_x + corner_window_size, j);
			for (int j = old_y - corner_window_size; j <= old_y + corner_window_size; j++)
				left_corner_points -= util::simple_camera_point_check(cam_buff, old_x - corner_window_size, j);
			break;
		case up_right:
			for (int i = new_x - corner_window_size; i < new_x + corner_window_size; i++)
				left_corner_points += util::simple_camera_point_check(cam_buff, i, new_y - corner_window_size);
			for (int j = new_y - corner_window_size; j <= new_y + corner_window_size; j++)
				left_corner_points += util::simple_camera_point_check(cam_buff, new_x + corner_window_size, j);
			for (int i = old_x - corner_window_size; i <= old_x + corner_window_size; i++)
				left_corner_points -= util::simple_camera_point_check(cam_buff, i, old_y + corner_window_size);
			for (int j = old_y - corner_window_size; j < old_y + corner_window_size; j++)
				left_corner_points -= util::simple_camera_point_check(cam_buff, old_x - corner_window_size, j);
			break;
		}
	} else {
		for (uint8_t y = 0; y <= corner_window_size; y++) {
			for (uint8_t x = 0; x <= corner_window_size; x++) {
				left_corner_points += util::simple_camera_point_check(cam_buff, new_x - x, new_y - y);
			}
		}
		for (uint8_t y = 0; y <= corner_window_size; y++) {
			for (uint8_t x = 1; x <= corner_window_size; x++) {
				left_corner_points += util::simple_camera_point_check(cam_buff, new_x + x, new_y - y);
			}
		}
		for (uint8_t y = 1; y <= corner_window_size; y++) {
			for (uint8_t x = 0; x <= corner_window_size; x++) {
				left_corner_points += util::simple_camera_point_check(cam_buff, new_x - x, new_y + y);
			}
		}
		for (uint8_t y = 1; y <= corner_window_size; y++) {
			for (uint8_t x = 1; x <= corner_window_size; x++) {
				left_corner_points += util::simple_camera_point_check(cam_buff, new_x + x, new_y + y);
			}
		}
	}
	if (left_corner_points > corner_min && left_corner_points < corner_max) {
		corner_pos[0].x = new_x;
		corner_pos[0].y = new_y;
		return true;
	}
	return false;
}

bool find_right_corner() {
	coor new_edge = right_edge.back();
	coor old_edge = right_edge[left_edge.size() - 2];
	int16_t new_x = new_edge.x, new_y = new_edge.y;
	int16_t old_x = old_edge.x, old_y = old_edge.y;
	if (right_corner_points) {
		switch (right_edge_dir) {
		case up:
			for (int i = new_x - corner_window_size; i <= new_x + corner_window_size; i++)
				right_corner_points += util::simple_camera_point_check(cam_buff, i, new_y - corner_window_size);
			for (int i = old_x - corner_window_size; i <= old_x + corner_window_size; i++)
				right_corner_points -= util::simple_camera_point_check(cam_buff, i, old_y + corner_window_size);
			break;
		case up_left:
			for (int i = new_x - corner_window_size + 1; i <= new_x + corner_window_size; i++)
				right_corner_points += util::simple_camera_point_check(cam_buff, i, new_y - corner_window_size);
			for (int j = new_y - corner_window_size; j <= new_y + corner_window_size; j++)
				right_corner_points += util::simple_camera_point_check(cam_buff, new_x - corner_window_size, j);
			for (int i = old_x - corner_window_size; i <= old_x + corner_window_size; i++)
				right_corner_points -= util::simple_camera_point_check(cam_buff, i, old_y + corner_window_size);
			for (int j = old_y - corner_window_size; j < old_y + corner_window_size; j++)
				right_corner_points -= util::simple_camera_point_check(cam_buff, old_x + corner_window_size, j);
			break;
		case left:
			for (int j = new_y - corner_window_size; j <= new_y + corner_window_size; j++)
				right_corner_points += util::simple_camera_point_check(cam_buff, new_x - corner_window_size, j);
			for (int j = old_y - corner_window_size; j <= old_y + corner_window_size; j++)
				right_corner_points -= util::simple_camera_point_check(cam_buff, old_x + corner_window_size, j);
			break;
		case down_left:
			for (int i = new_x - corner_window_size; i <= new_x + corner_window_size; i++)
				right_corner_points += util::simple_camera_point_check(cam_buff, i, new_y + corner_window_size);
			for (int j = new_y - corner_window_size; j < new_y + corner_window_size; j++)
				right_corner_points += util::simple_camera_point_check(cam_buff, new_x - corner_window_size, j);
			for (int i = old_x - corner_window_size; i < old_x + corner_window_size; i++)
				right_corner_points -= util::simple_camera_point_check(cam_buff, i, old_y - corner_window_size);
			for (int j = old_y - corner_window_size; j <= old_y + corner_window_size; j++)
				right_corner_points -= util::simple_camera_point_check(cam_buff, old_x + corner_window_size, j);
			break;
		case down:
			for (int i = new_x - corner_window_size; i <= new_x + corner_window_size; i++)
				right_corner_points += util::simple_camera_point_check(cam_buff, i, new_y + corner_window_size);
			for (int i = old_x - corner_window_size; i <= old_x + corner_window_size; i++)
				right_corner_points -= util::simple_camera_point_check(cam_buff, i, old_y - corner_window_size);
			break;
		case down_right:
			for (int i = new_x - corner_window_size; i < new_x + corner_window_size; i++)
				right_corner_points += util::simple_camera_point_check(cam_buff, i, new_y + corner_window_size);
			for (int j = new_y - corner_window_size; j <= new_y + corner_window_size; j++)
				right_corner_points += util::simple_camera_point_check(cam_buff, new_x + corner_window_size, j);
			for (int i = old_x - corner_window_size + 1; i <= old_x + corner_window_size; i++)
				right_corner_points -= util::simple_camera_point_check(cam_buff, i, old_y - corner_window_size);
			for (int j = old_y - corner_window_size; j <= old_y + corner_window_size; j++)
				right_corner_points -= util::simple_camera_point_check(cam_buff, old_x - corner_window_size, j);
			break;
		case right:
			for (int j = new_y - corner_window_size; j <= new_y + corner_window_size; j++)
				right_corner_points += util::simple_camera_point_check(cam_buff, new_x + corner_window_size, j);
			for (int j = old_y - corner_window_size; j <= old_y + corner_window_size; j++)
				right_corner_points -= util::simple_camera_point_check(cam_buff, old_x - corner_window_size, j);
			break;
		case up_right:
			for (int i = new_x - corner_window_size; i < new_x + corner_window_size; i++)
				right_corner_points += util::simple_camera_point_check(cam_buff, i, new_y - corner_window_size);
			for (int j = new_y - corner_window_size; j <= new_y + corner_window_size; j++)
				right_corner_points += util::simple_camera_point_check(cam_buff, new_x + corner_window_size, j);
			for (int i = old_x - corner_window_size; i <= old_x + corner_window_size; i++)
				right_corner_points -= util::simple_camera_point_check(cam_buff, i, old_y + corner_window_size);
			for (int j = old_y - corner_window_size; j < old_y + corner_window_size; j++)
				right_corner_points -= util::simple_camera_point_check(cam_buff, old_x - corner_window_size, j);
			break;
		}
	} else {
		for (uint8_t y = 0; y <= corner_window_size; y++) {
			for (uint8_t x = 0; x <= corner_window_size; x++) {
				right_corner_points += util::simple_camera_point_check(cam_buff, new_x - x, new_y - y);
			}
		}
		for (uint8_t y = 0; y <= corner_window_size; y++) {
			for (uint8_t x = 1; x <= corner_window_size; x++) {
				right_corner_points += util::simple_camera_point_check(cam_buff, new_x + x, new_y - y);
			}
		}
		for (uint8_t y = 1; y <= corner_window_size; y++) {
			for (uint8_t x = 0; x <= corner_window_size; x++) {
				right_corner_points += util::simple_camera_point_check(cam_buff, new_x - x, new_y + y);
			}
		}
		for (uint8_t y = 1; y <= corner_window_size; y++) {
			for (uint8_t x = 1; x <= corner_window_size; x++) {
				right_corner_points += util::simple_camera_point_check(cam_buff, new_x + x, new_y + y);
			}
		}
	}
	if (right_corner_points > corner_min && right_corner_points < corner_max) {
		corner_pos[1].x = new_x;
		corner_pos[1].y = new_y;
		return true;
	}
	return false;
}

void algo() {
	left_edge_dir = up;
	right_edge_dir = up;
	left_corner_points = 0;
	right_corner_points = 0;
	for (uint8_t i = cam_height - 10; i > 0; i--) {
		for (uint8_t j = cam_width / 2; j > 0; j--) {
			switch (util::camera_point_check(cam_buff, j, i)) {
			case 1:
				coor edge;
				edge.x = j + 1;
				edge.y = i;
				left_edge.push_back(edge);
				goto end_left_edge;
				break;
			case 2:
				goto end_left_edge;
				break;
			default:
				break;
			}
		}
		end_left_edge: for (uint8_t j = cam_width / 2; j < cam_width; j++) {
			switch (util::camera_point_check(cam_buff, j, i)) {
			case 1:
				coor edge;
				edge.x = j - 1;
				edge.y = i;
				right_edge.push_back(edge);
				goto end_right_edge;
				break;
			case 2:
				goto end_right_edge;
				break;
			default:
				break;
			}
		}
		end_right_edge: if (left_edge.size() || right_edge.size()) {
			break;
		}
	}
	bool find_right = true;
	bool find_left = true;
	while (find_left || find_right) {
		if (find_left) {
			find_left = find_left_edge();
			if (find_left)
				find_left = !find_left_corner();
		}
		if (find_right) {
			find_right = find_right_edge();
			if (find_right)
				find_right = !find_right_corner();
		}
	}
}
