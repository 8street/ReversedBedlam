
#include "briefing_room.h"
#include "core.h"
#include "ddraw_func.h"
#include "draw_img.h"
#include "game_level.h"
#include "main_menu.h"
#include "map_room.h"
#include "palette.h"
#include "shop_room.h"

File GENERAL_BIN("GAMEGFX/GENERAL.BIN");
File LOAD_US_BIN("GAMEGFX/LOAD_US.BIN");
File FULLFONT_BIN("GAMEGFX/FULLFONT.BIN");
File NORMAL_BIN("GAMEGFX/NORMAL.BIN");

File LOADPALU_PAL("GAMEGFX/LOADPALU.PAL");
File FULLPAL_PAL("GAMEGFX/FULLPAL.PAL");

uint8_t DIFFICULTY;

std::string PLAYER_NAME("PLAYER");

//0041C050
int32_t game_core() {

    int32_t entry = MAIN_MENU;

    while (entry) {
        switch (entry)
        {
        case MAIN_MENU:
            entry = main_menu();
            break;
        case MAP_ROOM:
            entry = map_room();
            break;
        case SHOP_ROOM:
            entry = shop_room();
            break;
        case BRIEFING_ROOM:
            entry = briefing_room();
            break;
        case GAME_LEVEL:
            entry = game_level();
            break;
        default:
            entry = CLOSE_GAME;
            break;
        }
    }

    return 0;
}
