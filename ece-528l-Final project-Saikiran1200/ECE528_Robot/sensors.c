#include "msp.h"
#include "sensors.h"

void Sensors_Init(void)
{
}

unsigned char Sensors_Read(void)
{
    static unsigned long count = 0;
    count++;

    if(count > 400000)
    {
        count = 0;
        return 1;
    }

    return 0;
}
