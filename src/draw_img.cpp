
#include "ddraw_func.h"
#include "draw_img.h"

//00401CA2
void draw_IMG_on_screen(int32_t image_number, int16_t unkn, int32_t y_pos, int32_t x_pos, uint8_t* bin_ptr)
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
    short unkn1; 
    int img_x_pos;
    int img_y_pos;
    int img_x_size;
    int img_height;

    unkn1 = unkn;
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
                if (unkn1)
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
            else if (unkn1)
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
