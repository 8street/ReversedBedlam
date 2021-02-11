#pragma once
#include <stdint.h>

extern uint8_t GAME_IS_PLAYING;



extern uint8_t GAME_SCREEN_PTR[409600];

int32_t game_level();
void draw_all();
