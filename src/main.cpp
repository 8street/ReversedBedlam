#include <process.h>

#include "core.h"
#include "ddraw_func.h"
#include "main.h"
#include "window.h"
#include "timers.h"


DWORD GAME_THREAD_ID;
HANDLE HANDLE_GAME_THREAD;

//0044D6E8
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{

    SURFACE_NEED_UNLOCK = 1;
    int32_t error_code = init_window(hInstance, hPrevInstance, lpCmdLine);

    if (!error_code)
    {
        if (game_thread_create())
        {
            error_code = 4;
        }
        else
        {
            error_code = init_timer();
            if (!error_code)
            {
                error_code = static_cast<int>(message_dispatcher());
                timeKillEvent((UINT)TIMER_EVENT);
                timeEndPeriod((UINT)TIMER_RESOLUTION);
            }
            game_thread_exit();
        }

    }

    return error_code;
}

//0044D9C0
int16_t game_thread_create()
{
    int16_t retVal; // ax

    //thread_flag_ = 0;
    HANDLE_GAME_THREAD = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)game_thread_start_func, NULL, 0, &GAME_THREAD_ID);
    retVal = GAME_THREAD_ID == -1;
    return retVal;
}

//0044DA1C
void game_thread_exit()
{
    if (GAME_THREAD_ID != -1)
    {
        SuspendThread(HANDLE_GAME_THREAD);
        TerminateThread(HANDLE_GAME_THREAD, 0);
        Sleep(500);
        GAME_THREAD_ID = -1;
    }
}

//0044DEA0
void game_thread_start_func()
{
    int32_t exit_code; // ax

    exit_code = game_core();
    //if (exit_code)
    //{
    //    HIBYTE(exit_code) += 64;
    //    LOWORD(surface_need_unlock) = exit_code;
    //}
    GAME_THREAD_ID = -1;
    SendMessageA(WINDOW_HWND, WM_DESTROY, 0, 0);
}
