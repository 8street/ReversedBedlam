#pragma once

#include <stdint.h>

extern int16_t CURSOR_X1;
extern int16_t CURSOR_Y1;

extern int32_t CURSOR_ICON;
extern int32_t CURSOR_ICON2;

extern uint16_t CURSOR_SURFACE_SIZE;

extern uint8_t CURSOR_HIDDEN;
extern uint8_t CURSOR_IS_HIDDEN;

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
void show_cursor(int16_t size);
int draw_cursor3();
int draw_cursor2();
void get_cursor_pos(LONG* x, LONG* y);
void set_and_hide_cursor();
void hide_cursor();
void mouse_buttons(uint16_t r_butt, uint16_t l_button);
