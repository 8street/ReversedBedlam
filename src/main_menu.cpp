
#include "ddraw_func.h"
#include "file.h"
#include "draw_img.h"
#include "main_menu.h"
#include "palette.h"

//0044A9AC
int32_t main_menu() {

    PALETTE_TIMER = 0;

    File pallete("D:\\games\\bedlam_cd\\GAMEGFX\\LOADPALU.PAL");
    File img("D:\\games\\bedlam_cd\\GAMEGFX\\LOAD_US.BIN");

    //File pallete("D:\\progi\\bedlam_cd\\GAMEGFX\\LOADPALU.PAL");
    //File img("D:\\progi\\bedlam_cd\\GAMEGFX\\LOAD_US.BIN");

    //File pallete("D:\\games\\bedlam_cd\\GAMEGFX\\BRFPAL.PAL");
    //File img("D:\\games\\bedlam_cd\\GAMEGFX\\BRF_B2.BIN");

    //set_palette(pallete.get_ptr());
    draw_IMG_on_screen(0, 1, 0, 0, img.get_ptr());
    swap_palette_with_animation(pallete.get_ptr(), 100);
    unlock_surface_and_screen_ptr();
    blit_second_surface_to_screen();
    wait_palette_animation(0);

    while (1) {

    }

return 0;
}
