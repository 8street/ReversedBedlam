#pragma once
#include <stdint.h>

#include "file.h"

extern File SELDARK_PAL;
extern File TXPAL3_PAL;

int32_t map_room();
void draw_doors(uint8_t* bin_ptr, uint8_t* buffer);
void draw_textbox_black_rectangle(int32_t y_max, int32_t x_max, uint8_t* pos);
void draw_missions(uint8_t* bin_ptr, uint8_t* screen_buf_ptr);
void draw_ended_missions(uint8_t* bin_ptr, uint8_t* scren_buf);
int32_t get_selected_level();
void draw_nascent_missions_contour(uint8_t* bin_ptr, uint8_t* scren_buf);
