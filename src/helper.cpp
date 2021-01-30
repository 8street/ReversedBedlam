#include <string.h>
#include "helper.h"


//00402965
void clear_buffer(uint32_t size, uint8_t* buffer)
{
    memset(buffer, 0, size);
}

//no present
bool bittest(int32_t value, int32_t bit) 
{
    return value & (1 << bit);
}
