#include "msp.h"

void delay(void)
{
    volatile unsigned long i;
    for(i = 0; i < 300000; i++);
}

int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    P2->DIR |= BIT1;   // LED

    P5->DIR &= ~BIT1;  // input

    while(1)
    {
        P2->OUT ^= BIT1;   // LED toggles always
        delay();
    }
}
