

#include "core.h"
#include "ddraw_func.h"
#include "draw_img.h"
#include "main_menu.h"
#include "palette.h"

File general_bin("GAMEGFX/GENERAL.BIN");
File loadpalu_pal("GAMEGFX/LOADPALU.PAL");
File load_us_bin("GAMEGFX/LOAD_US.BIN");
File fullfont_bin("GAMEGFX/FULLFONT.BIN");

//0041C050
int32_t game_core() {
    
    main_menu();

    return 0;
}
