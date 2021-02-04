#pragma once
#include <stdint.h>
#include <Windows.h>

extern uint32_t TIMER_RESOLUTION;
extern MMRESULT TIMER_EVENT;

extern int32_t WAITING_TIMER;
extern int32_t BUTTON_TIMER;
extern int32_t GAME_UPDATE_TIMER;

int init_timer();
void timer_callback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
void timer_update();
void increment_timers();
void unlock_surface_and_wait(int32_t time_to_waiting);
