#pragma once
#include <stdint.h>
#include <vector>

class Mission_state
{
public:
    Mission_state(int32_t zone_level = 1, int32_t zone = 1, int32_t ended = 0)
        : m_zone_level(zone_level), m_zone(zone), m_ended(ended)
    {
    }

    int32_t m_zone_level;
    int32_t m_zone;
    int32_t m_ended;
private:

};

extern int32_t ZONE_LEVEL;
extern int32_t ZONE;

extern std::vector<Mission_state> ZONE_ARR;


void init_zone_mision_arr();
int32_t get_level_number(int32_t zone, int32_t zone_level);

