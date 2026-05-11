#include "msp.h"

void Chassis_Board_LEDs_Init(void)
{
    // Set P8.0, P8.5, P8.6, P8.7 as outputs
    P8->DIR |= (BIT0 | BIT5 | BIT6 | BIT7);

    // Initialize all selected pins to 0 (LEDs off)
    P8->OUT &= ~(BIT0 | BIT5 | BIT6 | BIT7);
}