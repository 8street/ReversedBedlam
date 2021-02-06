#include "rnd.h"

Rnd::Rnd()
{
    std::random_device rd;
    m_generator.seed(rd());
}
Rnd::Rnd(uint32_t seed)
{
    m_generator.seed(seed);
}
uint32_t Rnd::get()
{
    return m_generator();
}
uint32_t Rnd::get(uint32_t max) 
{
    return get() % (max + 1);
}
int32_t Rnd::get(int32_t min, int32_t max)
{
    return get() % ( abs(max - min) + 1) + min;
}
