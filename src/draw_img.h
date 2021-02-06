#pragma once
#include <stdint.h>

void draw_IMG_on_screen(int32_t image_number, int16_t transparent, int32_t y_pos, int32_t x_pos, uint8_t* bin_ptr);
void draw_main_menu_background_IMG(uint8_t* bin, uint8_t* palitra, uint8_t* buffer);
void draw_IMG_in_buffer(int32_t icon_number, int16_t transparent, int32_t x_pos, int32_t y_pos, uint8_t* buffer, uint8_t* bin_ptr);
int merge_IMG(int mission, int code, uint8_t* scren_buf, uint8_t* bin_ptr);

