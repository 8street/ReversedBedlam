#pragma once

#include <ddraw.h>
#include <stdint.h>
#include <Windows.h>

extern int32_t GAME_WIDTH;
extern int32_t GAME_HEIGHT;

extern uint8_t FULLSCREEN;
extern uint8_t SURFACE_IS_LOCKED;

extern uint16_t USE_VIDEOMEMORY;


extern LPDIRECTDRAWCLIPPER DDRAW_SURFACE_CLIPPER;

extern PALETTEENTRY PALETTEENTRY_BUFFER[258];

extern uint32_t SCREEN_SURFACE_WIDTH;
extern uint32_t SCREEN_SURFACE_HEIGHT;

extern uint8_t* SCREEN_BUFFER_PTR;

extern uint8_t IS_BLITTING;

int ddraw_init(HWND hWnd);
int create_surface_palette(int32_t width, int32_t height, int32_t depth);
HRESULT create_smack_buffer();
HRESULT create_mouse_buffer();
void clear_and_blit_screen();
HRESULT unlock_surface();
uint8_t* lock_and_get_surface_ptr();
int blit_cursor_bg_to_screen();
void blit_cursor_bg();
int blit_second_surface_to_screen();
int blit_cursor(int x, int y);
void activate_app(int32_t activate);
void get_screen_buffer_ptr();
HRESULT unlock_surface_and_screen_ptr();
HRESULT ddraw_setpalettes(uint8_t* pal_ptr, int16_t offset, int16_t num_entries);
void redraw();
void copy_buffer_to_screen_and_unlock(uint8_t* buffer);
void unlock_cursor_surface();
uint8_t* lock_and_get_cursor_surface();
HRESULT Set_Cursor_ColorKey(int16_t color_range);
void clear_screen();
