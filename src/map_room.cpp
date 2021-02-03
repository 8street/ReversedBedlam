
#include "core.h"
#include "ddraw_func.h"
#include "draw_img.h"
#include "draw_text.h"
#include "keyboard.h"
#include "levels.h"
#include "map_room.h"
#include "mouse.h"
#include "palette.h"
#include "timers.h"

File SELECTOR_BIN;
File SELMONT_BIN;
File NORMAL_BIN;

File SELECTOR_PAL;
File SELDARK_PAL;
File TXPAL3_PAL;

int32_t Doors_frame;
int32_t Level_selected;

uint8_t buf[308480];

//0043E7D4
int32_t map_room() {
    int32_t ret_code = NO_EXIT_ROOM;
    uint8_t black_pal[770];
    int32_t blink_timer = 0;
    int32_t helper_timer = 0;
    // draw loading screen
    set_cursor_icon(ICON_WAIT);
    draw_IMG_on_screen(0, 0, 0, 0, LOAD_US_BIN.get_ptr());
    set_palette(LOADPALU_PAL.get_ptr());
    draw_text("Loading", FULLFONT_BIN.get_ptr(), 180, 130);
    draw_text("Please Wait", FULLFONT_BIN.get_ptr(), 210, 130);
    redraw();
    // loading splashscreen. heavy load here

    SELECTOR_BIN.load("GAMEGFX/SELECTOR.BIN");
    SELMONT_BIN.load("GAMEGFX/SELMONT.BIN");
    NORMAL_BIN.load("GAMEGFX/NORMAL.BIN");

    SELECTOR_PAL.load("GAMEGFX/SELECTOR.PAL");
    SELDARK_PAL.load("GAMEGFX/SELDARK.PAL");
    TXPAL3_PAL.load("GAMEGFX/TXPAL3.PAL");

    uint8_t* background_pal = SELECTOR_PAL.get_ptr();

    memset(BACKGROUND_BUF, 0, sizeof(BACKGROUND_BUF));
    memset(black_pal, 0, sizeof(black_pal));
    memcpy(background_pal + 674, FULLPAL_PAL.get_ptr() + 2, 96u);

    // test
    ZONE_ARR[0].m_ended = 1;
    ZONE_ARR[1].m_ended = 1;
    ZONE = 2;
    ZONE_LEVEL = 3;

    draw_IMG_in_buffer(0, 1, 0, 0, buf, SELECTOR_BIN.get_ptr());
    draw_textbox_black_rectangle(119, 205, buf + 641);
    draw_ended_missions(NORMAL_BIN.get_ptr(), buf);

    // loading is over
    swap_palette_with_animation(black_pal, 10);
    wait_palette_animation(0);

    draw_cursor_one_time();
    set_cursor_icon(ICON_CURSOR);

    clear_screen();
    draw_IMG_in_buffer(0, 1, 0, 0, BACKGROUND_BUF, SELECTOR_BIN.get_ptr());
    draw_textbox_black_rectangle(119, 205, BACKGROUND_BUF + 641);
    copy_buffer_to_screen_and_unlock(BACKGROUND_BUF);
    redraw();

    swap_palette_with_animation(background_pal, 10);
    wait_palette_animation(0);

    while(ret_code == NO_EXIT_ROOM){
        draw_IMG_in_buffer(0, 1, 0, 0, BACKGROUND_BUF, SELECTOR_BIN.get_ptr());
        
        draw_textbox_black_rectangle(119, 205, BACKGROUND_BUF + 641);

        set_cursor_icon(ICON_CURSOR);
        draw_cursor_by_timer();

        draw_doors(SELECTOR_BIN.get_ptr(), BACKGROUND_BUF);

        //draw_missions_contour(NORMAL_BIN.get_ptr(), BACKGROUND_BUF);
        draw_ended_missions(NORMAL_BIN.get_ptr(), BACKGROUND_BUF);

        // blink selected
        int32_t level_num = get_level_number(ZONE, ZONE_LEVEL);
        int32_t selected_mission = 0;
        int32_t code;
        if (level_num != -1 && !ZONE_ARR[level_num].m_ended)
        {
            Level_selected = 1;
            if (ZONE == 1)
                selected_mission = 0;
            else
                selected_mission = ZONE_LEVEL + 5 * (ZONE - 2);
            if ((helper_timer & 7u) > 2)
                code = 300;
            else
                code = 304;
            merge_IMG(selected_mission, code, BACKGROUND_BUF, NORMAL_BIN.get_ptr());
        }
        helper_timer++;

        copy_buffer_to_screen_and_unlock(BACKGROUND_BUF);
        redraw();

        // not working yet
        uint8_t v10 = 0;
        int32_t var = 2;
        int32_t game_mode1 = GAME_MODE;
        if (MOUSE_BUTTONS_STATE1) //&& !num_players_maybe)
        {

            v10 = buf[640 * CURSOR_POS_Y + CURSOR_POS_X + 641];
            if (GAME_MODE == 2)
            {
                if (v10 && v10 <= 2)
                    goto LABEL_47;
                if (v10 >= 3u && v10 <= 4u)
                {
                    v10 -= 2;
                    ZONE = 3;
                    goto LABEL_84;
                }
                if (v10 >= 5u && v10 <= 6u)
                {
                    game_mode1 = 4;
                    v10 -= 4;
                LABEL_47:
                    ZONE = game_mode1;
                LABEL_84:
                    ZONE_LEVEL = v10;
                    goto LABEL_85;
                }
                if (v10 >= 7u && v10 <= 8u)
                {
                    v10 -= 6;
                    ZONE = 5;
                    goto LABEL_84;
                }
                if (v10 >= 9u && v10 <= 0xAu)
                {
                    v10 -= 8;
                    ZONE = 6;
                    goto LABEL_84;
                }
            }
            else if (v10 && v10 <= 1u && ZONE == 1)
            {
                ZONE_LEVEL = ZONE;
            }
            else
            {
                if (v10 >= 2u && v10 <= 6u && ZONE == 2)
                {
                    --v10;
                    goto LABEL_84;
                }
                if (v10 >= 7u && v10 <= 0xBu && ZONE == 3)
                {
                    v10 -= 6;
                    goto LABEL_84;
                }
                if (v10 >= 0xCu && v10 <= 0x10u && ZONE == 4)
                {
                    v10 -= 11;
                    goto LABEL_84;
                }
                if (v10 >= 0x11u && v10 <= 0x15u && ZONE == 5)
                {
                    v10 -= 16;
                    goto LABEL_84;
                }
                if (v10 >= 0x16u && v10 <= 0x1Au && ZONE == 6)
                {
                    v10 -= 21;
                    goto LABEL_84;
                }
            }
        }
        LABEL_85:

        // door click
        if (ZONE_LEVEL && MOUSE_BUTTONS_STATE1 && Doors_frame == 4)
        {
            // shoop door click
            if (CURSOR_POS_X > 227 && CURSOR_POS_X < 284 && CURSOR_POS_Y > 39 && CURSOR_POS_Y < 128)
            {
                //play_sound(beep1_raw, -1, -1, 2);
                ret_code = SHOP_ROOM;
            }
            // briefing door click
            if (ZONE > 1 && GAME_MODE != 2 
            && CURSOR_POS_X > 458 && CURSOR_POS_X < 542 && CURSOR_POS_Y > 41 && CURSOR_POS_Y < 176)
            {
                //play_sound(beep1_raw, -1, -1, 2);
                ret_code = BRIEFING_ROOM;
            }
        }
        // exit
        if (KEY_ESC) {
            KEY_ESC = 0;
            ret_code = MAIN_MENU;
        }
    }
    return ret_code;
}

//0043F4EE
void draw_doors(uint8_t* bin_ptr, uint8_t* buffer)
{
    int32_t door_img; // eax

    if (Level_selected)
        ++Doors_frame;
    else
        --Doors_frame;
    if (Doors_frame < 0)
        Doors_frame = 0;
    if (Doors_frame > 4)
        Doors_frame = 4;
    draw_IMG_in_buffer(2 * Doors_frame + 5, 1, 20, 218, buffer, bin_ptr);
    if (ZONE_LEVEL <= 1 || GAME_MODE == 2)
    {
        door_img = 6;
    }
    else
    {
        door_img = 2 * Doors_frame + 6;
    }
    draw_IMG_in_buffer(door_img, 1, 4, 447, buffer, bin_ptr);
}

//00402A56
void draw_textbox_black_rectangle(int32_t y_max, int32_t x_max, uint8_t* pos)
{
    uint8_t* darkpal = SELDARK_PAL.get_ptr();
    uint8_t pos_val = 0;
    uint8_t* pos_buf = pos;
    uint8_t* pos_start_line;

    for(int y = 0; y < y_max; y++) {
        pos_start_line = pos_buf;
        for (int x = 0; x < x_max; x++) {
            pos_val = *pos_buf;
            *pos_buf = darkpal[pos_val];
            pos_buf++;
        }
        pos_buf = pos_start_line;
        pos_buf += 640;
    }
}

//0043F4A4
void draw_missions_contour(uint8_t* bin_ptr, uint8_t* screen_buf_ptr)
{
    int32_t mission; // ebp

    if (GAME_MODE == 2)
    {
        for (mission = 0; mission < 10; mission++)
        {
            merge_IMG(mission, 302, screen_buf_ptr, bin_ptr);
        }
    }
    else
    {
        for (mission = 0; mission < 27; mission++)
        {
            merge_IMG(mission, 302, screen_buf_ptr, bin_ptr);
        }
    }
}

//0043F430
void draw_ended_missions(uint8_t* bin_ptr, uint8_t* scren_buf)
{
    int i; // ebp
    int mission; // eax
    int code; // ebx
    int zone1; // ebx

    if (GAME_MODE != 2)
    {
        for (i = 0; i < static_cast<int32_t>(ZONE_ARR.size()); i++)
        {
            zone1 = ZONE_ARR[i].m_zone;
            if (zone1 == 1) {
                mission = 0;
            }
            else {
                mission = ZONE_ARR[i].m_zone_level + 5 * (zone1 - 2);
            }
            if (ZONE_ARR[i].m_ended)
            {
                code = 303;
            }
            else
            {
                if (ZONE != ZONE_ARR[i].m_zone) {
                    continue;
                }
                code = 302;
            }
            merge_IMG(mission, code, scren_buf, bin_ptr);
        }
    }
}
