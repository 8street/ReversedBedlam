#pragma once
#include <stdint.h>

int32_t get_zone_water_img();
void draw_tile(int32_t img_num, int32_t ofst, uint8_t* palette, uint8_t* screen_pos, uint8_t* bin_ptr);
