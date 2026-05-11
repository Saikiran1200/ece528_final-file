/**
 * @file EUSCI_B1_I2C.c
 * @brief Source code for the EUSCI_B1_I2C driver.
 *
 * This file contains the function definitions for the EUSCI_B1_I2C driver.
 * The EUSCI_B1_I2C driver uses busy-wait implementation.
 *
 * @note This function assumes that the necessary pin configurations for I2C communication have been performed
 *       on the corresponding pins. The output from the pins will be observed using an oscilloscope.
 *       - P6.4 (SDA)
 *       - P6.5 (SCL)
 *
 * For more information regarding the Enhanced Universal Serial Communication Interface (eUSCI),
 * refer to the MSP432Pxx Microcontrollers Technical Reference Manual
 *
 * @author
 *
 */

#include "../inc/EUSCI_B1_I2C.h"

void EUSCI_B1_I2C_Init()
{

}

void EUSCI_B1_I2C_Send_A_Byte(uint8_t slave_address, uint8_t data)
{

}

void EUSCI_B1_I2C_Send_Multiple_Bytes(uint8_t slave_address, uint8_t *data_buffer, uint32_t packet_length)
{

}

uint8_t EUSCI_B1_I2C_Receive_A_Byte(uint8_t slave_address)
{
    return 0;
}

void EUSCI_B1_I2C_Receive_Multiple_Bytes(uint8_t slave_address, uint8_t *data_buffer, uint16_t packet_length)
{

}
