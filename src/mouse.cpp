

#include "core.h"
#include "ddraw_func.h"
#include "helper.h"
#include "mouse.h"
#include "window.h"


int16_t CURSOR_X1;
int16_t CURSOR_Y1;

int32_t CURSOR_ICON;
int32_t CURSOR_ICON2;

int16_t CURSOR_SURFACE_IS_LOCKED;

uint16_t CURSOR_SURFACE_SIZE;

uint8_t CURSOR_HIDDEN;
uint8_t CURSOR_IS_HIDDEN;

int32_t CURSOR_POS_X;
int32_t CURSOR_POS_Y;

uint32_t CURSOR_UNKNOWN;
uint8_t CURSOR_IS_BLITTING;

//00425AB9
void mouse_update()
{
    //int icon; // eax
    LONG pos_x; // [esp+0h] [ebp-1Ch] BYREF
    LONG pos_y; // [esp+4h] [ebp-18h] OVERLAPPED BYREF


    ////if ((mouse_buttons_state1 & 2) != 0)
    ////    dword_4EDE60 = 1;
    //v2 = mouse_r_button_up;
    //if (!mouse_r_button_up)
    //{
    //    if ((mouse_buttons_state1 & 3) != 0)
    //    {
    //        if (dword_4EDB48)
    //        {
    //            mouse_r_button_up = 1;
    //            dword_4EDB48 = v2;
    //        }
    //    }
    //    else
    //    {
    //        dword_4EDB48 = 1;
    //    }
    //}
    //mouse_buttons_state1 = mouse_buttons_state;
    get_cursor_pos(&pos_x, &pos_y);
    pos_x += 9;
    pos_y += 9;
    if (pos_x < 9)
        pos_x = 9;
    if (pos_x > 631)
        pos_x = 631;
    if (pos_y < 9)
        pos_y = 9;
    if (pos_y > 463)
        pos_y = 463;
    CURSOR_POS_X = pos_x;
    CURSOR_POS_Y = pos_y;
    //if ((mouse_buttons_state1 & 1) != 0)
    //{
    //    cursor_pos_lclick_x = CURSOR_POS_X;
    //    cursor_pos_lclick_y = CURSOR_POS_Y;
    //}
    //if ((mouse_buttons_state1 & 2) != 0)
    //{
    //    cursor_pos_rclick_x = CURSOR_POS_X;
    //    cursor_pos_rclick_y = CURSOR_POS_Y;
    //}
    
    //if (game_is_playing)
    //{
    //    if (CURSOR_POS_X < 480)
    //        icon = 0;
    //    else
    //        icon = 93;
    //    set_cursor_icon((_BYTE*)icon);
    //}
}

//0041D714
void set_cursor_icon(int32_t icon)
{
    uint8_t* cursor_surface; // ebp
    uint8_t* pos; // edi
    uint8_t* cursor_pos; // edx
    int i; // esi
    uint8_t* line; // eax
    int icon1; // [esp+0h] [ebp-20h]
    uint8_t* cursor_pos1; // [esp+4h] [ebp-1Ch]
    uint8_t* general;

    icon1 = icon;
    if (icon != CURSOR_ICON)
    {

        if (CURSOR_SURFACE_IS_LOCKED != 1)
        {
            CURSOR_SURFACE_IS_LOCKED = 1;
            show_cursor(24);
            Set_Cursor_ColorKey(0);
            if (icon >= 144 && icon < 152)
            {
                cursor_surface = lock_and_get_cursor_surface();
                if (!cursor_surface) {
                    return;
                }

            }
            else
            {
                cursor_surface = NULL;
                while (!cursor_surface) {
                    cursor_surface = lock_and_get_cursor_surface();
                }

            }
            clear_buffer(1024u, cursor_surface);
            pos = cursor_surface + 24;
            general = general_bin.get_ptr();
            cursor_pos = &general[4 * icon1 + 8 + *(uint32_t*)&general[4 * icon1 + 2]];
            for (i = 0; i < 24; ++i)
            {
                cursor_pos1 = cursor_pos;
                line = &cursor_surface[32 * i];
                do {
                    *line++ = *cursor_pos++;
                } while (line != pos);
                pos += 32;
                cursor_pos = cursor_pos1 + 24;
            }
            unlock_cursor_surface();
            icon = icon1;
            CURSOR_ICON = icon1;
            CURSOR_ICON2 = icon1;
            CURSOR_SURFACE_IS_LOCKED = 0;
        }
    }
}

//0044BBAC
void show_cursor(int16_t size)
{
    __int16 hidden; // bx
    int result; // eax

    hidden = CURSOR_HIDDEN;
    if (CURSOR_HIDDEN == 1)
    {
        CURSOR_HIDDEN = 0;
        blit_cursor_bg_to_screen();
    }
    result = hidden;
    CURSOR_SURFACE_SIZE = size;
    if (hidden == 1)
    {
        CURSOR_X1 = -1;
        CURSOR_HIDDEN = 1;
    }
}


//0042391D
int draw_cursor3()
{
    CURSOR_IS_HIDDEN = 0;
    return draw_cursor2();
}

//0044B3F8
int draw_cursor2()
{
    CURSOR_HIDDEN = 0;
    return blit_cursor_bg_to_screen();
}

//0044B428
void get_cursor_pos(LONG* x, LONG* y)
{
    struct tagPOINT cursor_pos; // [esp+0h] [ebp-1Ch] BYREF

    GetCursorPos(&cursor_pos);
    cursor_pos.x -= WINDOW_POS_X;
    cursor_pos.y -= WINDOW_POS_Y;
    cursor_pos.x = cursor_pos.x * GAME_WIDTH / WINDOW_WIDTH;
    cursor_pos.y = cursor_pos.y * GAME_HEIGHT / WINDOW_HEIGHT;
    if (cursor_pos.x < 0)
        cursor_pos.x = 0;
    if (cursor_pos.y < 0)
        cursor_pos.y = 0;
    if (cursor_pos.x >= WINDOW_WIDTH)
        cursor_pos.x = WINDOW_WIDTH - 1;
    if (cursor_pos.y >= WINDOW_HEIGHT)
        cursor_pos.y = WINDOW_HEIGHT - 1;
    *x = cursor_pos.x;
    *y = cursor_pos.y;
}

void set_and_hide_cursor()
{
    set_cursor_icon(CURSOR_ICON);
    CURSOR_IS_HIDDEN = 1;
    hide_cursor();
}

void hide_cursor()
{
    CURSOR_X1 = -1;
    CURSOR_HIDDEN = 1;
}
