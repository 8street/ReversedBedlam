#include "ddraw_func.h"
#include "palette.h"

int32_t PALETTE_TIMER;
uint8_t ANIMATE_PALETTE_PTR[780];
uint8_t ANIMATE_PALETTE_BUFER[3082]; 
uint8_t GETTED_PALETTE[769];

//004258D0
void set_palette(uint8_t* pal_file)
{
    int16_t offset; // si
    int16_t num_entries; // dx
    uint8_t* pal_ptr; // ecx

    offset = pal_file[0];
    num_entries = pal_file[1];
    pal_ptr = pal_file + 2;
    if (!num_entries) {
        num_entries = 256;
    }
    unlock_surface_and_screen_ptr();
    ddraw_setpalettes(pal_ptr, offset, num_entries);
}

//00425901
void palette_animation()
{
    int ofst; // edx
    int buf_ofst; // ecx
    int16_t color; // bx

    ofst = 0;
    buf_ofst = 0;
    do
    {
        color = *(WORD*)&ANIMATE_PALETTE_BUFER[buf_ofst + 2] + *(WORD*)&ANIMATE_PALETTE_BUFER[buf_ofst];
        *(WORD*)&ANIMATE_PALETTE_BUFER[buf_ofst] = color;
        ANIMATE_PALETTE_PTR[ofst++] = HIBYTE(color);
        buf_ofst += 4;
    } while (ofst < 768);
    ddraw_setpalettes(ANIMATE_PALETTE_PTR, 0, 256);
    PALETTE_TIMER--;
}

//0041CBF0
void swap_palette_with_animation(uint8_t* palette_file_ptr, int time)
{
    uint8_t* palette_ptr; // edi
    uint8_t* buf_file; // ebx
    uint8_t* screen_palette_ptr; // ecx
    uint8_t* buf; // ebx
    int R_scr; // esi
    int R_in; // edx
    int value; // eax
    uint8_t* end_pallete; // [esp+0h] [ebp-1Ch]

    PALETTE_TIMER = 0;
    palette_ptr = palette_file_ptr + 2;
    buf_file = ANIMATE_PALETTE_BUFER;
    screen_palette_ptr = get_RGB_palette_ptr();
    end_pallete = screen_palette_ptr + 768;
    while (1)
    {
        R_scr = (unsigned __int8)*screen_palette_ptr;
        R_in = (unsigned __int8)*palette_ptr++;
        if (R_in <= R_scr)
            value = -((((R_scr - R_in) << 8) + 1) / time);
        else
            value = (((R_in - R_scr) << 8) + 1) / time;
        *(WORD*)buf_file = (WORD)R_scr << 8;
        buf = buf_file + 2;
        ++screen_palette_ptr;
        *(WORD*)buf = value;
        buf_file = buf + 2;
        if (screen_palette_ptr == end_pallete)
        {
            PALETTE_TIMER = time;
            return;
        }
    }
}

//0044B040
uint8_t* get_RGB_palette_ptr()
{
    int32_t i;
    int32_t color_offset; // ecx

    for (i = 0; i < 256; ++i)
    {
        color_offset = 3 * i;
        GETTED_PALETTE[color_offset + 0] = (int)PALETTEENTRY_BUFFER[i + 1].peRed >> 2;
        GETTED_PALETTE[color_offset + 1] = (int)PALETTEENTRY_BUFFER[i + 1].peGreen >> 2;
        GETTED_PALETTE[color_offset + 2] = (int)PALETTEENTRY_BUFFER[i + 1].peBlue >> 2;
    }
    return GETTED_PALETTE;
}

//0041FA3F
void wait_palette_animation(int target_time)
{
    unlock_surface_and_screen_ptr();
    while (PALETTE_TIMER > target_time) {
        ;
    }
}
