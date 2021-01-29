
#include "ddraw_func.h"
#include "mouse.h"
#include "palette.h"
#include "timers.h"


uint32_t TIMER_RESOLUTION;
MMRESULT TIMER_EVENT;

//0044DA64
int init_timer()
{
    // 10 ms
    TIMER_RESOLUTION = 10;
    //while (!thread_flag_)
    //    ;
    timeBeginPeriod(TIMER_RESOLUTION);
    TIMER_EVENT = timeSetEvent(TIMER_RESOLUTION, 0, (LPTIMECALLBACK)timer_callback, NULL, TIME_PERIODIC);
    return 0;
}

//0044DE58
void timer_callback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    struct tagPOINT cursor; // [esp+0h] [ebp-8h] BYREF

    timer_update();
    // Maybe never execute 
    if (*(int*)((char*)&DDRAW_SURFACE_CLIPPER + 2) >> 16 == 1)
    {
        //word_4EF708 = 0;
        GetCursorPos(&cursor);
        blit_cursor(cursor.x, cursor.y);
    }
}

//0041BFB6
void timer_update()
{

    //if (register_readed)
    //    sub_402BAC();
    increment_timers();
    //mouse_update();

    // animated cursor
    if (CURSOR_ICON2 >= 144 && CURSOR_ICON2 < 152 && (PALETTE_TIMER & 7) == 0)
    {
        ++CURSOR_ICON2;
        if (CURSOR_ICON2 == 151) {
            CURSOR_ICON2 = 144;
        }
        //set_cursor_icon(CURSOR_ICON2);
    }
}

//00402B0C
void increment_timers()
{
    //++timer1;
    //++PALETTE_TIMER;
    //++main_menu_timer;
    //++timer3;
    //++game_update_timer;
    //level_clock();
    if (PALETTE_TIMER)
    {
        palette_animation();
    }
}
