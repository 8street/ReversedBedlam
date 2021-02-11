#pragma once
#include <stdint.h>

typedef struct {
    uint8_t* screen_pos;
    int32_t x_tile;
    int32_t y_tile;
}tile;

extern tile TILE_BUFFER[1296];
extern uint8_t TOT_BUFFER[306000];
extern int32_t NUM_VISIBLE_TILES;

int32_t get_zone_water_img();
void draw_tile(int32_t img_num, int32_t ofst, uint8_t* palette, uint8_t* screen_pos, uint8_t* bin_ptr);
void init_tiles();
