#include "../inc/OPT3001.h"

typedef enum
{
    RESULT            = 0x00,
    CONFIG            = 0x01,
    LOW_LIMIT         = 0x02,
    HIGH_LIMIT        = 0x03,
    MANUFACTURER_ID   = 0x7E,
    DEVICE_ID         = 0x7F,
} OPT3001_Commands;

typedef union
{
    struct
    {
        uint16_t FaultCount:                2;
        uint16_t MaskExponent:              1;
        uint16_t Polarity:                  1;
        uint16_t Latch:                     1;
        uint16_t FlagLow:                   1;
        uint16_t FlagHigh:                  1;
        uint16_t ConversionReady:           1;
        uint16_t OverflowFlag:              1;
        uint16_t ModeOfConversionOperation: 2;
        uint16_t ConversionTime:            1;
        uint16_t RangeNumber:               4;
    };
    uint16_t RawData;
} OPT3001_Config;

OPT3001_Config Read_Sensor_Configuration;

static void OPT3001_Write_Data(OPT3001_Commands command)
{
    EUSCI_B1_I2C_Send_A_Byte(OPT3001_ADDRESS, command);
}

static void OPT3001_Read_Data(uint16_t* data)
{
    uint8_t buffer[2];

    EUSCI_B1_I2C_Receive_Multiple_Bytes(OPT3001_ADDRESS, buffer, 2);

    *data = ((uint16_t)buffer[0] << 8) | buffer[1];
}

static OPT3001_Result OPT3001_Read_Register(OPT3001_Commands command)
{
    OPT3001_Result result;

    OPT3001_Write_Data(command);
    OPT3001_Read_Data(&result.RawData);

    return result;
}

static void OPT3001_Write_Register(uint8_t register_address, uint16_t register_data)
{
    uint8_t buffer[3];

    buffer[0] = register_address;
    buffer[1] = (uint8_t)(register_data >> 8);
    buffer[2] = (uint8_t)(register_data & 0xFF);

    EUSCI_B1_I2C_Send_Multiple_Bytes(OPT3001_ADDRESS, buffer, 3);
}

static void OPT3001_Write_Configuration(OPT3001_Config config)
{
    OPT3001_Write_Register(CONFIG, config.RawData);
}

static OPT3001_Config OPT3001_Read_Configuration(void)
{
    OPT3001_Config config;

    OPT3001_Write_Data(CONFIG);
    OPT3001_Read_Data(&config.RawData);

    return config;
}

void OPT3001_Init(void)
{
    OPT3001_Config config;

    P4->DIR |= BIT5;
    P4->OUT |= BIT5;

    Clock_Delay1ms(100);

    config.RawData = 0x0000;
    config.RangeNumber = 0xC;
    config.ConversionTime = 1;
    config.ModeOfConversionOperation = 0x2;
    config.Latch = 1;

    OPT3001_Write_Configuration(config);

    Clock_Delay1ms(100);

    Read_Sensor_Configuration = OPT3001_Read_Configuration();
}

OPT3001_Result OPT3001_Read_Light(void)
{
    return OPT3001_Read_Register(RESULT);
}
