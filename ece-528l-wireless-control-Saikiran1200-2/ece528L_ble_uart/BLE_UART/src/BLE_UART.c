/**
 * @file BLE_UART.c
 *
 * @brief Source code for the BLE_UART driver.
 *
 * This file contains the function definitions for the BLE_UART driver.
 *
 * It interfaces with the Adafruit Bluefruit LE UART Friend Bluetooth Low Energy (BLE) module, which uses the UART communication protocol.
 *  - Product Link: https://www.adafruit.com/product/2479
 *
 * The following connections must be made:
 *  - BLE UART MOD  (Pin 1)     <-->  MSP432 LaunchPad Pin P1.6
 *  - BLE UART CTS  (Pin 2)     <-->  MSP432 LaunchPad GND
 *  - BLE UART TXO  (Pin 3)     <-->  MSP432 LaunchPad Pin P9.6 (PM_UCA3RXD)
 *  - BLE UART RXI  (Pin 4)     <-->  MSP432 LaunchPad Pin P9.7 (PM_UCA3TXD)
 *  - BLE UART VIN  (Pin 5)     <-->  MSP432 LaunchPad VCC (3.3V)
 *  - BLE UART RTS  (Pin 6)     <-->  Not Connected
 *  - BLE UART GND  (Pin 7)     <-->  MSP432 LaunchPad GND
 *  - BLE UART DFU  (Pin 8)     <-->  Not Connected
 *
 * @note For more information regarding the Enhanced Universal Serial Communication Interface (eUSCI),
 * refer to the MSP432Pxx Microcontrollers Technical Reference Manual
 *
 * @author
 *
 */

#include "inc/BLE_UART.h"

void BLE_UART_Init(void)
{
    // Configure P9.6 and P9.7 for primary module function
    P9->SEL0 |= 0xC0;
    P9->SEL1 &= ~0xC0;

    // Configure P1.6 as GPIO output for MOD pin
    P1->SEL0 &= ~0x40;
    P1->SEL1 &= ~0x40;
    P1->DIR  |= 0x40;

    // Default to DATA mode
    P1->OUT &= ~0x40;

    // Hold EUSCI_A3 in reset
    EUSCI_A3->CTLW0 |= 0x01;

    // Clear modulation control register
    EUSCI_A3->MCTLW &= ~0xFF;

    // Disable parity
    EUSCI_A3->CTLW0 &= ~0x8000;

    // Odd parity bit setting not used because parity disabled
    EUSCI_A3->CTLW0 &= ~0x4000;

    // LSB first
    EUSCI_A3->CTLW0 &= ~0x2000;

    // 8-bit data
    EUSCI_A3->CTLW0 &= ~0x1000;

    // One stop bit
    EUSCI_A3->CTLW0 &= ~0x0800;

    // UART mode
    EUSCI_A3->CTLW0 &= ~0x0600;

    // Asynchronous mode
    EUSCI_A3->CTLW0 &= ~0x0100;

    // SMCLK clock source
    EUSCI_A3->CTLW0 |= 0x00C0;

    // Baud rate = 12,000,000 / 9600 = 1250
    EUSCI_A3->BRW = 1250;

    // Do not enable EUSCI_A3 interrupts since this code uses polling
    EUSCI_A3->IE = 0x00;

    // Release from reset
    EUSCI_A3->CTLW0 &= ~0x01;
}

uint8_t BLE_UART_InChar(void)
{
    // Wait until receive interrupt flag is set
    while ((EUSCI_A3->IFG & 0x01) == 0)
    {
    }

    // Return received byte
    return EUSCI_A3->RXBUF;
}

void BLE_UART_OutChar(uint8_t data)
{
    // Wait until transmit buffer is empty
    while ((EUSCI_A3->IFG & 0x02) == 0)
    {
    }

    // Write data to TX buffer
    EUSCI_A3->TXBUF = data;
}

int BLE_UART_InString(char *buffer_pointer, uint16_t buffer_size)
{
    int length = 0;
    int string_size = 0;
    char character;

    if ((buffer_pointer == 0) || (buffer_size == 0))
    {
        return 0;
    }

    // Leave room for null terminator
    length = buffer_size - 1;

    // Read first character
    character = BLE_UART_InChar();

    // Keep receiving until carriage return OR line feed
    while ((character != CR) && (character != LF))
    {
        if (character == BS)
        {
            if (string_size > 0)
            {
                buffer_pointer--;
                length++;
                string_size--;
            }
        }
        else
        {
            if (length)
            {
                *buffer_pointer = character;
                buffer_pointer++;
                length--;
                string_size++;
            }
        }

        character = BLE_UART_InChar();
    }

    *buffer_pointer = 0;
    return string_size;
}

void BLE_UART_OutString(char *pt)
{
    while (*pt)
    {
        BLE_UART_OutChar(*pt);
        pt++;
    }
}

uint8_t Check_BLE_UART_Data(char BLE_UART_Data_Buffer[], char *data_string)
{
    if (strstr(BLE_UART_Data_Buffer, data_string) != NULL)
    {
        return 0x01;
    }
    else
    {
        return 0x00;
    }
}

void BLE_UART_Reset(void)
{
    // Set MOD high for CMD mode
    P1->OUT |= 0x40;
    Clock_Delay1ms(1000);

    // Send reset command
    BLE_UART_OutString("ATZ\r\n");
    Clock_Delay1ms(3000);

    // Clear MOD for DATA mode
    P1->OUT &= ~0x40;
}
