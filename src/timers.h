#pragma once
#include <stdint.h>
#include <Windows.h>

extern uint32_t TIMER_RESOLUTION;
extern MMRESULT TIMER_EVENT;

int init_timer();
void timer_callback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
void timer_update();
void increment_timers();
