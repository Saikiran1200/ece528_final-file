#include "msp.h"
#include "motor.h"

#define LEFT_DIR    BIT4   // P5.4
#define RIGHT_DIR   BIT5   // P5.5
#define LEFT_EN     BIT7   // P3.7
#define RIGHT_EN    BIT6   // P3.6

#define PERIOD 15000
#define DUTY   3500

void Motor_Init(void)
{
    P5->DIR |= LEFT_DIR | RIGHT_DIR;
    P5->OUT &= ~(LEFT_DIR | RIGHT_DIR);

    P3->DIR |= LEFT_EN | RIGHT_EN;
    P3->OUT |= LEFT_EN | RIGHT_EN;

    P2->DIR |= BIT6 | BIT7;
    P2->SEL0 |= BIT6 | BIT7;
    P2->SEL1 &= ~(BIT6 | BIT7);

    TIMER_A0->CCR[0] = PERIOD - 1;
    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7; // P2.6
    TIMER_A0->CCR[3] = 0;
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7; // P2.7
    TIMER_A0->CCR[4] = 0;
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR;
}

void Motor_Stop(void)
{
    TIMER_A0->CCR[3] = 0;
    TIMER_A0->CCR[4] = 0;
}

void Motor_Forward(void)
{
    P5->OUT &= ~(LEFT_DIR | RIGHT_DIR);
    TIMER_A0->CCR[3] = DUTY;
    TIMER_A0->CCR[4] = DUTY;
}

void Motor_Backward(void)
{
    P5->OUT |= LEFT_DIR | RIGHT_DIR;
    TIMER_A0->CCR[3] = DUTY;
    TIMER_A0->CCR[4] = DUTY;
}

void Motor_Left(void)
{
    P5->OUT |= LEFT_DIR;
    P5->OUT &= ~RIGHT_DIR;
    TIMER_A0->CCR[3] = DUTY;
    TIMER_A0->CCR[4] = DUTY;
}

void Motor_Right(void)
{
    P5->OUT &= ~LEFT_DIR;
    P5->OUT |= RIGHT_DIR;
    TIMER_A0->CCR[3] = DUTY;
    TIMER_A0->CCR[4] = DUTY;
}
