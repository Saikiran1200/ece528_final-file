#include "msp.h"
#include "motor.h"

void Motor_Init(void)
{
    P2->DIR |= BIT1;
    P2->OUT &= ~BIT1;
}

void Motor_Forward(void)
{
    P2->OUT |= BIT1;
}

void Motor_Backward(void)
{
    P2->OUT &= ~BIT1;
}

void Motor_Left(void)
{
    P2->OUT |= BIT1;
}

void Motor_Right(void)
{
    P2->OUT &= ~BIT1;
}

void Motor_Stop(void)
{
    P2->OUT &= ~BIT1;
}
