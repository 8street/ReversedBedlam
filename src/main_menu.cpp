

#include "core.h"
#include "ddraw_func.h"
#include "file.h"
#include "draw_img.h"
#include "draw_text.h"
#include "keyboard.h"
#include "main_menu.h"
#include "mouse.h"
#include "palette.h"
#include "timers.h"

uint8_t Background_buf[307200u];

std::vector<std::string> MENU_TEXT_ARR;

enum meny_type {
    UNKNOWN = 0,
    SINGLE_GAME,
    COOPERATIVE_GAME,
    LOAD_SAVE_GAME,
    LOAD_COOPERATIVE_GAME,
    EXIT_GAME,
};



//0044A9AC
int32_t main_menu() {
    int32_t exit = 0;
    int32_t map_room = 0;
    int32_t selected = -1;
    int32_t old_selected = -1;
    int32_t num_menu_lines = 0;
    int32_t menu_type = SINGLE_GAME;
    int32_t old_menu_type = -1;
    PALETTE_TIMER = 0;
    uint8_t white_text_pal[770];
    uint8_t black_text_pal[770];
    uint8_t* main_menu_palette = LOADPALU_PAL.get_ptr();
    
    memcpy(white_text_pal, main_menu_palette, 770);
    memcpy(black_text_pal, main_menu_palette, 770);
    for (int i = 0; i < 96; i++) {
        white_text_pal[i + 673] = 63;
    }
    for (int i = 0; i < 36; i++) {
        black_text_pal[i + 697] = 0;
    }

    draw_main_menu_background_IMG(LOAD_US_BIN.get_ptr(), main_menu_palette, Background_buf);

    while (!exit && !map_room) {

        // cursor
        set_cursor_icon(ICON_CURSOR);
        set_and_hide_cursor();

        // background
        copy_buffer_to_screen_and_unlock(Background_buf);

        // draw white fading menu text
        if (menu_type != old_menu_type) {
            construct_menu(menu_type);
            draw_menu_text(selected, FULLFONT_BIN.get_ptr());
            set_palette(white_text_pal);
            swap_palette_with_animation(main_menu_palette, 10);
            redraw();
            unlock_surface_and_wait(32);
            old_menu_type = menu_type;
        }

        // menu text
        construct_menu(menu_type);
        num_menu_lines = static_cast<int32_t>(MENU_TEXT_ARR.size());
        int32_t first_menu_entry_pos_y = 470 - 24 * num_menu_lines;
        if (CURSOR_POS_X <= 220 || CURSOR_POS_X >= 420 ||  CURSOR_POS_Y <= first_menu_entry_pos_y || CURSOR_POS_Y >= 470)
        {
            selected = -1;
        }
        else
        {
            selected = (CURSOR_POS_Y - first_menu_entry_pos_y) / 24;
            if (selected < 0) {
                selected = 0;
            }
            if (selected > num_menu_lines) {
                selected = num_menu_lines;
            }

        }
        draw_menu_text(selected, FULLFONT_BIN.get_ptr());
        // fade selected text
        if (selected != old_selected) {
            set_palette(black_text_pal);
            swap_palette_with_animation(main_menu_palette, 10);
            redraw();
            wait_palette_animation(0);
            old_selected = selected;
        }
        // drawing
        unlock_surface_and_screen_ptr();
        redraw();

        // click to menu item
        if (selected != -1 && MOUSE_BUTTONS_STATE1) {
            switch (menu_type)
            {
            case SINGLE_GAME:
                switch (selected) 
                {
                case -1:

                    break;
                case 0:
                    // Play Single game
                    map_room = 1;
                    break;
                case 1:
                    menu_type = LOAD_SAVE_GAME;
                    break;
                case 2:
                    DIFFICULTY++;
                    if (DIFFICULTY > 2) {
                        DIFFICULTY = 0;
                    }
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    menu_type = EXIT_GAME;
                    break;
                default:
                    break;
                }
                break;
            case COOPERATIVE_GAME:
                break;
            case LOAD_SAVE_GAME:
                switch (selected)
                {
                case -1:
                    break;
                case 0:
                    map_room = 1;
                    break;
                case 1:
                    map_room = 1;
                    break;
                case 2:
                    map_room = 1;
                    break;
                case 3:
                    map_room = 1;
                    break;
                case 4:
                    map_room = 1;
                    break;
                case 5:
                    menu_type = SINGLE_GAME;
                    break;
                default:
                    break;
                }
                break;
            case LOAD_COOPERATIVE_GAME:
                break;
            case EXIT_GAME:
                if (!selected) {
                    exit = 1;
                }
                if (selected == 1) {
                    menu_type = SINGLE_GAME;
                }
                break;
            default:
                break;
            }
            selected = -1;
            unlock_surface_and_wait(32);
        }

        //if (KEY_ESC) {
        //    exit = 1;
        //    KEY_ESC = 0;
        //}
    }

    if (map_room) {
        return MAP_ROOM;
    }
    else {
        return CLOSE_GAME;
    }
}

//00445B5C
void construct_menu(int32_t menu_type)
{
    //TODO: language selector

    MENU_TEXT_ARR.clear();

    switch (menu_type)
    {
    // Main menu
    case SINGLE_GAME:
        MENU_TEXT_ARR.push_back("New Single Player Game");
        MENU_TEXT_ARR.push_back("Start Saved Game");
        MENU_TEXT_ARR.push_back("Difficulty: " + get_difficulty_str(DIFFICULTY));
        MENU_TEXT_ARR.push_back("Name: " + PLAYER_NAME);
        MENU_TEXT_ARR.push_back("View Hall of Fame");
        MENU_TEXT_ARR.push_back("Credits");
        MENU_TEXT_ARR.push_back("Quit to Windows");
        break;

    // Start Cooperative Game
    case COOPERATIVE_GAME:
        MENU_TEXT_ARR.push_back("Start Cooperative Game");
        MENU_TEXT_ARR.push_back("Start Head2Head");
        //MENU_TEXT_ARR.push_back("Difficulty: STANDARD");
        //MENU_TEXT_ARR.push_back("Name: PLAYER");
        //MENU_TEXT_ARR.push_back("View Hall of Fame");
        //MENU_TEXT_ARR.push_back("Credits");
        MENU_TEXT_ARR.push_back("Quit to Windows");
        break;

    // Start Saved Game
    case LOAD_SAVE_GAME:
        MENU_TEXT_ARR.push_back("Player 1");
        MENU_TEXT_ARR.push_back("NONE");
        MENU_TEXT_ARR.push_back("NONE");
        MENU_TEXT_ARR.push_back("NONE");
        MENU_TEXT_ARR.push_back("NONE");
        MENU_TEXT_ARR.push_back("Main Menu");
        break;

    // Start cooperative saves maybe
    case LOAD_COOPERATIVE_GAME:

    // Quit to Windows
    case EXIT_GAME:
        MENU_TEXT_ARR.push_back("Quit to Windows");
        MENU_TEXT_ARR.push_back("Main Menu");
        break;

    default:
        exit(3);
        break;
    }
}

//00446522
std::string get_difficulty_str(uint8_t difficulty_num)
{
    // TODO: lang selector
    if (difficulty_num == 0) {
        return "SIMPLE";
    }
    if (difficulty_num == 1) {
        return "STANDARD";
    }
    if (difficulty_num == 2) {
        return "BEDLAM !!!";
    }
    return "";
}
