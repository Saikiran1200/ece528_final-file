/**
 * @file main.c
 * @brief Main source code for the Tutorial program.
 *
 * This file contains the main entry point and function definitions for the Tutorial program.
 * It interfaces with the user LEDs of the TI MSP432 LaunchPad and provides an example of a basic
 * blinking LED program.
 *
 * To verify the pinout of the user LEDs, refer to the MSP432P401R SimpleLink Microcontroller LaunchPad Development Kit User's Guide
 * Link: https://docs.rs-online.com/3934/A700000006811369.pdf
 *
 * @author Aaron Nanas
 */

#include <stdint.h>
#include "msp.h"
#include "inc/Clock.h"
#include "inc/EUSCI_A0_UART.h"

// Constant definitions for the built-in red LED
const uint8_t RED_LED_OFF           =   0x00;
const uint8_t RED_LED_ON            =   0x01;

// Constant definitions for the RGB LED colors
const uint8_t RGB_LED_OFF           =   0x00;
const uint8_t RGB_LED_RED           =   0x01;
const uint8_t RGB_LED_GREEN         =   0x02;
const uint8_t RGB_LED_YELLOW        =   0x03;
const uint8_t RGB_LED_BLUE          =   0x04;
const uint8_t RGB_LED_PINK          =   0x05;
const uint8_t RGB_LED_SKY_BLUE      =   0x06;
const uint8_t RGB_LED_WHITE         =   0x07;

/**
 * @brief The LED1_Init function initializes the built-in red LED (P1.0).
 *
 * This function initializes the built-in red LED located at pin P1.0
 * and configures it as a GPIO pin. It sets the direction of the pin as output.
 *
 * @param None
 *
 * @return None
 */
void LED1_Init()
{
    P1->SEL0 &= ~0x01;
    P1->SEL1 &= ~0x01;
    P1->DIR |= 0x01;
}

/**
 * @brief The LED1_Output function sets the output of the built-in red LED and returns the status.
 *
 * This function sets the output of the built-in red LED based on the value of the input, led_value.
 * A bitwise AND operation (& 0xFE) is performed to mask the first bit (LSB) of the output register
 * to preserve the state of other pins connected to Port 1 while keeping the LED pin unaffected.
 * Then, a bitwise OR operation is performed with led_value to set the LED pin to the desired state
 * specified by led_value.
 *
 * @param led_value An 8-bit unsigned integer that determines the output of the built-in red LED. To turn off
 *                  the LED, set led_value to 0. Otherwise, setting led_value to 1 turns on the LED.
 *
 * @return None
 */
void LED1_Output(uint8_t led_value)
{
    P1->OUT = (P1->OUT & 0xFE) | led_value;
}

uint8_t LED1_Status()
{
    uint8_t LED1_Status = P1->OUT & 0x01;
    return LED1_Status;
}

/**
 * @brief The LED2_Init function initializes the RGB LED (P2.0 - P2.2).
 *
 * This function initializes the following RGB LED, configures the pins as GPIO pins with high drive strength,
 * and sets the direction of the pins as output. The RGB LED is off by default upon initialization.
 *  - RGBLED_RED      (P2.0)
 *  - RGBLED_GREEN    (P2.1)
 *  - RGBLED_BLUE     (P2.2)
 *
 * @param None
 *
 * @return None
 */
void LED2_Init()
{
    P2->SEL0 &= ~0x07;
    P2->SEL1 &= ~0x07;
    P2->DS |= 0x07;
    P2->DIR |= 0x07;
    P2->OUT &= ~0x07;
}

/**
 * @brief The LED2_Output function sets the output of the RGB LED and returns the status.
 *
 * This function sets the output of the RGB LED based on the value of the input, led_value.
 * A bitwise AND operation (& 0xF8) is performed to mask the lower three bits of the output register
 * to preserve the state of other pins connected to Port 2 while keeping the RGB LED pin unaffected.
 * Then, a bitwise OR operation is performed with led_value to set the RGB LED pin to the desired state
 * specified by led_value.
 *
 * @param led_value An 8-bit unsigned integer that determines the output of the RGB LED. To turn off
 *                  the RGB LED, set led_value to 0. The following values determine the color of the RGB LED:
 *
 *  Color       LED(s)   led_value
 *  Off         ---         0x00
 *  Red         R--         0x01
 *  Green       -G-         0x02
 *  Yellow      RG-         0x03
 *  Blue        --B         0x04
 *  Pink        R-B         0x05
 *  Sky Blue    -GB         0x06
 *  White       RGB         0x07
 *
 * @return None
 */

void LED2_Output(uint8_t led_value)
{
    P2->OUT = (P2->OUT & 0xF8) | led_value;
}
uint8_t LED2_Status()
{
    uint8_t LED2_Status = P2->OUT & 0x07;
    return LED2_Status;
}

int main(void)
{
    // Initialize the 48 MHz Clock
    Clock_Init48MHz();

    // Initialize the built-in red LED and the RGB LEDs
    LED1_Init();
    LED2_Init();

    while(1)
    {
        LED1_Output(RED_LED_ON);
        LED2_Output(RGB_LED_GREEN);
        uint8_t LED1_Value = LED1_Status();
        uint8_t LED2_Value = LED2_Status();
        Clock_Delay1ms(1000);

        LED1_Output(RED_LED_OFF);
        LED2_Output(RGB_LED_OFF);
        LED1_Value = LED1_Status();
        LED2_Value = LED2_Status();
        Clock_Delay1ms(1000);
    }
}
