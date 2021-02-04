#include "core.h"
#include "game_level.h"
#include "ddraw_func.h"
#include "draw_img.h"
#include "draw_text.h"
#include "keyboard.h"
#include "levels.h"
#include "mouse.h"
#include "palette.h"
#include "timers.h"

uint8_t GAME_IS_PLAYING;

File GAMEPAL_PAL;

//0044771C
int32_t game_level() 
{
    uint8_t black_pal[770];
    int32_t ret_code = NO_EXIT_ROOM;

    draw_cursor_by_timer();
    set_cursor_icon(ICON_WAIT);
    draw_IMG_on_screen(0, 0, 0, 0, LOAD_US_BIN.get_ptr());
    set_palette(LOADPALU_PAL.get_ptr());
    draw_text("Loading", FULLFONT_BIN.get_ptr(), 180, 130);
    draw_text("Please Wait", FULLFONT_BIN.get_ptr(), 210, 130);
    redraw();
    // ----loading splashscreen. heavy load here----

    GAMEPAL_PAL.load("GAMEGFX/GAMEPAL.PAL");

    memset(black_pal, 0, sizeof(black_pal));
    unlock_surface_and_wait(100);


    // -----loading is over---------
    swap_palette_with_animation(black_pal, 40);
    wait_palette_animation(0);
    clear_screen();
    draw_IMG_on_screen(1, 0, 0, 480, GENERAL_BIN.get_ptr());
    redraw();
    swap_palette_with_animation(GAMEPAL_PAL.get_ptr(), 60);

    GAME_IS_PLAYING = 1;
    while (ret_code == NO_EXIT_ROOM) {
        //draw_cursor_by_timer();
        // draw sidebar
        draw_IMG_on_screen(1, 0, 0, 480, GENERAL_BIN.get_ptr());
        redraw();


        // exit
        if (KEY_ESC) {
            GAME_IS_PLAYING = 0;
            KEY_ESC = 0;
            ret_code = MAIN_MENU;
        }

        // waiting 50ms
        while(GAME_UPDATE_TIMER < 5) {
            ;
        }
        GAME_UPDATE_TIMER = 0;
    }
    return ret_code;
}
