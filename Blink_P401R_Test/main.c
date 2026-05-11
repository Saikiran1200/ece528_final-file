#include "msp.h"
#include "motor.h"
#include "sensors.h"

void delay_ms(unsigned long count)
{
    volatile unsigned long i;
    while(count--)
    {
        for(i = 0; i < 3000; i++);
    }
}

int main(void)
{
    unsigned char obstacle;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    Motor_Init();
    Sensors_Init();

    while(1)
    {
        obstacle = Sensors_Read();

        if(obstacle == 0)
        {
            // clear path
            Motor_Forward();
        }
        else if(obstacle == 1)
        {
            // obstacle on left -> slight right move
            Motor_Stop();
            delay_ms(40);

            Motor_Right();
            delay_ms(40);
        }
        else if(obstacle == 2)
        {
            // obstacle on right -> slight left move
            Motor_Stop();
            delay_ms(40);

            Motor_Left();
            delay_ms(40);
        }
        else
        {
            // obstacle in front / both -> quick left correction
            Motor_Stop();
            delay_ms(50);

            Motor_Left();
            delay_ms(90);
        }

        delay_ms(10);
    }
}
