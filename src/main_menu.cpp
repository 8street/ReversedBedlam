
#include "core.h"
#include "ddraw_func.h"
#include "file.h"
#include "draw_img.h"
#include "draw_text.h"
#include "main_menu.h"
#include "mouse.h"
#include "palette.h"


uint8_t buf[307200u];

//0044A9AC
int32_t main_menu() {

    PALETTE_TIMER = 0;



    draw_main_menu_background_IMG(load_us_bin.get_ptr(), loadpalu_pal.get_ptr(), buf);

    draw_text("Loading", fullfont_bin.get_ptr(), 180, 130);
    draw_text("Please wait", fullfont_bin.get_ptr(), 210, 130);
    set_cursor_icon(144);
    draw_cursor3();



    while (1) {
        set_cursor_icon(93);
        set_and_hide_cursor();
        unlock_surface_and_screen_ptr();
        redraw();
    }

return 0;
}
