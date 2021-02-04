
#include "ddraw_func.h"
#include "mouse.h"
#include "palette.h"
#include "timers.h"


uint32_t TIMER_RESOLUTION;
MMRESULT TIMER_EVENT;

int32_t WAITING_TIMER;
int32_t BUTTON_TIMER;
int32_t GAME_UPDATE_TIMER;

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

    if (UPDATE_CURSOR_BY_TIMER == 1 && !IS_BLITTING)
    {
        //word_4EF708 = 0;
        GetCursorPos(&cursor);
        blit_cursor(cursor.x, cursor.y);
    }
}

//0041BFB6
void timer_update()
{
    static uint32_t cursor_timer;

    cursor_timer++;
    //if (register_readed)
    //    sub_402BAC();
    increment_timers();
    mouse_update();

    // animated cursor
    if (CURSOR_ICON2 >= ICON_WAIT && CURSOR_ICON2 < 152 && (cursor_timer & 7) == 0)
    {
        ++CURSOR_ICON2;
        if (CURSOR_ICON2 == 151) {
            CURSOR_ICON2 = ICON_WAIT;
        }
        set_cursor_icon(CURSOR_ICON2);
    }
}

//00402B0C
void increment_timers()
{
    // not present in original function
    BUTTON_TIMER++;

    //timer1++;
    //PALETTE_TIMER++;
    WAITING_TIMER++;
    //timer3++;
    GAME_UPDATE_TIMER++;
    //level_clock();
    if (PALETTE_TIMER)
    {
        palette_animation();
    }
}

//0041E215
void unlock_surface_and_wait(int32_t time_to_waiting)
{
    unlock_surface_and_screen_ptr();
    WAITING_TIMER = 0;
    while (time_to_waiting > WAITING_TIMER) {
        ;
    }
}
