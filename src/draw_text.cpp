#include <cstring>

#include "draw_img.h"
#include "draw_text.h"

char Special_symbol;

//0043C87C
void draw_text(const char* buffer, uint8_t* bin_ptr, int32_t pos_y, int32_t font_offset)
{
    int size_x; // ebp
    int pos_x; // ebp
    unsigned int symbol; // eax
    int img_num; // eax
    signed int len; // [esp+10h] [ebp-24h]
    const char* buffer1; // [esp+18h] [ebp-1Ch]
    signed int i; // [esp+20h] [ebp-14h]

    size_x = 0;
    len = strlen(buffer);
    i = 0;
    buffer1 = buffer;
    while (i < len)
    {
        symbol = (unsigned __int8)*buffer1;
        if (symbol >= 0x80)
            symbol = get_special_symbol_code(symbol);
        img_num = symbol - 33;
        if (img_num >= 0)
            size_x += get_char_IMG_width(font_offset + img_num, bin_ptr) + 2;
        else
            size_x += 9;
        ++buffer1;
        ++i;
    }
    pos_x = 320 - size_x / 2;
    i = 0;
    buffer1 = buffer;
    while (i < len)
    {
        Special_symbol = 0;
        symbol = *buffer1;
        if (symbol >= 0x80)
            symbol = get_special_symbol_code(symbol);
        img_num = symbol - 33;
        if (img_num >= 0)
        {
            draw_IMG_on_screen(img_num + font_offset, 1, pos_y, pos_x, bin_ptr);
            if (Special_symbol)
                draw_IMG_on_screen(Special_symbol + font_offset + 107, 1, pos_y, pos_x, bin_ptr);
            pos_x += get_char_IMG_width(img_num + font_offset, bin_ptr) + 2;
        }
        else
        {
            pos_x += 9;
        }
        ++buffer1;
        ++i;
    }
}

//00402A12
int get_char_IMG_width(int32_t img_num, uint8_t* img_ptr)
{
    uint32_t ofst = *(uint32_t*)&img_ptr[4 * img_num + 2];
    return *(uint16_t*)&img_ptr[4 * img_num + 8 + ofst];
}

//00410493
char get_special_symbol_code(char in_char)
{
    unsigned int code; // eax
    int retVal; // edx
    int num_code_in_table; // ecx
    uint8_t table[] = {0x78, 0x61, 0x2D, 0x28, 0x27, 0x25, 0x23, 0x22, 0x21, 
    0x20, 0x1A, 0x19, 0x17, 0x16, 0x15, 0x14, 0x13, 0xE, 0xD, 0xC, 0xB, 0xA,
    9, 8, 7, 5, 4, 3, 2, 1, 0};
    bool match; // zf
    int v6; // esi
    int v8; // ecx
    int v9; // ebx
    int v10; // ebp
    int v11; // edi
    int v12; // eax
    int i = 0;

    code = in_char - 0x80;
    Special_symbol = 1;
    retVal = 45;
    if (code <= 0x78)
    {
        num_code_in_table = 32;
        do
        {
            if (!num_code_in_table)
                break;
            match = table[i] == (uint8_t)code;
            i++;
            --num_code_in_table;
        } while (!match);
        switch (num_code_in_table)
        {
        case 0:
            return retVal;
        case 1:
            v6 = 0;
            retVal = 128;
            goto LABEL_7;
        case 2:
        case 21:
            v8 = 1;
            retVal = 117;
            goto LABEL_12;
        case 3:
            v9 = 2;
            goto LABEL_36;
        case 4:
            v12 = 4;
            retVal = 97;
            goto LABEL_32;
        case 5:
            v10 = 1;
            retVal = 97;
            goto LABEL_15;
        case 6:
            v11 = 3;
            retVal = 97;
            goto LABEL_17;
        case 7:
            v6 = 0;
            retVal = 129;
            goto LABEL_7;
        case 8:
            v8 = 4;
            retVal = 101;
            goto LABEL_12;
        case 9:
            v9 = 1;
        LABEL_36:
            retVal = 101;
            goto LABEL_37;
        case 10:
            v12 = 3;
            retVal = 101;
            goto LABEL_32;
        case 11:
            v10 = 1;
            retVal = 105;
            goto LABEL_15;
        case 12:
            v11 = 4;
            retVal = 105;
            goto LABEL_17;
        case 13:
            v6 = 3;
            retVal = 105;
            goto LABEL_7;
        case 14:
            v8 = 1;
            retVal = 103;
            goto LABEL_12;
        case 15:
            v9 = 4;
            retVal = 111;
            goto LABEL_37;
        case 16:
        case 20:
        case 27:
        case 31:
            v12 = 1;
            goto LABEL_31;
        case 17:
            v10 = 3;
            retVal = 111;
            goto LABEL_15;
        case 18:
            v11 = 4;
            retVal = 117;
            goto LABEL_17;
        case 19:
            v6 = 3;
            retVal = 117;
            goto LABEL_7;
        case 22:
            v8 = 2;
            retVal = 97;
            goto LABEL_12;
        case 23:
            v9 = 2;
            retVal = 105;
            goto LABEL_37;
        case 24:
            v12 = 2;
        LABEL_31:
            retVal = 111;
        LABEL_32:
            Special_symbol = v12;
            break;
        case 25:
            v10 = 2;
            retVal = 117;
        LABEL_15:
            Special_symbol = v10;
            break;
        case 26:
            v11 = 0;
            retVal = 124;
        LABEL_17:
            Special_symbol = v11;
            break;
        case 28:
            v6 = 0;
            retVal = 126;
        LABEL_7:
            Special_symbol = v6;
            break;
        case 29:
            v8 = 0;
            retVal = 127;
        LABEL_12:
            Special_symbol = v8;
            break;
        case 30:
            v9 = 0;
            retVal = 123;
        LABEL_37:
            Special_symbol = v9;
            break;
        }
    }
    return retVal;
}
