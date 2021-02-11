
#include "core.h"
#include "ddraw_func.h"
#include "game_level.h"
#include "helper.h"
#include "levels.h"
#include "tiles.h"

int const1_1 = 1;

tile TILE_BUFFER[1296];
uint8_t TOT_BUFFER[306000];
int32_t NUM_VISIBLE_TILES;

//00407E11
void init_tiles()
{
    int offset; // edi
    int y; // edx
    int n; // ebp
    int num_tiles_x; // esi
    int x; // ebx
    int v7; // eax
    int tot_buf_pos; // edx
    int z_level; // esi
    uint8_t* tot1; // ebx
    int dat_pos; // ebp
    int x_tile; // [esp+4h] [ebp-50h]
    int x_ofst; // [esp+Ch] [ebp-48h]
    int y_ofst; // [esp+10h] [ebp-44h]
    int y1; // [esp+14h] [ebp-40h]
    int y_tile; // [esp+18h] [ebp-3Ch]
    int summ_y; // [esp+1Ch] [ebp-38h]
    int num_tiles_y; // [esp+24h] [ebp-30h]
    uint8_t* tot; // [esp+30h] [ebp-24h]
    int tot_ofst; // [esp+34h] [ebp-20h]
    uint8_t* dat; // [esp+38h] [ebp-1Ch]

    clear_buffer(sizeof(TILE_BUFFER), (uint8_t*)TILE_BUFFER);

    offset = 0;
    NUM_VISIBLE_TILES = 0;
    num_tiles_y = 0;
    for (y1 = -256; num_tiles_y <= 36; y1 += 16)
    {
        y = y1;
        n = 5;
        num_tiles_x = 0;
        x = -32 * num_tiles_y + 304;
        do
        {
            if (x >= 0 && x < 608 && y >= 0 && y < 800)
            {
                if (!offset)
                    offset = n;
                TILE_BUFFER[NUM_VISIBLE_TILES].screen_pos = &GAME_SCREEN_PTR[640 * y + x];
                TILE_BUFFER[NUM_VISIBLE_TILES].x_tile = num_tiles_x - offset;
                TILE_BUFFER[NUM_VISIBLE_TILES].y_tile = num_tiles_y - offset;
                NUM_VISIBLE_TILES++;
            }
            y += 16;
            x += 32;
            ++num_tiles_x;
            ++n;
        } while (num_tiles_x < 36);
        num_tiles_y++;
    }

    clear_buffer(sizeof(TOT_BUFFER), TOT_BUFFER);
    tot = MISSION_TOT_PTR;
    dat = MISSION_DAT_PTR;
    y_ofst = 30 * MISSION_X_MAPSIZE;
    summ_y = 0;
    x_ofst = 30 * MISSION_X_MAPSIZE;
    tot_ofst = 2 * MISSION_SQUARE;
    for (y_tile = 0; y_tile < MISSION_Y_MAPSIZE; ++y_tile)
    {
        for (x_tile = summ_y; x_tile < summ_y + x_ofst; x_tile += 30)
        {
            v7 = x_tile;
            tot_buf_pos = x_tile;
            z_level = 0;
            tot1 = tot;
            do
            {
                dat_pos = z_level * MISSION_SQUARE;
                if (*(WORD*)tot1)
                {
                    *(WORD*)&TOT_BUFFER[tot_buf_pos] = *(WORD*)tot1;
                    //if (!dat[dat_pos])
                    //    dat_z_level_empty[v7] = 1;
                }
                tot_buf_pos += 2;
                ++v7;
                ++z_level;
                tot1 += tot_ofst;
            } while (z_level < 8);
            tot += 2;
            ++dat;
        }
        summ_y += y_ofst;
    }
    clear_buffer(409600u, GAME_SCREEN_PTR);
}


//00408030
int32_t get_zone_water_img()
{
    int result; // eax

    switch (ZONE)
    {
    case 1:
    case 2:
    case 4:
    case 7:
        result = RND1.get(9) + 55;
        break;
    case 3:
        result = RND1.get(9) + 574;
        break;
    case 5:
        result = RND1.get(9) + 101;
        break;
    case 6:
        result = 748;
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

//00401471
void draw_tile(int32_t img_num, int32_t ofst, uint8_t* palette, uint8_t* screen_pos, uint8_t* bin_ptr)
{
    uint8_t* img_adr; // esi
    uint8_t* img_ptr; // esi
    uint8_t* v7; // esi
    int v8; // edx
    int v9; // edx
    uint8_t* v11; // esi
    uint8_t* v12; // edi
    uint8_t* v13; // esi
    int v14; // ebx
    int j; // edx
    int v16; // ecx
    unsigned int v17; // ecx
    char v18; // cf
    unsigned int v19; // ecx
    unsigned int v20; // ecx
    uint8_t* line_ofst_ptr; // esi
    int line_ofst; // edx
    int img_ofst; // edx
    uint8_t* v24; // esi
    uint8_t* screen_pos_1; // edi
    uint8_t* v26; // esi
    int v27; // ebx
    int i; // edx
    unsigned int v29; // ecx
    unsigned int v30; // ecx
    unsigned int v31; // ecx
    int v32; // eax
    uint8_t* v36; // esi
    int v37; // ecx
    int v38; // edx
    int v39; // ecx
    int v40; // ecx
    int v44; // [esp-Ch] [ebp-Ch]
    int v45; // [esp-8h] [ebp-8h]
    int v46; // [esp-8h] [ebp-8h]
    uint8_t* v47; // [esp-4h] [ebp-4h]
    uint8_t* v48; // [esp-4h] [ebp-4h]
    uint8_t* palette_ptr = palette;

    uint16_t unkn1;
    uint32_t unkn2;
    uint16_t unkn3;
    uint32_t unkn4;
    uint32_t unkn6;

    img_adr = &bin_ptr[4 * img_num + 2];
    img_ptr = &img_adr[*(DWORD*)img_adr];
    if (*(unsigned __int16*)img_ptr >= 4u)
    {
        line_ofst_ptr = img_ptr + 2;
        line_ofst = 640 * *(unsigned __int16*)line_ofst_ptr;
        line_ofst_ptr += 2;
        img_ofst = *(unsigned __int16*)line_ofst_ptr + line_ofst;
        line_ofst_ptr += 2;
        line_ofst = *(uint16_t*)line_ofst_ptr;
        v24 = line_ofst_ptr + 2;
        if (line_ofst)
        {
            screen_pos_1 = &screen_pos[img_ofst];
            unkn1 = *(unsigned __int16*)v24;
            v26 = v24 + 2;
            v27 = unkn1;
            if (unkn1)
            {
                if (palette_ptr && const1_1)
                {
                LABEL_37:
                    while (2)
                    {
                        v47 = screen_pos_1;
                        while (1)
                        {
                            while (1)
                            {
                                ofst &= 0xFFFFFF00;
                                ofst |= *v26++;
                                v44 = ofst;
                                if (bittest(v44, 7u))
                                    break;
                                ofst = (ofst & 0x3F) + 1;
                                v45 = v27;
                                do
                                {
                                    *screen_pos_1 = palette_ptr[*v26];
                                    ++v26;
                                    ++screen_pos_1;
                                    --ofst;
                                } while (ofst);
                                v27 = v45;
                                if (bittest(v44, 6u))
                                {
                                    screen_pos_1 = v47 + 640;
                                    v27 = v45 - 1;
                                    if (v45 != 1)
                                        goto LABEL_37;
                                    return;
                                }
                            }
                            if (bittest(ofst, 6u))
                                break;
                            screen_pos_1 += (ofst & 0x3F) + 1;
                        }
                        screen_pos_1 = v47 + 640;
                        if (--v27)
                            continue;
                        break;
                    }
                }
                else
                {
                LABEL_24:
                    while (2)
                    {
                        for (i = 640; ; i -= v32)
                        {
                            while (1)
                            {
                                ofst &= 0xFFFFFF00;
                                ofst |= *v26++;
                                unkn2 = ofst;
                                if (bittest(unkn2, 7u))
                                    break;
                                v29 = (ofst & 0x3F) + 1;
                                i -= v29;
                                v18 = v29 & 1;
                                v30 = v29 >> 1;
                                if (v18)
                                    *screen_pos_1++ = *v26++;
                                v18 = v30 & 1;
                                v31 = v30 >> 1;
                                if (v18)
                                {
                                    *(WORD*)screen_pos_1 = *(WORD*)v26;
                                    v26 += 2;
                                    screen_pos_1 += 2;
                                }
                                memcpy(screen_pos_1, v26, 4 * v31);
                                v26 += 4 * v31;
                                screen_pos_1 += 4 * v31;
                                ofst = 0;
                                if (bittest(unkn2, 6u))
                                {
                                    screen_pos_1 += i;
                                    if (--v27)
                                        goto LABEL_24;
                                    return;
                                }
                            }
                            if (bittest(ofst, 6u))
                                break;
                            v32 = (ofst & 0x3F) + 1;
                            screen_pos_1 += v32;
                        }
                        screen_pos_1 += i;
                        if (--v27)
                            continue;
                        break;
                    }
                }
            }
        }
    }
    else if (*(WORD*)img_ptr)
    {
        v7 = img_ptr + 2;
        v8 = 640 * *(unsigned __int16*)v7;
        v7 += 2;
        v9 = *(unsigned __int16*)v7 + v8;
        v7 += 2;
        unkn3 = *(unsigned __int16*)v7;
        v11 = v7 + 2;
        if (unkn3)
        {
            v12 = &screen_pos[v9];
            unkn3 = *(unsigned __int16*)v11;
            v13 = v11 + 2;
            v14 = unkn3;
            if (unkn3)
            {
                if (palette_ptr && const1_1)
                {
                LABEL_55:
                    while (2)
                    {
                        v48 = v12;
                        while (1)
                        {
                            while (1)
                            {
                                v39 = *(unsigned __int16*)v13;
                                v13 += 2;
                                unkn4 = v39;
                                if (bittest(unkn4, 0xFu))
                                    break;
                                v40 = v39 & 0xFFF;
                                v46 = v14;
                                do
                                {
                                    *v12 = palette_ptr[*v13];
                                    ++v13;
                                    ++v12;
                                    --v40;
                                } while (v40);
                                v14 = v46;
                                if (bittest(unkn4, 0xEu))
                                {
                                    v12 = v48 + 640;
                                    v14 = v46 - 1;
                                    if (v46 != 1)
                                        goto LABEL_55;
                                    return;
                                }
                            }
                            if (bittest(v39, 0xEu))
                                break;
                            v12 += v39 & 0xFFF;
                        }
                        v12 = v48 + 640;
                        if (--v14)
                            continue;
                        break;
                    }
                }
                else
                {
                LABEL_7:
                    while (2)
                    {
                        for (j = 640; ; j -= v16 & 0xFFF)
                        {
                            while (1)
                            {
                                v16 = *(unsigned __int16*)v13;
                                v13 += 2;
                                unkn6 = v16;
                                if (bittest(unkn6, 0xFu))
                                    break;
                                v17 = v16 & 0xFFF;
                                j -= v17;
                                v18 = v17 & 1;
                                v19 = v17 >> 1;
                                if (v18)
                                    *v12++ = *v13++;
                                v18 = v19 & 1;
                                v20 = v19 >> 1;
                                if (v18)
                                {
                                    *(WORD*)v12 = *(WORD*)v13;
                                    v13 += 2;
                                    v12 += 2;
                                }
                                memcpy(v12, v13, 4 * v20);
                                v13 += 4 * v20;
                                v12 += 4 * v20;
                                if (bittest(unkn6, 0xEu))
                                {
                                    v12 += j;
                                    if (--v14)
                                        goto LABEL_7;
                                    return;
                                }
                            }
                            if (bittest(v16, 0xEu))
                                break;
                            v12 += v16 & 0xFFF;
                        }
                        v12 += j;
                        if (--v14)
                            continue;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        v36 = img_ptr + 6;
        v37 = 64;
        do
        {
            v38 = 64;
            do
            {
                if (*v36)
                    *screen_pos = *v36;
                ++v36;
                ++screen_pos;
                --v38;
            } while (v38);
            screen_pos += 576;
            --v37;
        } while (v37);
    }
}
