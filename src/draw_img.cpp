
#include "ddraw_func.h"
#include "draw_img.h"
#include "helper.h"
#include "palette.h"

//00401CA2
void draw_IMG_on_screen(int32_t image_number, int16_t transparent, int32_t y_pos, int32_t x_pos, uint8_t* bin_ptr)
{
    uint8_t* img_ptr; // esi
    int img_header1; // eax
    uint8_t* file_pos_ptr; // esi
    int x_offset; // eax
    uint8_t* y_offset; // esi
    uint8_t* file_pos_ptr1; // esi
    int img_y_size2; // eax
    uint8_t* img_ptr1; // esi
    uint8_t* current_pos_ptr; // edi
    unsigned int img_x_size1; // ecx
    int img_y_size1; // ebx
    int img_header2; // eax
    char scr_byte; // al
    int v18; // ecx
    int v19; // eax
    int count; // ecx
    unsigned int size; // ecx
    int v22; // ecx
    int v23; // eax
    int v24; // ecx
    int v25; // ecx
    int v26; // ecx
    uint8_t* v27; // [esp-8h] [ebp-8h]
    char v28; // [esp-8h] [ebp-8h]
    int v29; // [esp-8h] [ebp-8h]
    unsigned int img_x_size2; // [esp-4h] [ebp-4h]
    uint8_t* start_x_pos_line; // [esp-4h] [ebp-4h]
    uint8_t* v32; // [esp-4h] [ebp-4h]
    int img_header;
    short transparent1; 
    int img_x_pos;
    int img_y_pos;
    int img_x_size;
    int img_height;

    transparent1 = transparent;
    img_ptr = &bin_ptr[4 * image_number + 2 + *(DWORD*)&bin_ptr[4 * image_number + 2]];
    img_header1 = *(unsigned __int16*)img_ptr;
    file_pos_ptr = img_ptr + 2;
    img_header = img_header1;
    if (img_header1 & (1 << 1u))
    {
        x_offset = *(unsigned __int16*)file_pos_ptr;
        y_offset = file_pos_ptr + 2;
        y_pos += x_offset;
        x_pos += *(unsigned __int16*)y_offset;
        file_pos_ptr = y_offset + 2;
    }
    img_y_pos = y_pos;
    img_x_pos = x_pos;
    if (*(WORD*)file_pos_ptr)
    {
        img_x_size = *(unsigned __int16*)file_pos_ptr;
        file_pos_ptr1 = file_pos_ptr + 2;
        img_y_size2 = *(unsigned __int16*)file_pos_ptr1;
        if (*(WORD*)file_pos_ptr1)
        {
            img_ptr1 = file_pos_ptr1 + 2;
            img_height = img_y_size2;
            get_screen_buffer_ptr();
            current_pos_ptr = &SCREEN_BUFFER_PTR[img_x_pos + SCREEN_SURFACE_WIDTH * img_y_pos];
            img_x_size1 = img_x_size;
            img_y_size1 = img_height;
            img_header2 = (unsigned __int16)img_header;
            if (img_header2 & (1 << 0))
            {
                if (transparent1)
                {
                    do
                    {
                        start_x_pos_line = current_pos_ptr;
                        do
                        {
                            while (1)
                            {
                                v18 = *(unsigned __int16*)img_ptr1;
                                img_ptr1 += 2;
                                if (!(v18 & (1 << 0xFu)))
                                    break;
                                current_pos_ptr += v18 & 0xFFF;
                                if (v18 & (1 << 0xEu))
                                    goto LABEL_31;
                            }
                            v19 = v18;
                            count = v18 & 0xFFF;
                            if (count > 3)
                            {
                                if (((int64_t)current_pos_ptr & 1) != 0)
                                {
                                    *current_pos_ptr++ = *img_ptr1++;
                                    --count;
                                }
                                if (((int64_t)current_pos_ptr & 2) != 0)
                                {
                                    *(WORD*)current_pos_ptr = *(WORD*)img_ptr1;
                                    img_ptr1 += 2;
                                    current_pos_ptr += 2;
                                    count -= 2;
                                }
                                v28 = count;
                                size = (unsigned int)count >> 2;
                                memcpy(current_pos_ptr, img_ptr1, 4 * size);
                                img_ptr1 += 4 * size;
                                current_pos_ptr += 4 * size;
                                if ((v28 & 2) != 0)
                                {
                                    *(WORD*)current_pos_ptr = *(WORD*)img_ptr1;
                                    img_ptr1 += 2;
                                    current_pos_ptr += 2;
                                }
                                if ((v28 & 1) != 0)
                                    *current_pos_ptr++ = *img_ptr1++;
                            }
                            else
                            {
                                memcpy(current_pos_ptr, img_ptr1, count);
                                img_ptr1 += count;
                                current_pos_ptr += count;
                            }
                        } while (!(v19 & (1 << 0xEu)));
                    LABEL_31:
                        current_pos_ptr = &start_x_pos_line[SCREEN_SURFACE_WIDTH];
                        --img_y_size1;
                    } while (img_y_size1);
                }
                else
                {
                    do
                    {
                        v32 = current_pos_ptr;
                        do
                        {
                            while (1)
                            {
                                v22 = *(unsigned __int16*)img_ptr1;
                                img_ptr1 += 2;
                                if (v22 & (1 << 0xFu))
                                    break;
                                v23 = v22;
                                v24 = v22 & 0xFFF;
                                memcpy(current_pos_ptr, img_ptr1, v24);
                                img_ptr1 += v24;
                                current_pos_ptr += v24;
                                if (v23 & (1 << 0xEu))
                                    goto LABEL_38;
                            }
                            v29 = v22;
                            v25 = v22 & 0xFFF;
                            memset(current_pos_ptr, 0, v25);
                            current_pos_ptr += v25;
                            v26 = v29;
                        } while (!(v26 & (1 << 0xEu)));
                    LABEL_38:
                        current_pos_ptr = &v32[SCREEN_SURFACE_WIDTH];
                        --img_y_size1;
                    } while (img_y_size1);
                }
            }
            else if (transparent1)
            {
                do
                {
                    img_x_size2 = img_x_size1;
                    v27 = current_pos_ptr;
                    do
                    {
                        scr_byte = *img_ptr1++;
                        if (scr_byte)
                            *current_pos_ptr = scr_byte;
                        ++current_pos_ptr;
                        --img_x_size1;
                    } while (img_x_size1);
                    current_pos_ptr = &v27[SCREEN_SURFACE_WIDTH];
                    img_x_size1 = img_x_size2;
                    --img_y_size1;
                } while (img_y_size1);
            }
            else
            {
                do
                {
                    memcpy(current_pos_ptr, img_ptr1, img_x_size1);
                    img_ptr1 += img_x_size1;
                    current_pos_ptr = &current_pos_ptr[SCREEN_SURFACE_WIDTH];
                    --img_y_size1;
                } while (img_y_size1);
            }
        }
    }
}

//00445AAB
void draw_main_menu_background_IMG(uint8_t* bin, uint8_t* palitra, uint8_t* buffer)
{
    uint8_t black_pal[770];
    wait_palette_animation(0);
    clear_buffer(770u, black_pal);
    clear_buffer(307200u, buffer);
    swap_palette_with_animation(black_pal, 10);
    wait_palette_animation(0);
    draw_IMG_in_buffer(0, 1, 0, 0, buffer, bin);
    copy_buffer_to_screen_and_unlock(buffer);
    redraw();
    swap_palette_with_animation(palitra, 10);
    memcpy(black_pal, palitra, 770u);
    copy_buffer_to_screen_and_unlock(buffer);
    unlock_surface_and_screen_ptr();
    wait_palette_animation(0);
}

void draw_IMG_in_buffer(int32_t image_number, int16_t transparent, int32_t x_pos, int32_t y_pos, uint8_t* buffer, uint8_t* bin_ptr)
{
 
    int img_header;
    int img_x_pos;
    int img_y_pos;
    int img_x_size;
    int img_height;
    int img_height1;
    int img_x_size1;
    int transparent1;
    uint8_t* v6; // esi
    int v7; // eax
    uint8_t* v8; // esi
    int v9; // eax
    uint8_t* v10; // esi
    uint8_t* v12; // esi
    uint8_t* v13; // esi
    uint8_t* v14; // edi
    int v16; // ebx
    bool v17; // zf
    int v18; // ecx
    int i; // ecx
    int v20; // ecx
    int v21; // ecx
    int v22; // ecx
    int v23; // ecx
    uint8_t* v25; // [esp-8h] [ebp-8h]
    uint8_t* v26; // [esp-8h] [ebp-8h]
    char v27; // [esp-8h] [ebp-8h]
    int v28; // [esp-8h] [ebp-8h]
    unsigned int v29; // [esp-4h] [ebp-4h]
    unsigned int v30; // [esp-4h] [ebp-4h]
    uint8_t* v31; // [esp-4h] [ebp-4h]
    uint8_t* v32; // [esp-4h] [ebp-4h]

    transparent1 = transparent;
    v6 = &bin_ptr[4 * image_number + 2 + *(DWORD*)&bin_ptr[4 * image_number + 2]];
    v7 = *(unsigned __int16*)v6;
    v8 = v6 + 2;
    img_header = v7;
    if (bittest(v7, 1u))
    {
        v9 = *(unsigned __int16*)v8;
        v10 = v8 + 2;
        x_pos += v9;
        y_pos += *(unsigned __int16*)v10;
        v8 = v10 + 2;
    }
    img_y_pos = x_pos;
    img_x_pos = y_pos;
    img_height1 = *(WORD*)v8;
    if (*(WORD*)v8)
    {
        img_x_size = *(unsigned __int16*)v8;
        v12 = v8 + 2;
        img_height1 = *(unsigned __int16*)v12;
        if (*(WORD*)v12)
        {
            v13 = v12 + 2;
            img_height = img_height1;
            v14 = &buffer[640 * img_y_pos + img_x_pos];
            img_x_size1 = img_x_size;
            v16 = img_height1;
            img_height1 = (unsigned __int16)img_header;
            if (bittest(img_height1, 0))
            {
                if (transparent1)
                {
                    do
                    {
                        v31 = v14;
                        do
                        {
                            while (1)
                            {
                                v18 = *(unsigned __int16*)v13;
                                v13 += 2;
                                if (!bittest(v18, 0xFu))
                                    break;
                                img_height1 = v18 & 0xFFF;
                                v14 += img_height1;
                                if (bittest(v18, 0xEu))
                                    goto LABEL_28;
                            }
                            img_height1 = v18;
                            v27 = v18;
                            for (i = (unsigned __int16)(v18 & 0xFFF) >> 1; i; --i)
                            {
                                *(WORD*)v14 = *(WORD*)v13;
                                v13 += 2;
                                v14 += 2;
                            }
                            if ((v27 & 1) != 0)
                                *v14++ = *v13++;
                        } while (!bittest(img_height1, 0xEu));
                    LABEL_28:
                        v14 = v31 + 640;
                        --v16;
                    } while (v16);
                }
                else
                {
                    do
                    {
                        v32 = v14;
                        do
                        {
                            while (1)
                            {
                                v20 = *(unsigned __int16*)v13;
                                v13 += 2;
                                if (bittest(v20, 0xFu))
                                    break;
                                img_height1 = v20;
                                v21 = v20 & 0xFFF;
                                memcpy(v14, v13, v21);
                                v13 += v21;
                                v14 += v21;
                                if (bittest(img_height1, 0xEu))
                                    goto LABEL_37;
                            }
                            v28 = v20;
                            v22 = v20 & 0xFFF;
                            img_height1 = 0;
                            do
                            {
                                *v14++ = 0;
                                --v22;
                            } while (v22);
                            v23 = v28;
                        } while (!bittest(v23, 0xEu));
                    LABEL_37:
                        v14 = v32 + 640;
                        --v16;
                    } while (v16);
                }
            }
            else
            {
                v17 = transparent1 == 0;
                if (transparent1)
                {
                    do
                    {
                        v29 = img_x_size1;
                        v25 = v14;
                        do
                        {
                            img_height1 = *v13++;
                            if ((BYTE)img_height1)
                                *v14 = img_height1;
                            ++v14;
                            --img_x_size1;
                        } while (img_x_size1);
                        v14 = v25 + 640;
                        img_x_size1 = v29;
                        --v16;
                    } while (v16);
                }
                else
                {
                    do
                    {
                        v30 = img_x_size1;
                        v26 = v14;
                        do
                        {
                            memcpy(v14, v13, img_x_size1);
                            v13 += img_x_size1;
                            v14 += img_x_size1;
                            img_x_size1 = 0;
                        } while (!v17);
                        v14 = v26 + 640;
                        img_x_size1 = v30;
                        v17 = --v16 == 0;
                    } while (v16);
                }
            }
        }
    }
}
