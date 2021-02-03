#include "levels.h"

int32_t ZONE_LEVEL;
int32_t ZONE;

std::vector<Mission_state> ZONE_ARR;

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
    int32_t level; // edx
    int32_t i; // eax

    level = 0;
    for (i = 0; i < static_cast<int32_t>(ZONE_ARR.size()); i++)
    {
        if (zone_level == ZONE_ARR[i].m_zone_level && zone == ZONE_ARR[i].m_zone) {
            return level;
        }
        level++;
    }
    return -1;
}
