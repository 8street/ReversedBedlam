
#include "ddraw_func.h"
#include "file.h"
#include "draw_img.h"
#include "draw_text.h"
#include "main_menu.h"
#include "palette.h"

uint8_t buf[307200u];

//0044A9AC
int32_t main_menu() {

    PALETTE_TIMER = 0;

    File loadpalu("GAMEGFX/LOADPALU.PAL");
    File load_us("GAMEGFX/LOAD_US.BIN");
    File fullfont("GAMEGFX/FULLFONT.BIN");

    draw_main_menu_background_IMG(load_us.get_ptr(), loadpalu.get_ptr(), buf);

    draw_text("Loading", fullfont.get_ptr(), 180, 130);
    draw_text("Please wait", fullfont.get_ptr(), 210, 130);
    redraw();

    while (1) {

    }

return 0;
}
