
#include "mouse.h"

int16_t CURSOR_X1;
int16_t CURSOR_Y1;

int32_t CURSOR_ICON2;

//00425AB9
//void mouse_update()
//{
//    LONG v0; // edx
//    LONG v1; // ecx
//    int v2; // ecx
//    int icon; // eax
//    LONG pos_x; // [esp+0h] [ebp-1Ch] BYREF
//    LONG pos_y; // [esp+4h] [ebp-18h] OVERLAPPED BYREF
//    LONG pos_y_12; // [esp+10h] [ebp-Ch]
//    LONG pos_y_16; // [esp+14h] [ebp-8h]
//
//    pos_y_16 = v1;
//    pos_y_12 = v0;
//    //if ((mouse_buttons_state1 & 2) != 0)
//    //    dword_4EDE60 = 1;
//    v2 = mouse_r_button_up;
//    if (!mouse_r_button_up)
//    {
//        if ((mouse_buttons_state1 & 3) != 0)
//        {
//            if (dword_4EDB48)
//            {
//                mouse_r_button_up = 1;
//                dword_4EDB48 = v2;
//            }
//        }
//        else
//        {
//            dword_4EDB48 = 1;
//        }
//    }
//    mouse_buttons_state1 = mouse_buttons_state;
//    get_cursor_pos(&pos_x, &pos_y);
//    pos_x += 9;
//    pos_y += 9;
//    if (pos_x < 9)
//        pos_x = 9;
//    if (pos_x > 631)
//        pos_x = 631;
//    if (pos_y < 9)
//        pos_y = 9;
//    if (pos_y > 463)
//        pos_y = 463;
//    cursor_pos_x = pos_x;
//    cursor_pos_y = pos_y;
//    if ((mouse_buttons_state1 & 1) != 0)
//    {
//        cursor_pos_lclick_x = cursor_pos_x;
//        cursor_pos_lclick_y = cursor_pos_y;
//    }
//    if ((mouse_buttons_state1 & 2) != 0)
//    {
//        cursor_pos_rclick_x = cursor_pos_x;
//        cursor_pos_rclick_y = cursor_pos_y;
//    }
//    if (game_is_playing)
//    {
//        if (cursor_pos_x < 480)
//            icon = 0;
//        else
//            icon = 93;
//        set_cursor_icon((_BYTE*)icon);
//    }
//}
