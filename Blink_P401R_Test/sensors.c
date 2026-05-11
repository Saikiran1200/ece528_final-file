#include "msp.h"
#include "sensors.h"

void Sensors_Init(void)
{
    P4->DIR &= ~(BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2);
    P4->REN |=  (BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2);
    P4->OUT |=  (BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2);
}

unsigned char Sensors_Read(void)
{
    unsigned char leftPressed = 0;
    unsigned char rightPressed = 0;

    if((P4->IN & (BIT7 | BIT6 | BIT5)) != (BIT7 | BIT6 | BIT5))
        leftPressed = 1;

    if((P4->IN & (BIT4 | BIT3 | BIT2)) != (BIT4 | BIT3 | BIT2))
        rightPressed = 1;

    if(leftPressed && rightPressed)
        return 3;
    else if(leftPressed)
        return 1;
    else if(rightPressed)
        return 2;
    else
        return 0;
}
