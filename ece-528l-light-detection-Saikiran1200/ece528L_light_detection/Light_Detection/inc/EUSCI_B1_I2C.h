#ifndef INC_EUSCI_B1_I2C_H_
#define INC_EUSCI_B1_I2C_H_

#include <stdint.h>
#include "msp.h"

void EUSCI_B1_I2C_Init(void);

void EUSCI_B1_I2C_Send_A_Byte(uint8_t slave_address, uint8_t data);

void EUSCI_B1_I2C_Send_Multiple_Bytes(uint8_t slave_address,
                                      uint8_t *data_buffer,
                                      uint32_t packet_length);

uint8_t EUSCI_B1_I2C_Receive_A_Byte(uint8_t slave_address);

void EUSCI_B1_I2C_Receive_Multiple_Bytes(uint8_t slave_address,
                                         uint8_t *data_buffer,
                                         uint16_t packet_length);

#endif
