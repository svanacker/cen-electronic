/**
 * PIC 32 PORT of ARDUINO
 * Inspired from : https://github.com/adafruit/Adafruit_VL53L0X/blob/c5a73e09389740752771a67c8de9723b4c0ca477/src/platform/src/vl53l0x_i2c_comms.cpp
 * There is only to implement write multi to the I2C PIC32 library so that it works
 * because write/read on byte/word/dwork are simply mapped to write_multi / read_multi
 */
#include <stdlib.h>
#include <stdbool.h>
#include "../vl53l0x_types.h"
#include "../vl53l0x_api.h"
#include "../../../../common/i2c/master/i2cMaster.h"
#include "../../../../common/i2c/i2cBusConnectionList.h"

#include "../../../../common/log/logger.h"

#include "../../../../common/io/outputStream.h"
#include "../../../../common/io/printWriter.h"
#include "error.h"

// #define VL53L0X_DEBUG    0

// PRIMITIVES

int32_t VL53L0X_write_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata, int32_t count) {
    I2cBusConnection* i2cBusConnection = getI2cBusConnectionBySlaveAddress(deviceAddress);
    if (i2cBusConnection == NULL) {
        writeError(I2C_BUS_CONNECTION_NULL);
        appendStringAndDecLN(getErrorOutputStreamLogger(), "addr=", deviceAddress);
        return VL53L0X_ERROR_CONTROL_INTERFACE;
    }

    portableMasterWaitSendI2C(i2cBusConnection);
    // Wait till Start sequence is completed
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    // I2C PICs adress use 8 bits and not 7 bits
    portableMasterWriteI2C(i2cBusConnection, deviceAddress);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterWriteI2C(i2cBusConnection, index);
    WaitI2cBusConnection(i2cBusConnection);

#ifdef VL53L0X_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "\tWriting ");
    appendDec(debugOutputStream, count);
    appendString(debugOutputStream, " to addr 0x");
    appendHex2(debugOutputStream, deviceAddress);
    appendString(debugOutputStream, ": ");
#endif

    while (count--) {
        portableMasterWriteI2C(i2cBusConnection, pdata[0]);
        WaitI2cBusConnection(i2cBusConnection);
#ifdef VL53L0X_DEBUG
        appendString(debugOutputStream, "0x ");
        appendHex2(debugOutputStream, pdata[0]);
        appendString(debugOutputStream, ", ");
#endif
        pdata++;
    }
#ifdef VL53L0X_DEBUG
    println(debugOutputStream);
#endif

    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    return VL53L0X_ERROR_NONE;
}

int32_t VL53L0X_read_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata, int32_t count) {
    I2cBusConnection* i2cBusConnection = getI2cBusConnectionBySlaveAddress(deviceAddress);
    if (i2cBusConnection == NULL) {
        writeError(I2C_BUS_CONNECTION_NULL);
        appendStringAndDecLN(getErrorOutputStreamLogger(), "addr=", deviceAddress);
        return VL53L0X_ERROR_CONTROL_INTERFACE;
    }

    portableMasterWaitSendI2C(i2cBusConnection);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterWriteI2C(i2cBusConnection, deviceAddress);
    WaitI2cBusConnection(i2cBusConnection);

    // Write the "index" from which we want to read
    portableMasterWriteI2C(i2cBusConnection, index);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    // Enter in "read" mode
    portableMasterWriteI2C(i2cBusConnection, deviceAddress | 1);
    WaitI2cBusConnection(i2cBusConnection);

#ifdef VL53L0X_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "\tReading ");
    appendDec(debugOutputStream, count);
    appendString(debugOutputStream, " from addr 0x");
    appendHex2(debugOutputStream, deviceAddress);
    appendString(debugOutputStream, ": ");
#endif

    while (count--) {
        pdata[0] = portableMasterReadI2C(i2cBusConnection);
        // Ack
        if (count > 0) {
            portableMasterAckI2C(i2cBusConnection);
        } else {
            portableMasterNackI2C(i2cBusConnection);
        }
        WaitI2cBusConnection(i2cBusConnection);
#ifdef VL53L0X_DEBUG
        appendString(debugOutputStream, "0x ");
        appendHex2(debugOutputStream, pdata[0]);
        appendString(debugOutputStream, ", ");
#endif
        pdata++;
    }
#ifdef VL53L0X_DEBUG
    println(debugOutputStream);
#endif

    return VL53L0X_ERROR_NONE;
}

