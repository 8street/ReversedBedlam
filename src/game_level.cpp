#include "core.h"
#include "game_level.h"
#include "ddraw_func.h"
#include "draw_img.h"
#include "draw_text.h"
#include "helper.h"
#include "keyboard.h"
#include "levels.h"
#include "mouse.h"
#include "palette.h"
#include "tiles.h"
#include "timers.h"

uint8_t GAME_IS_PLAYING;


uint8_t GAME_SCREEN_PTR[409600];

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

    memset(black_pal, 0, sizeof(black_pal));

    load_mission_files();


    init_tiles();

    // -----loading is over---------
    swap_palette_with_animation(black_pal, 40);
    wait_palette_animation(0);
    clear_screen();
    draw_IMG_on_screen(1, 0, 0, 480, GENERAL_BIN.get_ptr());
    redraw();
    swap_palette_with_animation(GAMEPAL_PAL.get_ptr(), 60);

    GAME_IS_PLAYING = 1;
    while (ret_code == NO_EXIT_ROOM) {


        draw_all();
        // draw sidebar
        draw_IMG_on_screen(1, 0, 0, 480, GENERAL_BIN.get_ptr());

        redraw();
        // waiting 50ms
        while(GAME_UPDATE_TIMER < 5) {
            ;
        }
        GAME_UPDATE_TIMER = 0;

        // exit
        if (KEY_ESC) {
            GAME_IS_PLAYING = 0;
            KEY_ESC = 0;
            ret_code = MAIN_MENU;
        }
    }
    return ret_code;
}

//00403938
void draw_all() 
{
    static int32_t screen_x_tile;
    static int32_t screen_y_tile;

    //test
    if (KEY_1 && BUTTON_TIMER > 2) {
        screen_x_tile++;
        BUTTON_TIMER = 0;
        KEY_1 = 0;
    }

    if (KEY_2 && BUTTON_TIMER > 2) {
        screen_x_tile--;
        BUTTON_TIMER = 0;
        KEY_2 = 0;
    }

    if (KEY_3 && BUTTON_TIMER > 2) {
        screen_y_tile++;
        BUTTON_TIMER = 0;
        KEY_3 = 0;
    }

    if (KEY_4 && BUTTON_TIMER > 2) {
        screen_y_tile--;
        BUTTON_TIMER = 0;
        KEY_4 = 0;
    }

    uint8_t* game_screen_end_ptr = GAME_SCREEN_PTR + 367360;

    int32_t tile = 0;
    int32_t line_offset = -640 * 0;

    while (tile < NUM_VISIBLE_TILES)
    {
        uint8_t* pos = TILE_BUFFER[tile].screen_pos + line_offset;
        int32_t x_tile = screen_x_tile + TILE_BUFFER[tile].x_tile;
        int32_t y_tile = screen_y_tile + TILE_BUFFER[tile].y_tile;

        if (x_tile < 0 || x_tile >= MISSION_X_MAPSIZE || y_tile < 0 || y_tile >= MISSION_Y_MAPSIZE)
        {
            int32_t water_img = get_zone_water_img();
            if (pos >= GAME_SCREEN_PTR && pos < game_screen_end_ptr) {
                draw_tile(water_img, 0, 0, pos, MISSION_BIN.get_ptr());
            }
        }
        else 
        {
            for (int32_t z = 0; z < 8; z++)
            {
                int32_t tile_img = *(uint16_t*)&MISSION_TOT_PTR[2*(x_tile + MISSION_X_MAPSIZE * y_tile)+ 2*z*MISSION_SQUARE ];
                if (pos >= GAME_SCREEN_PTR && pos < game_screen_end_ptr && tile_img) {
                    draw_tile(tile_img, 0, 0, pos, MISSION_BIN.get_ptr());
                }
                pos += 20480; 
            }
            //int32_t tile_pos = x_tile + MISSION_X_MAPSIZE * y_tile;
            //for (int32_t z = 0; z < 8; z++)
            //{

            //    int32_t tot_ofst = 30 * tile_pos + 2 * z;
            //    int32_t tile_img = *(uint16_t*)&TOT_BUFFER[tot_ofst];

            //    if (pos >= GAME_SCREEN_PTR && pos < game_screen_end_ptr && tile_img) {
            //        draw_tile(tile_img, 0, 0, pos, MISSION_BIN.get_ptr());
            //    }
            //    pos = pos + 20480;
            //}
        }
        

        tile++;
    }


    get_screen_buffer_ptr();
    memcpy(SCREEN_BUFFER_PTR, GAME_SCREEN_PTR, SCREEN_SURFACE_WIDTH * GAME_HEIGHT);
    clear_buffer(sizeof(GAME_SCREEN_PTR), GAME_SCREEN_PTR);



}
