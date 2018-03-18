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

#define VL53L0X_DEBUG    true

// PRIMITIVES

int32_t VL53L0X_write_multi(uint8_t deviceAddress, uint8_t index, uint8_t  *pdata, int32_t count) {
    I2cBusConnection* i2cConnection = getI2cBusConnectionBySlaveAddress(deviceAddress);
    
    portableMasterStartI2C(i2cConnection);
    
    portableMasterWriteI2C(i2cConnection, index);
    
#ifdef VL53L0X_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "\tWriting ");
    appendDec(debugOutputStream, count);
    appendString(debugOutputStream, " to addr 0x");
    appendHex2(debugOutputStream, deviceAddress);
    appendString(debugOutputStream, ": ");
#endif
    
    while(count--) {
        portableMasterWriteI2C(i2cConnection, pdata[0]);
        
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
    
    portableMasterStopI2C(i2cConnection);
    
    return VL53L0X_ERROR_NONE;
}

int32_t VL53L0X_read_multi(uint8_t deviceAddress,  uint8_t index, uint8_t  *pdata, int32_t count) {
    I2cBusConnection* i2cConnection = getI2cBusConnectionBySlaveAddress(deviceAddress);
    
    portableMasterStartI2C(i2cConnection);
    portableMasterWriteI2C(i2cConnection, index);
    portableMasterStopI2C(i2cConnection);
    
    // TODO : SVA Wire.requestFrom(deviceAddress, (byte)count);
#ifdef VL53L0X_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "\tReading ");
    appendDec(debugOutputStream, count);
    appendString(debugOutputStream, " from addr 0x");
    appendHex2(debugOutputStream, deviceAddress);
    appendString(debugOutputStream, ": ");
#endif

  while (count--) {
    pdata[0] = portableMasterReadI2C(i2cConnection);
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

