#include "adxl345.h"
#include "adxl345Register.h"
#include "adxl345Debug.h"

#include "../../common/error/error.h"

#include "../../common/i2c/i2cBusConnectionList.h"
#include "../../common/i2c/master/i2cMaster.h"

#include <stdbool.h>
#include <math.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"
#include "../../common/log/logger.h"

// Forward declatation
I2cBusConnection* _ADXL345_getI2cBusConnection(Accelerometer* accelerometer);

void adxl345_writeRate(I2cBusConnection* i2cBusConnection, unsigned char rate) {
    adxl345_write8(i2cBusConnection, REG_BW_RATE, rate & BW_RATE_RATE_MASK);
}

void adxl345_writeRangeMask(I2cBusConnection* i2cBusConnection, unsigned char rangeMask) {
    adxl345_write8(i2cBusConnection, REG_DATA_FORMAT, rangeMask & DATA_FORMAT_RANGE_MASK);
}

void adxl345_writeFifoCtrl(I2cBusConnection* i2cBusConnection, unsigned char fifoCtrl) {
    adxl345_write8(i2cBusConnection, REG_FIFO_CTL, fifoCtrl);
}

void adxl345_start(I2cBusConnection* i2cBusConnection) {
    adxl345_write8(i2cBusConnection, REG_POWER_CTL, POWER_CTL_MEASURE);
}

void adxl345_stop(I2cBusConnection* i2cBusConnection) {
    adxl345_write8(i2cBusConnection, REG_POWER_CTL, 0);
}

unsigned char adxl345_readDeviceID(I2cBusConnection* i2cBusConnection) {
    return adxl345_read8(i2cBusConnection, REG_DEVID);
}

unsigned int adxl345_readSampleCount(Accelerometer* accelerometer) {
    I2cBusConnection* i2cBusConnection = _ADXL345_getI2cBusConnection(accelerometer);
    return (unsigned int) adxl345_read8(i2cBusConnection, REG_FIFO_STATUS & FIFO_STATUS_ENTRIES_MASK);
}

void adxl345_setupInterruptOnSingleTapOnInt1(Accelerometer* accelerometer, 
                                       unsigned int thresholdMilliG,
                                       unsigned int thresholdDurationMilliSec,
                                       unsigned char tapAxesMap,
                                       unsigned char rate,
                                       unsigned char rangeMask) {
    I2cBusConnection* i2cBusConnection = _ADXL345_getI2cBusConnection(accelerometer);
    AccelerometerData* accelerometerData = accelerometer->accelerometerData;
    unsigned char deviceId = adxl345_readDeviceID(i2cBusConnection);
    if (deviceId != REG_DEVID_CONST_VALUE) {
        appendStringAndDec(getErrorOutputStreamLogger(), "ADXL345 INIT PB : DEV ID=", deviceId);
        appendCRLF(getErrorOutputStreamLogger());
        writeError(ACCELEROMETER_SENSOR_SETUP_PROBLEM);
        return;
    }
    accelerometerData->rangeMask = rangeMask;
    
    // Start to measure
    adxl345_start(i2cBusConnection);
    adxl345_clearOffset(i2cBusConnection);
    adxl345_setThresholdInMilliG(accelerometer, thresholdMilliG);
    adxl345_setDurationInMilliSec(accelerometer, thresholdDurationMilliSec);
    adxl345_write8(i2cBusConnection, REG_INT_MAP, 0b00000000);
    adxl345_writeRate(i2cBusConnection, rate);
    adxl345_writeRangeMask(i2cBusConnection, rangeMask);
    // Suppress double tap detection, and active tap only for specified mask
    // adxl345_write8(i2cBusConnection, REG_TAP_AXES, TAP_AXES_SUPPRESS | tapAxesMap);
    adxl345_write8(i2cBusConnection, REG_TAP_AXES, tapAxesMap);
    // Start enable of Interrupt
    adxl345_write8(i2cBusConnection, REG_INT_ENABLE, INT_ENABLE_SINGLE_TAP); 
    
    // Manage to get data in STREAM, and keep INT Trigger
    // TODO : Change this, if we want to use INT
    adxl345_writeFifoCtrl(i2cBusConnection, FIFO_CTL_FIFO_MODE_STREAM);
    
    // Start Measurement
    adxl345_start(i2cBusConnection);
}

unsigned int adxl345_getThresholdInMilliG(Accelerometer* accelerometer) {
    I2cBusConnection* i2cBusConnection = _ADXL345_getI2cBusConnection(accelerometer);
    unsigned char thresholdTapValue = adxl345_read8(i2cBusConnection, REG_THRESH_TAP);
    unsigned char dataFormat = accelerometer->accelerometerData->rangeMask;
    switch (dataFormat) {
        case ADXL345_RANGE_2G:
            return (unsigned int) (thresholdTapValue * 7.8f);
        case ADXL345_RANGE_4G:
            return (unsigned int) (thresholdTapValue * 15.6f);
        case ADXL345_RANGE_8G:
            return (unsigned int) (thresholdTapValue * 31.2f);
        case ADXL345_RANGE_16G:
            return (unsigned int) (thresholdTapValue * 62.5f);
        default:
            return 0;
    }    
}

void adxl345_setThresholdInMilliG(Accelerometer* accelerometer, unsigned int thresholdInMilliG) {
    unsigned char thresholdTapValue = 0;
    unsigned char dataFormat = accelerometer->accelerometerData->rangeMask;
    if (thresholdInMilliG != 0) {
        switch (dataFormat) {
            case ADXL345_RANGE_2G:
                thresholdTapValue = (unsigned char) (thresholdInMilliG / 7.8f);
                break;
            case ADXL345_RANGE_4G:
                thresholdTapValue = (unsigned char) (thresholdInMilliG / 15.6f);
                break;
            case ADXL345_RANGE_8G:
                thresholdTapValue = (unsigned char) (thresholdInMilliG / 31.2f);
                break;
            case ADXL345_RANGE_16G:
                thresholdTapValue = (unsigned char) (thresholdInMilliG / 62.5f);
                break;
            default:
                thresholdTapValue = 0;
        }    
    }
    I2cBusConnection* i2cBusConnection = _ADXL345_getI2cBusConnection(accelerometer);
    adxl345_write8(i2cBusConnection, REG_THRESH_TAP, thresholdTapValue);
}

void adxl345_setDurationInMilliSec(Accelerometer* accelerometer, unsigned int durationInMilliG) {
    unsigned char durationRegValue = (unsigned char) ((float) durationInMilliG / 0.625f);
    I2cBusConnection* i2cBusConnection = _ADXL345_getI2cBusConnection(accelerometer);
    adxl345_write8(i2cBusConnection, REG_DUR, durationRegValue);
}

bool adxl345_wasIntRaised(Accelerometer* accelerometer) {
    I2cBusConnection* i2cBusConnection = _ADXL345_getI2cBusConnection(accelerometer);
    unsigned char value = adxl345_read8(i2cBusConnection, REG_INT_SOURCE);
    return (value & INT_SOURCE_SINGLE_TAP) != 0;
}

float adxl345_convertRawToMilliG(int rawValue, Accelerometer* accelerometer) {
    unsigned dataFormat = accelerometer->accelerometerData->rangeMask;
    switch (dataFormat) {
        case ADXL345_RANGE_2G:
            return (float) rawValue * 3.9f;

        case ADXL345_RANGE_4G:
            return (float) rawValue * 7.8f;

        case ADXL345_RANGE_8G:
            return (float) rawValue * 15.6f;

        case ADXL345_RANGE_16G:
            return (float) rawValue * 31.2f;

        default:
            return 0.0f;
    }
}

void adxl345_setupOffset(I2cBusConnection* i2cBusConnection, unsigned char offsetX, unsigned char offsetY, unsigned char offsetZ) {
    // Not optimal, does not use multiple writes, but must work
    adxl345_write8(i2cBusConnection, REG_OFSX, offsetX);
    adxl345_write8(i2cBusConnection, REG_OFSY, offsetY);
    adxl345_write8(i2cBusConnection, REG_OFSZ, offsetZ);    
}

void adxl345_clearOffset(I2cBusConnection* i2cBusConnection) {
    adxl345_setupOffset(i2cBusConnection, 0, 0, 0);
}

void adxl345_write8(I2cBusConnection* i2cBusConnection, unsigned char reg, unsigned char data) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterWaitSendI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    // Start
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    // Address
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);

    // Register
    portableMasterWriteI2C(i2cBusConnection, reg);
    WaitI2C(i2cBus);

    // Data
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
}

void adxl345_readAccelerometerData(Accelerometer* accelerometer) {
    I2cBusConnection* i2cBusConnection = _ADXL345_getI2cBusConnection(accelerometer);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    AccelerometerData* accelerometerData = accelerometer->accelerometerData;

    portableMasterWaitSendI2C(i2cBusConnection);
    
    // Start
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    // Address
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);

    // Register
    portableMasterWriteI2C(i2cBusConnection, REG_DATAX0);
    WaitI2C(i2cBus);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    // Restart in read mode
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    // send read address (bit zero is set)
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 1);
    WaitI2C(i2cBus);
    
    // X
    accelerometerData->xRawLowValue = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    accelerometerData->xRawHighValue = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterAckI2C(i2cBusConnection);

    accelerometerData->xRawValue = (unsigned int) ((accelerometerData->xRawHighValue << 8) | accelerometerData->xRawLowValue);
    if (accelerometerData->xRawValue > 32768) {
        accelerometerData->xRawValue -= 65536;
    }
    accelerometerData->milligXValue = adxl345_convertRawToMilliG(accelerometerData->xRawValue, accelerometer);
 
    // Y
    WaitI2C(i2cBus);
    accelerometerData->yRawLowValue = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    accelerometerData->yRawHighValue = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    accelerometerData->yRawValue = (unsigned int) ((accelerometerData->yRawHighValue << 8) | accelerometerData->yRawLowValue);
    if (accelerometerData->yRawValue > 32768) {
        accelerometerData->yRawValue -= 65536;
    }
    accelerometerData->milligYValue = adxl345_convertRawToMilliG(accelerometerData->yRawValue, accelerometer);

    // Z
    accelerometerData->zRawLowValue = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterAckI2C(i2cBusConnection);

    WaitI2C(i2cBus);
    accelerometerData->zRawHighValue = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterNackI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);

    accelerometerData->zRawValue = (unsigned int) ((accelerometerData->zRawHighValue << 8) | accelerometerData->zRawLowValue);
    if (accelerometerData->zRawValue > 32768) {
        accelerometerData->zRawValue -= 65536;
    }
    accelerometerData->milligZValue = adxl345_convertRawToMilliG(accelerometerData->zRawValue, accelerometer);
}

unsigned char adxl345_read8(I2cBusConnection* i2cBusConnection, unsigned char reg) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    unsigned char result;
    portableMasterWaitSendI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    // Start
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    // Address
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);

    // Register
    portableMasterWriteI2C(i2cBusConnection, reg);
    WaitI2C(i2cBus);
    
    // Restart in read mode
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    // send read address (bit zero is set)
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 1);
    WaitI2C(i2cBus);
    
    result = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterNackI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterStopI2C(i2cBusConnection);
    return result;
}

// ACCELEROMETER INTERFACE

/**
 * Get the internal I2cBusConnection.
 * @param accelerometer the accelerometer structure (to simulate POO Programming).
 * @private
 */
I2cBusConnection* _ADXL345_getI2cBusConnection(Accelerometer* accelerometer) {
    I2cBusConnection* result = (I2cBusConnection*) accelerometer->object;
    
    return result;
}

void initADXL345AsAccelerometer(Accelerometer* accelerometer, 
                       AccelerometerData* accelerometerData,
                       I2cBusConnection* i2cBusConnection) {
    initAccelerometer(accelerometer, 
                      accelerometerData,
                      adxl345_readSampleCount,
                      adxl345_readAccelerometerData,
                      // THRESHOLD
                      adxl345_getThresholdInMilliG,
                      adxl345_setThresholdInMilliG,
                      // DEBUG
                      adxl345_debugMainRegisterList,
                      adxl345_debugValueRegisterList,
                      (int*) i2cBusConnection);
}
