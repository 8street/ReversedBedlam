
#include "core.h"
#include "ddraw_func.h"
//#include "file.h"
#include "draw_img.h"
#include "draw_text.h"
#include "keyboard.h"
#include "map_room.h"
#include "mouse.h"
#include "palette.h"
#include "timers.h"

File SELECTOR_BIN("GAMEGFX/SELECTOR.BIN");
File SELECTOR_PAL("GAMEGFX/SELECTOR.PAL");
File SELDARK_PAL("GAMEGFX/SELDARK.PAL");
File SELMONT_BIN("GAMEGFX/SELMONT.BIN");

//0043E7D4
int32_t map_room() {
    uint8_t black_pal[770];
    uint8_t* background_pal = SELECTOR_PAL.get_ptr();

    memset(black_pal, 0, sizeof(black_pal));
    memcpy(background_pal + 674, FULLPAL_PAL.get_ptr() + 2, 96u);

    // draw loading screen
    set_cursor_icon(ICON_WAIT);
    draw_IMG_on_screen(0, 0, 0, 0, LOAD_US_BIN.get_ptr());
    set_palette(LOADPALU_PAL.get_ptr());
    draw_text("Loading", FULLFONT_BIN.get_ptr(), 180, 130);
    draw_text("Please Wait", FULLFONT_BIN.get_ptr(), 210, 130);
    redraw();
    // can remove waiting
    unlock_surface_and_wait(50);
    swap_palette_with_animation(black_pal, 10);
    wait_palette_animation(0);

    draw_cursor3();
    set_cursor_icon(ICON_CURSOR);

    clear_screen();
    draw_IMG_on_screen(0, 1, 0, 0, SELECTOR_BIN.get_ptr());
    redraw();

    swap_palette_with_animation(background_pal, 10);
    wait_palette_animation(0);

    while(1){

        draw_IMG_on_screen(0, 1, 0, 0, SELECTOR_BIN.get_ptr());
        
        set_cursor_icon(ICON_CURSOR);
        set_and_hide_cursor();

        redraw();

        if (KEY_ESC) {
            KEY_ESC = 0;
            return MAIN_MENU;
        }
    }

    return MAIN_MENU;
}
