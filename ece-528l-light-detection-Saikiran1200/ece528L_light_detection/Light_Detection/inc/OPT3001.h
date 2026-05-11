#ifndef INC_OPT3001_H_
#define INC_OPT3001_H_

#include <stdint.h>
#include "msp.h"
#include "EUSCI_B1_I2C.h"
#include "Clock.h"

#define OPT3001_ADDRESS 0x44

typedef union
{
    uint16_t RawData;
    struct
    {
        uint16_t Result : 12;
        uint16_t Exponent : 4;
    };
} OPT3001_Result;

void OPT3001_Init(void);

OPT3001_Result OPT3001_Read_Light(void);

#endif
