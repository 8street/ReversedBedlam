
#include <string.h>
#include "helper.h"


//00402965
void clear_buffer(uint32_t size, uint8_t* buffer)
{
    memset(buffer, 0, size);
}

//not present
bool bittest(int32_t value, int32_t bit) 
{
    return value & (1 << bit);
}

//not present
uint8_t BYTE2(uint32_t value) {
    uint32_t ret = (value & 0x00FF0000) >> 16;
    return static_cast<uint8_t>(ret);
}

