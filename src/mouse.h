#pragma once

#include <stdint.h>

extern int16_t CURSOR_X1;
extern int16_t CURSOR_Y1;

extern int32_t CURSOR_ICON;
extern int32_t CURSOR_ICON2;

extern uint16_t CURSOR_SURFACE_SIZE;

extern uint8_t UPDATE_CURSOR_BY_TIMER;
extern uint8_t CURSOR_BY_TIMER;

extern uint32_t CURSOR_UNKNOWN;
extern uint8_t CURSOR_IS_BLITTING;

extern int32_t MOUSE_BUTTONS_STATE;
extern int32_t MOUSE_BUTTONS_STATE1;

extern int32_t CURSOR_POS_X;
extern int32_t CURSOR_POS_Y;

extern int32_t CURSOR_POS_LCLICK_X;
extern int32_t CURSOR_POS_LCLICK_Y;
extern int32_t CURSOR_POS_RCLICK_X;
extern int32_t CURSOR_POS_RCLICK_Y;

enum CURSOR_ICON {
    ICON_CROSSHAIR = 0,
    ICON_CURSOR = 93,
    ICON_WAIT = 144,
};


void mouse_update();
void set_cursor_icon(int32_t icon);
void set_cursor_surface_size(int16_t size);
int draw_cursor_one_time();
int blit_cursor_one_time();
void get_cursor_pos(LONG* x, LONG* y);
void draw_cursor_by_timer();
void set_update_cursor_by_timer();
void mouse_buttons(uint16_t r_butt, uint16_t l_button);
