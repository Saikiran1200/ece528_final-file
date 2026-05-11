/**
 * @file main.c
 * @brief Light Detection using OPT3001 + I2C
 */

#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "inc/Clock.h"
#include "inc/EUSCI_A0_UART.h"
#include "inc/EUSCI_B1_I2C.h"
#include "inc/OPT3001.h"
#include "inc/Timer_A1_Interrupt.h"
#include "inc/Motor.h"
/* ===================== DEFINES ===================== */
#define LIGHT_THRESHOLD  100.0f   // adjust after testing
#define MOTOR_MIN        0
#define MOTOR_MAX        70       // lab requirement: max 70%

/* ===================== GLOBAL ===================== */
static float Lux = 0.0f;

/* ===================== PROTOTYPES ===================== */
void Sample_Light_Sensor(void);
void Controller_1(void);

/* ===================== MAIN ===================== */
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    Clock_Init48MHz();

    /* UART for printf */
    EUSCI_A0_UART_Init_Printf();

    /* Motor setup */
    Motor_Init();

    /* Timer for controller (1 kHz) */
    Timer_A1_Interrupt_Init(&Controller_1, 48000);

    /* I2C init FIRST (important) */
    EUSCI_B1_I2C_Init();

    /* Debug pin P8.0 (for oscilloscope trigger) */
    P8->DIR |= BIT0;
    P8->OUT &= ~BIT0;

    /* Trigger HIGH during OPT init */
    P8->OUT |= BIT0;
    OPT3001_Init();
    P8->OUT &= ~BIT0;

    printf("=== Light Detection Started ===\r\n");

    while(1)
    {
        Sample_Light_Sensor();

        printf("Lux: %.2f\r\n", Lux);

        Clock_Delay1ms(100);   // sample every 100 ms
    }
}

/* ===================== SENSOR ===================== */
void Sample_Light_Sensor(void)
{
    OPT3001_Result result;

    result = OPT3001_Read_Light();

    Lux = 0.01f * (1 << result.Exponent) * result.Result;
}
/* ===================== CONTROLLER ===================== */
void Controller_1(void)
{
    uint16_t duty;

    /* If light is too low → stop */
    if(Lux < LIGHT_THRESHOLD)
    {
        Motor_Stop();
        return;
    }

    /* Map lux to motor speed (0 → 70%) */
    if(Lux > 1000)   // max expected lux (you will tune this)
    {
        duty = MOTOR_MAX;
    }
    else
    {
        duty = (uint16_t)((Lux / 1000.0f) * MOTOR_MAX);
    }

    Motor_Forward(duty, duty);
}
