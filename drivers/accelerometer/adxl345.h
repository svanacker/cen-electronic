#ifndef ADXL435_H
#define ADXL435_H

#include "../../common/i2c/i2cBusConnectionList.h"
#include "../../common/io/outputStream.h"

// Data Rate
#define ADXL345_RATE_3200HZ   0x0F    // 3200 Hz
#define ADXL345_RATE_1600HZ   0x0E    // 1600 Hz
#define ADXL345_RATE_800HZ    0x0D    // 800 Hz
#define ADXL345_RATE_400HZ    0x0C    // 400 Hz
#define ADXL345_RATE_200HZ    0x0B    // 200 Hz
#define ADXL345_RATE_100HZ    0x0A    // 100 Hz
#define ADXL345_RATE_50HZ     0x09    // 50 Hz
#define ADXL345_RATE_25HZ     0x08    // 25 Hz
#define ADXL345_RATE_12_5HZ   0x07    // 12.5 Hz
#define ADXL345_RATE_6_25HZ   0x06    // 6.25 Hz
#define ADXL345_RATE_3_13HZ   0x05    // 3.13 Hz
#define ADXL345_RATE_1_56HZ   0x04    // 1.56 Hz
#define ADXL345_RATE_0_78HZ   0x03    // 0.78 Hz
#define ADXL345_RATE_0_39HZ   0x02    // 0.39 Hz
#define ADXL345_RATE_0_20HZ   0x01    // 0.20 Hz
#define ADXL345_RATE_0_10HZ   0x00    // 0.10 Hz

// Range
#define ADXL345_RANGE_2G      0x00    // +-2 g
#define ADXL345_RANGE_4G      0x01    // +-4 g
#define ADXL345_RANGE_8G      0x02    // +-8 g
#define ADXL345_RANGE_16G     0x03    // +-16 g

// A setting of 1 in the TAP_X enable, TAP_Y enable, or TAP_Z
// enable bit enables x-, y-, or z-axis participation in tap detection.
// A setting of 0 excludes the selected axis from participation in
// tap detection. 
#define TAP_AXES_ALL_ENABLE                     0b00000111
#define TAP_AXES_X_ENABLE                       0b00000100
#define TAP_AXES_Y_ENABLE                       0b00000010
#define TAP_AXES_Z_ENABLE                       0b00000001

/**
 * Universal accelerometer Value
 */
typedef struct AccelerometerData {
    // To know if we are in 2G, 4G, 8G or 16G sensibility
    unsigned char rangeMask;
    unsigned char xRawLowValue;
    unsigned char yRawLowValue;
    unsigned char zRawLowValue;
    unsigned char xRawHighValue;
    unsigned char yRawHighValue;
    unsigned char zRawHighValue;   
    
    int xRawValue;
    int yRawValue;
    int zRawValue;
    // Value in milliG
    float milligXValue;
    float milligYValue;
    float milligZValue;
} AccelerometerData;

// DEBUG PART

/**
 * Debug the main register list of the ADX1345 (but not the data).
 * @param outputStream
 * @param i2cBusConnection
 */
void adxl345_debugMainRegisterList(OutputStream* outputStream, I2cBusConnection* i2cBusConnection);

/**
 * Read then debug the Data value stored in AccelerometerData
 * @param outputStream
 * @param i2cBusConnection
 * @param accelerometerData
 */
void adxl345_debugValueRegisterList(OutputStream* outputStream, I2cBusConnection* i2cBusConnection, AccelerometerData* accelerometerData);

// SETUP FUNCTIONS

/**
 * Setup the adxl345 to raise an interrupt on INT 1 for a single TAP detection
 * @param i2cBusConnection the connection to the I2C
 * @param thresholdTap      : 62,5 mg / LSB for 16G
 * @param thresholdDuration : 625 µs / LSB
 * @param tapAxesMap        : use X AND/OR, Y AND/OR Z
 * @param rate              : the rate of acceleration  2G, 4G, 8G, 16G
 * @param rangeMask         : ADXL345_RANGE_2G / ADXL345_RANGE_4G / ADXL345_RANGE_8G / ADXL345_RANGE_16G
 * @param accelerometerData : the pointer on the structure containing the data
 */
void adxl345_setupInterruptOnSingleTapOnInt1(I2cBusConnection* i2cBusConnection, 
                                       unsigned char thresholdTap,
                                       unsigned char thresholdDuration,
                                       unsigned char tapAxesMap,
                                       unsigned char rate,
                                       unsigned char rangeMask,
                                       AccelerometerData* accelerometerData);

void adxl345_setupOffset(I2cBusConnection* i2cBusConnection, unsigned char offsetX, unsigned char offsetY, unsigned char offsetZ);

void adxl345_clearOffset(I2cBusConnection* i2cBusConnection);

// PRIMITIVE FUNCTIONS

void adxl345_write8(I2cBusConnection* i2cBusConnection, unsigned char reg, unsigned char data);

unsigned char adxl345_read8(I2cBusConnection* i2cBusConnection, unsigned char reg);

// HIGH LEVEL Functions

unsigned char adx345_readSampleCount(I2cBusConnection* i2cBusConnection);

/**
 * Read the value of the accelerometer and store it in the data.
 * @param i2cBusConnection
 * @param accelerometerData
 */
void adxl345_readAccelerometerData(I2cBusConnection* i2cBusConnection, AccelerometerData* accelerometerData);

#endif
