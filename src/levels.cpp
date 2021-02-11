#include <string>
#include "levels.h"



int32_t ZONE_LEVEL;
int32_t ZONE;

std::vector<Mission_state> ZONE_ARR;

File GAMEPAL_PAL;
BIN_File MISSION_BIN;
File MISSION_TOT;
File MISSION_DAT;

uint8_t* MISSION_TOT_PTR;
uint8_t* MISSION_DAT_PTR;

int32_t MISSION_Y_MAPSIZE;
int32_t MISSION_X_MAPSIZE;
int32_t MISSION_SQUARE;

//0041DC5A
void load_mission_files()
{

    GAMEPAL_PAL.load("GAMEGFX/GAMEPAL.PAL");
    MISSION_BIN.load("EDITOR/ZONE" + get_zone_letter(ZONE) + "/MISSION" + get_zone_letter(ZONE) + ".BIN");
    MISSION_TOT.load("EDITOR/ZONE" + get_zone_letter(ZONE) + "/MISSION" + std::to_string(ZONE_LEVEL) + ".TOT");
    MISSION_DAT.load("EDITOR/ZONE" + get_zone_letter(ZONE) + "/MISSION" + std::to_string(ZONE_LEVEL) + ".DAT");

    MISSION_DAT_PTR = MISSION_DAT.get_ptr();
    MISSION_TOT_PTR = MISSION_TOT.get_ptr();
    MISSION_X_MAPSIZE = *(int16_t*)MISSION_TOT_PTR;
    MISSION_TOT_PTR += 2;
    MISSION_Y_MAPSIZE = *(int16_t*)MISSION_TOT_PTR;

    MISSION_SQUARE = MISSION_X_MAPSIZE * MISSION_Y_MAPSIZE;

    // set correct offset
    MISSION_TOT_PTR += 2;
    MISSION_DAT_PTR += 4;

    // TODO:
    // missions arrays
    // load pad
    // load cgr, min, lnk
}

//0044745E
void init_zone_mision_arr()
{
    ZONE_ARR.clear();
    ZONE_ARR.emplace_back(Mission_state(1, 1));

    for (int32_t zone = 2; zone < 7; zone++) {
        for (int32_t level = 1; level < 6; level++) {
            ZONE_ARR.emplace_back(Mission_state(level, zone));
        }
    }
}

//0044751C
int32_t get_level_number(int32_t zone, int32_t zone_level)
{
    int32_t i; // eax

    for (i = 0; i < static_cast<int32_t>(ZONE_ARR.size()); i++)
    {
        if (zone_level == ZONE_ARR[i].m_zone_level && zone == ZONE_ARR[i].m_zone) {
            return i;
        }
    }
    return -1;
}

//not present
std::string get_zone_letter(int32_t zone)
{
    zone += 0x40;
    if (zone > 255 || zone < 0) {
        return "B";
    }
    return std::string(1, static_cast<char>(zone));
}
