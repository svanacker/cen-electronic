#ifndef I2C_CONSTANTS_H
#define I2C_CONSTANTS_H

/**
 * Defines the constant which is sent from the client to the MASTER
 * indicating there is no more available data
 */
#define I2C_SLAVE_NO_DATA_IN_READ_BUFFER 0x00

/**
 * Data which is written to unblock read (I2C BUG ??)
 */
#define I2C_SLAVE_FAKE_WRITE     0x00

// ALL I2C DEVICE
#define I2C_GENERAL_ADDRESS     0x00

// ACCELEROMETER ADXL345        
#define ADXL345_ADDRESS         0x3A

// VL530X
#define VL530X_ADDRESS_0        0x52
#define VL530X_ADDRESS_1        0x54
#define VL530X_ADDRESS_2        0x56
#define VL530X_ADDRESS_3        0x58
#define VL530X_ADDRESS_4        0x5A
#define VL530X_ADDRESS_5        0x5C
#define VL530X_ADDRESS_6        0x5E

// GPIO14 : Conflict with PCF8574

#define GPIO14_ADDRESS_0        0x40
#define GPIO14_ADDRESS_1        0x42
#define GPIO14_ADDRESS_2        0x44
#define GPIO14_ADDRESS_3        0x46
#define GPIO14_ADDRESS_4        0x48
#define GPIO14_ADDRESS_5        0x4A
#define GPIO14_ADDRESS_6        0x4C
#define GPIO14_ADDRESS_7        0x4E

// PCF8574

#define PCF8574_ADDRESS_0        0x40
#define PCF8574_ADDRESS_1        0x42
#define PCF8574_ADDRESS_2        0x44
#define PCF8574_ADDRESS_3        0x46
#define PCF8574_ADDRESS_4        0x48
#define PCF8574_ADDRESS_5        0x4A
#define PCF8574_ADDRESS_6        0x4C
#define PCF8574_ADDRESS_7        0x4E

// FREE ADDRESS

#define FREE_ADDRESS_0            0x50
#define TCS34725_ADDRESS          0x52

#define FREE_ADDRESS_2            0x54
#define FREE_ADDRESS_3            0x56
#define FREE_ADDRESS_4            0x58
#define FREE_ADDRESS_5            0x5A
#define FREE_ADDRESS_6            0x5C
#define FREE_ADDRESS_7            0x5E

// PCF8574A

// !!! Conflict with RLY08_ADDRESS_0
#define PCF8574A_ADDRESS_0        0x70
#define PCF8574A_ADDRESS_1        0x72
#define PCF8574A_ADDRESS_2        0x74
#define PCF8574A_ADDRESS_3        0x76
#define PCF8574A_ADDRESS_4        0x78
#define PCF8574A_ADDRESS_5        0x7A
#define PCF8574A_ADDRESS_6        0x7C
#define PCF8574A_ADDRESS_7        0x7E


// RLY08

// Warning : Conflict with PCF8574AP !!
#define    RLY08_ADDRESS_0            0x70
#define    RLY08_ADDRESS_1            0x72
#define    RLY08_ADDRESS_2            0x74
#define    RLY08_ADDRESS_3            0x76
#define    RLY08_ADDRESS_4            0x78
#define    RLY08_ADDRESS_5            0x7A
#define    RLY08_ADDRESS_6            0x7C
#define    RLY08_ADDRESS_7            0x7E


// PCA9685
#define PCA9685_ADDRESS_0             0x80
#define PCA9685_ADDRESS_1             0x82
#define PCA9685_ADDRESS_2             0x84
#define PCA9685_ADDRESS_3             0x86
#define PCA9685_ADDRESS_4             0x88
#define PCA9685_ADDRESS_5             0x8A
#define PCA9685_ADDRESS_6             0x8C
#define PCA9685_ADDRESS_7             0x8E

// INA3221
#define INA3221_ADDRESS_0                   0x80    //A0->GND
#define INA3221_ADDRESS_1                   0x82    //A0->Vs
#define INA3221_ADDRESS_2                   0x84    //A0->SDA
#define INA3221_ADDRESS_3                   0x86    //A0->SCL

// LM75A TEMPERATURE SENSOR
#define LM75A_ADDRESS                 0x90

// FOCUS ROBOTIC ADDRESS : 0x92 -> 0x9E
/** Define the I2C address used by motorBoard. */
#define MOTOR_BOARD_I2C_ADDRESS         0x94
#define MECHANICAL_BOARD_1_I2C_ADDRESS  0x96


// EEPROM 24C16
#define ST24C16_ADDRESS_0             0xA0
#define ST24C16_ADDRESS_1             0XA1
#define ST24C16_ADDRESS_2             0XA2
#define ST24C16_ADDRESS_3             0xA3
#define ST24C16_ADDRESS_4             0XA4
#define ST24C16_ADDRESS_5             0XA5
#define ST24C16_ADDRESS_6             0xA6
#define ADXL345_ALT_ADDRESS           0xA6
#define ST24C16_ADDRESS_7             0XA7

// EEPROM 24C512

#define ST24C512_ADDRESS_0             0xA0
#define ST24C512_ADDRESS_1             0XA1
#define ST24C512_ADDRESS_2             0XA2
#define ST24C512_ADDRESS_3             0xA3
#define ST24C512_ADDRESS_4             0XA4
#define ST24C512_ADDRESS_5             0XA5
#define ST24C512_ADDRESS_6             0xA6
#define ST24C512_ADDRESS_7             0XA7

//CLOCK PCF8563
// Warning : Conflict with EEPROM "<ST24C16"
#define PCF8563_WRITE_ADDRESS               0xA2

// CMPS03

#define CMPS03_ADDRESS            0XC0

//  SD21

#define SD21_ADDRESS            0xC2

// SP03 - Speech Synthetizer

#define SP03_ADDRESS            0XC4

// LCD03

#define LCD03_ADDRESS            0XC6

// MD22 Address

#define MD22_ADDRESS_0             0xB0
#define MD22_ADDRESS_1             0xB2
#define MD22_ADDRESS_2             0xB4
#define MD22_ADDRESS_3             0xB6
#define MD22_ADDRESS_4             0xB8
#define MD22_ADDRESS_5             0xBA
#define MD22_ADDRESS_6             0xBC
#define MD22_ADDRESS_7             0xBE

// PCF8573 Address
#define PCF8573P_WRITE_ADDRESS     0xD0

// SRF02

#define SRF02_ADDRESS_0         0xE0
#define SRF02_ADDRESS_1         0xE2
#define SRF02_ADDRESS_2         0xE4
#define SRF02_ADDRESS_3         0xE6
#define SRF02_ADDRESS_4         0xE8
#define SRF02_ADDRESS_5         0xEA
#define SRF02_ADDRESS_6         0xEC
#define SRF02_ADDRESS_7         0xEE

#define SRF02_ADDRESS_8         0xF0
#define SRF02_ADDRESS_9         0xF2
#define SRF02_ADDRESS_10         0xF4
#define SRF02_ADDRESS_11         0xF6
#define SRF02_ADDRESS_12         0xF8
#define SRF02_ADDRESS_13         0xFA
#define SRF02_ADDRESS_14         0xFC
#define SRF02_ADDRESS_15         0xFE

#endif


