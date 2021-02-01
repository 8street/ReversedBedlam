#pragma once
#include <stdint.h>

void draw_text(const char* bufer, uint8_t* bin_ptr, int32_t pos_y, int32_t font_offset);
int get_char_IMG_width(int32_t img_num, uint8_t* img_ptr);
char get_special_symbol_code(char in_char);
void draw_menu_text(int32_t selected, uint8_t* font_ptr);
