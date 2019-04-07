#ifndef INA219_H
#define INA219_H

// Datasheet available here : http://www.ti.com/lit/ds/symlink/ina219.pdf

#include "../../../common/sensor/current/current.h"

#include "../../../common/i2c/i2cCommon.h"

#define INA219_CONFIGURATION_REGISTER                                       0x00
#define INA219_SHUNT_VOLTAGE_REGISTER                                       0x01
#define INA219_BUS_VOLTAGE_REGISTER                                         0x02
#define INA219_POWER_REGISTER                                               0x03
#define INA219_CURRENT_REGISTER                                             0x04
#define INA219_CALIBRATION_REGISTER                                         0x05

// Configuration mask
// Bit 15
#define INA219_CONFIGURATION_RESET                                        0x8000

// Bit 13 : Bus Voltage Range
#define INA219_CONFIGURATION_BUS_VOLTAGE_RANGE_16V                        0x0000
#define INA219_CONFIGURATION_BUS_VOLTAGE_RANGE_32V                        0x2000

// Bit 11/12
#define INA219_CONFIGURATION_GAIN_RANGE_40_MV                             0x0000
#define INA219_CONFIGURATION_GAIN_RANGE_80_MV                             0x0800
#define INA219_CONFIGURATION_GAIN_RANGE_160_MV                            0x1000
#define INA219_CONFIGURATION_GAIN_RANGE_320_MV                            0x1800

// Bit 7 - 10 : TODO

// Bit 3-6 :  SADC Shunt ADC Resolution/Averaging
#define INA219_ADC_MODE_9_BIT                                         0b00000000
#define INA219_ADC_MODE_10_BIT                                        0b00001000
#define INA219_ADC_MODE_11_BIT                                        0b00010000
#define INA219_ADC_MODE_12_BIT                                        0b00011000
#define INA219_ADC_MODE_SAMPLE_2                                      0b01001000
#define INA219_ADC_MODE_SAMPLE_4                                      0b01010000
#define INA219_ADC_MODE_SAMPLE_8                                      0b01011000
#define INA219_ADC_MODE_SAMPLE_16                                     0b01100000
#define INA219_ADC_MODE_SAMPLE_32                                     0b01101000
#define INA219_ADC_MODE_SAMPLE_64                                     0b01110000
#define INA219_ADC_MODE_SAMPLE_128                                    0b01111000


// Bit 0-2 : Operating Mode
#define INA219_CONFIGURATION_POWER_DOWN                               0b00000000
#define INA219_CONFIGURATION_SHUNT_VOLTAGE_TRIGGERED                  0b00000001
#define INA219_CONFIGURATION_BUS_VOLTAGE_TRIGGERED                    0b00000010
#define INA219_CONFIGURATION_SHUNT_AND_BUS_VOLTAGE_TRIGGERED          0b00000011

#define INA219_CONFIGURATION_ADC_OFF                                  0b00000100
#define INA219_CONFIGURATION_SHUNT_VOLTAGE_CONTINUOUS                 0b00000101
#define INA219_CONFIGURATION_BUS_VOLTAGE_CONTINOUS                    0b00000110
#define INA219_CONFIGURATION_SHUNT_AND_BUS_CONTINUOUS                 0b00000111


/**
 * Initializes a current structure for a INA219 sensor.
 * @param current a pointer on the current object (POO simulation)
 * @param i2cBusConnection a pointer on the i2cBusConnection
 */
void initCurrentINA219(Current* current, I2cBusConnection* i2cBusConnection);

// PRIMITIVE FUNCTIONS

void ina219_write16(I2cBusConnection* i2cBusConnection, unsigned char reg, unsigned int data);

int ina219_read16(I2cBusConnection* i2cBusConnection, unsigned char reg);

#endif
