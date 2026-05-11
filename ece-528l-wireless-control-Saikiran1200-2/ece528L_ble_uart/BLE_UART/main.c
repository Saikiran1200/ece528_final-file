/**
 * @file main.c
 *
 * @brief Main source code for the BLE_UART program.
 *
 * This file contains the main entry point for the BLE_UART program,
 * which is used to demonstrate the BLE_UART driver.
 *
 * It interfaces with the Adafruit Bluefruit LE UART Friend Bluetooth Low Energy (BLE) module, which uses the UART communication protocol.
 *  - Product Link: https://www.adafruit.com/product/2479
 *
 * @note For more information regarding the Enhanced Universal Serial Communication Interface (eUSCI),
 * refer to the MSP432Pxx Microcontrollers Technical Reference Manual
 *
 * @author
 *
 */
/**
 * @file main.c
 * @author Your Name
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "msp.h"

#include "clock.h"
#include "cortexm.h"
#include "gpio.h"
#include "EUSCI_A0_UART.h"
#include "motor.h"
#include "BLE_UART.h"

#define PWM_NOMINAL 3000

char BLE_UART_Buffer[BLE_UART_BUFFER_SIZE];

// Function to process received BLE commands
void Process_BLE_UART_Data(char BLE_UART_Buffer[])
{
    if (Check_BLE_UART_Data(BLE_UART_Buffer, "RGB LED GREEN"))
    {
        LED2_Output(0x02); // Green
    }
    else if (Check_BLE_UART_Data(BLE_UART_Buffer, "RGB LED OFF"))
    {
        LED2_Output(0x00); // Off
    }
    else
    {
        printf("BLE UART Command Not Found\n");
    }
}

int main(void)
{
    DisableInterrupts();

    // Clock setup
    Clock_Init48MHz();

    // LED init
    LED2_Init();

    // UART for printf (USB serial)
    EUSCI_A0_UART_Init_Printf();

    // BLE UART init
    BLE_UART_Init();

    // Motor init
    Motor_Init();

    // Enable interrupts
    EnableInterrupts();

    // Reset BLE module
    BLE_UART_Reset();
    Clock_Delay1ms(1000);

    // Send startup message
    BLE_UART_OutString("BLE UART Active\r\n");
    Clock_Delay1ms(1000);

    while (1)
    {
        int string_size = BLE_UART_InString(BLE_UART_Buffer, BLE_UART_BUFFER_SIZE);

        if (string_size > 0)
        {
            printf("User Data: ");

            for (int i = 0; i < string_size; i++)
            {
                printf("%c", BLE_UART_Buffer[i]);
            }
            printf("\n");

            Process_BLE_UART_Data(BLE_UART_Buffer);
        }
    }
}
