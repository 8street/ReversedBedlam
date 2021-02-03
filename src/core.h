#pragma once
#include <stdint.h>

#include "file.h"

extern uint8_t BACKGROUND_BUF[307200u];

extern File GENERAL_BIN;
extern File LOAD_US_BIN;
extern File FULLFONT_BIN;

extern File LOADPALU_PAL;
extern File FULLPAL_PAL;

extern uint8_t DIFFICULTY;

extern std::string PLAYER_NAME;

extern int32_t GAME_MODE;




enum core_entry
{
    CLOSE_GAME = 0,
    MAIN_MENU,
    MAP_ROOM,
    SHOP_ROOM,
    BRIEFING_ROOM,
    GAME_LEVEL,
    NO_EXIT_ROOM,
};

int32_t game_core();
