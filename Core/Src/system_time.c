#include "system_time.h"

static volatile uint32_t systick_count = 0;

void system_time_increment()
{
    systick_count++;
}

uint32_t get_system_time()
{
    return systick_count;
}
