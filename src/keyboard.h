#pragma once
#include <stdint.h>

extern uint8_t PRESSED_KEY_ARR[257];

extern uint8_t KEY_ESC;
extern uint8_t KEY_F1;
extern uint8_t KEY_F2;
extern uint8_t KEY_F3;
extern uint8_t KEY_1;
extern uint8_t KEY_2;
extern uint8_t KEY_3;
extern uint8_t KEY_4;
extern uint8_t KEY_5;
extern uint8_t KEY_6;
extern uint8_t KEY_7;
extern uint8_t KEY_P;
extern uint8_t KEY_M;


void keyboard(uint8_t scan_code, uint8_t key_up);
