#ifndef ADXL435_H
#define ADXL435_H

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/i2c/i2cBusConnectionList.h"
#include "../../common/io/outputStream.h"

#include "../../common/sensor/accelerometer/accelerometer.h"

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


// SETUP FUNCTIONS

/**
 * Setup the adxl345 to raise an interrupt on INT 1 for a single TAP detection
 * @param accelerometer the POO instance
 * @param thresholdTap      : 62,5 mg / LSB for 16G
 * @param thresholdDuration : 625 µs / LSB
 * @param tapAxesMap        : use X AND/OR, Y AND/OR Z
 * @param rate              : the rate of acceleration  2G, 4G, 8G, 16G
 * @param rangeMask         : ADXL345_RANGE_2G / ADXL345_RANGE_4G / ADXL345_RANGE_8G / ADXL345_RANGE_16G
 * @param accelerometerData : the pointer on the structure containing the data
 */
void adxl345_setupInterruptOnSingleTapOnInt1(Accelerometer* accelerometer, 
                                       unsigned int thresholdMilliG,
                                       unsigned int thresholdDurationMilliSec,
                                       unsigned char tapAxesMap,
                                       unsigned char rate,
                                       unsigned char rangeMask);

unsigned int adxl345_getThresholdInMilliG(Accelerometer* accelerometer);

/**
 * Set the threshold in milliG. You MUST configure the dataFormat before !
 * @param thresholdInMilliG
 * @param accelerometer
 */
void adxl345_setThresholdInMilliG(Accelerometer* accelerometer, unsigned int thresholdInMilliG);

void adxl345_setDurationInMilliSec(Accelerometer* accelerometer, unsigned int durationInMilliG);

/**
 * Return if the Interruption was raised.
 * @param accelerometer
 */
bool adxl345_wasIntRaised(Accelerometer* accelerometer);

/**
 * Setup the Offset on each direction.
 * @param i2cBusConnection
 * @param offsetX
 * @param offsetY
 * @param offsetZ
 */
void adxl345_setupOffset(I2cBusConnection* i2cBusConnection, unsigned char offsetX, unsigned char offsetY, unsigned char offsetZ);

/**
 * Clear all values of offset.
 * @param i2cBusConnection
 */
void adxl345_clearOffset(I2cBusConnection* i2cBusConnection);

// PRIMITIVE FUNCTIONS

void adxl345_write8(I2cBusConnection* i2cBusConnection, unsigned char reg, unsigned char data);

unsigned char adxl345_read8(I2cBusConnection* i2cBusConnection, unsigned char reg);

// ACCELEROMETER INTERFACE

/**
 * Read the amount of Sample Count available.
 * @param accelerometer pointer on object (POO)
 * @return 
 */
unsigned int adxl345_readSampleCount(Accelerometer* accelerometer);

/**
 * Read the value of the accelerometer and store it in the data.
 * @param accelerometer pointer on object (POO)
 */
void adxl345_readAccelerometerData(Accelerometer* accelerometer);

/**
 * Init the ADXL345 as an Accelerometer.
 * @param accelerometer the pointer on the structure with POO Callback
 * @param accelerometerData the structure to store the accelerometer Data
 * @param i2cBusConnection the i2c bus connection to reach the ADXL345
 */
void initADXL345AsAccelerometer(Accelerometer* accelerometer, 
                                AccelerometerData* accelerometerData,
                                I2cBusConnection* i2cBusConnection);

#endif
