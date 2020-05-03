#include <stdlib.h>
#include <stdbool.h>

#include "tcs34725.h"

#include "../../common/delay/cenDelay.h"
#include "../../common/i2c/i2cBusConnectionList.h"
#include "../../common/i2c/master/i2cMaster.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/delayTimer.h"

#include "../../common/io/printWriter.h"

// #define TCS34725_DEBUG     true

void initTcs34725Struct(Tcs34725* tcs34725, I2cBusConnection* i2cBusConnection) {
    tcs34725->i2cBusConnection = i2cBusConnection;
    tcs34725->integrationTime = TCS34725_INTEGRATIONTIME_2_4MS;
    tcs34725->gain = TCS34725_GAIN_60X;
    tcs34725->initialized = false;
}

/**
 * @private
 * Writes a register and an 8 bit value over I2C
 */
void tcs34725_write8(I2cBusConnection* i2cBusConnection, uint8_t reg, uint8_t value) {
#ifdef TCS34725_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "write8\n");
#endif    
    portableMasterWaitSendI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, TCS34725_ADDRESS);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, TCS34725_COMMAND_BIT | reg);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, value);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
}

/**
 * @private
 * Reads an 8 bit value over I2C
 */
uint8_t tcs34725_read8(I2cBusConnection* i2cBusConnection, uint8_t reg) {
#ifdef TCS34725_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "Read8\n");

    appendString(debugOutputStream, "reg : ");
    appendHex2(debugOutputStream, reg);
    println(debugOutputStream);
#endif
    portableMasterWaitSendI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

#ifdef TCS34725_DEBUG
    appendString(debugOutputStream, "TCS34725_ADDRESS : ");
    appendHex2(debugOutputStream, TCS34725_ADDRESS);
    println(debugOutputStream);
#endif

    portableMasterWriteI2C(i2cBusConnection, TCS34725_ADDRESS);
    WaitI2cBusConnection(i2cBusConnection);

#ifdef TCS34725_DEBUG
    appendString(debugOutputStream, "TCS34725_COMMAND_BIT | reg : ");
    appendHex2(debugOutputStream, TCS34725_COMMAND_BIT | reg);
    println(debugOutputStream);
#endif

    portableMasterWriteI2C(i2cBusConnection, TCS34725_COMMAND_BIT | reg);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    // Read
#ifdef TCS34725_DEBUG    
    appendString(debugOutputStream, "TCS34725_ADDRESS | 0x01 : ");
    appendHex2(debugOutputStream, TCS34725_ADDRESS | 0x01);
    println(debugOutputStream);
#endif
    /*
    portableMasterWriteI2C(i2cBusConnection, TCS34725_COMMAND_BIT | reg);
    WaitI2cBusConnection(i2cBusConnection);
     */

    portableMasterWriteI2C(i2cBusConnection, TCS34725_ADDRESS | 0x01);
    WaitI2cBusConnection(i2cBusConnection);

    uint8_t x = portableMasterReadI2C(i2cBusConnection);

    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    return x;
}

/**
 * @private
 * Reads a 16 bit values over I2C
 */
uint16_t tcs34725_read16(I2cBusConnection* i2cBusConnection, uint8_t reg) {
#ifdef TCS34725_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "read16\n");
#endif

    uint8_t low = tcs34725_read8(i2cBusConnection, reg);
    uint8_t high = tcs34725_read8(i2cBusConnection, ++reg);

    return (high << 8) | low;
}

/**
 * Enables the device.
 */
void tcs34725_enable(I2cBusConnection* i2cBusConnection) {
#ifdef TCS34725_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "Enable\n");
#endif

    tcs34725_write8(i2cBusConnection, TCS34725_ENABLE, TCS34725_ENABLE_PON);
    delayMilliSecs(3);
    tcs34725_write8(i2cBusConnection, TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
}

/**
 * Disables the device (putting it in lower power sleep mode).
 */
void tcs34725_disable(I2cBusConnection* i2cBusConnection) {
#ifdef TCS34725_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "Disable\n");
#endif

    // Turn the device off to save power
    uint8_t reg;
    reg = tcs34725_read8(i2cBusConnection, TCS34725_ENABLE);
    tcs34725_write8(i2cBusConnection, TCS34725_ENABLE, reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
}

/**
 * Initializes I2C and configures the sensor (call this function before doing anything else)
 */
bool tcs34725_begin(Tcs34725* tcs34725) {
#ifdef TCS34725_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "begin\n");
#endif
    I2cBusConnection* i2cBusConnection = tcs34725->i2cBusConnection;
    // Make sure we're actually connected
    uint8_t x = tcs34725_read8(i2cBusConnection, TCS34725_ID);

#ifdef TCS34725_DEBUG
    appendString(debugOutputStream, "Tcs34725_Id : ");
    appendHex2(debugOutputStream, x);
    println(debugOutputStream);
#endif
    if ((x != 0x44) && (x != 0x10)) {
        return false;
    }
    tcs34725->initialized = true;

    // Set default integration time and gain
    tcs34725_setIntegrationTime(tcs34725, tcs34725->integrationTime);
    tcs34725_setGain(tcs34725, tcs34725->gain);

    // Note: by default, the device is in power down mode on bootup
    tcs34725_enable(i2cBusConnection);

    return true;
}

/**
 * Sets the integration time for the TC34725
 */
void tcs34725_setIntegrationTime(Tcs34725* tcs34725, tcs34725IntegrationTime_t integrationTime) {
#ifdef TCS34725_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "tcs34725_setIntegrationTime\n");
#endif

    I2cBusConnection* i2cBusConnection = tcs34725->i2cBusConnection;
    if (!tcs34725->initialized) {
        tcs34725_begin(tcs34725);
    }

    // Update the timing register
    tcs34725_write8(i2cBusConnection, TCS34725_ATIME, integrationTime);

    // Update value placeholders
    tcs34725->integrationTime = integrationTime;
}

/**
 * Adjusts the gain on the TCS34725 (adjusts the sensitivity to light)
 */
void tcs34725_setGain(Tcs34725* tcs34725, tcs34725Gain_t gain) {
#ifdef TCS34725_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "tcs34725_setGain\n");
#endif

    I2cBusConnection* i2cBusConnection = tcs34725->i2cBusConnection;
    if (!tcs34725->initialized) {
        tcs34725_begin(tcs34725);
    }
    // Update the timing register
    tcs34725_write8(i2cBusConnection, TCS34725_CONTROL, gain);

    // Update value placeholders
    tcs34725->gain = gain;
}

/**
 * Reads the raw red, green, blue and clear channel values
 */
void tcs34725_getRawData(Tcs34725* tcs34725, uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c) {
#ifdef TCS34725_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "tcs34725_getRawData\n");
#endif

    I2cBusConnection* i2cBusConnection = tcs34725->i2cBusConnection;
    if (!tcs34725->initialized) {
        tcs34725_begin(tcs34725);
    }

    *c = tcs34725_read16(i2cBusConnection, TCS34725_CDATAL);
    *r = tcs34725_read16(i2cBusConnection, TCS34725_RDATAL);
    *g = tcs34725_read16(i2cBusConnection, TCS34725_GDATAL);
    *b = tcs34725_read16(i2cBusConnection, TCS34725_BDATAL);

    // Set a delay for the integration time
    switch (tcs34725->integrationTime) {
        case TCS34725_INTEGRATIONTIME_2_4MS:
            timerDelayMilliSeconds(3);
            break;
        case TCS34725_INTEGRATIONTIME_24MS:
            timerDelayMilliSeconds(24);
            break;
        case TCS34725_INTEGRATIONTIME_50MS:
            timerDelayMilliSeconds(50);
            break;
        case TCS34725_INTEGRATIONTIME_101MS:
            timerDelayMilliSeconds(101);
            break;
        case TCS34725_INTEGRATIONTIME_154MS:
            timerDelayMilliSeconds(154);
            break;
        case TCS34725_INTEGRATIONTIME_700MS:
            timerDelayMilliSeconds(700);
            break;
    }
}

void tcs34725_setInterrupt(Tcs34725* tcs34725, bool i) {
#ifdef TCS34725_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "tcs34725_setInterrupt\n");
#endif

    I2cBusConnection* i2cBusConnection = tcs34725->i2cBusConnection;
    uint8_t r = tcs34725_read8(i2cBusConnection, TCS34725_ENABLE);
    if (i) {
        r |= TCS34725_ENABLE_AIEN;
    } else {
        r &= ~TCS34725_ENABLE_AIEN;
    }
    tcs34725_write8(i2cBusConnection, TCS34725_ENABLE, r);
}

void tcs34725_clearInterrupt(Tcs34725* tcs34725) {
#ifdef TCS34725_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "tcs34725_clearInterrupt\n");
#endif

    I2cBusConnection* i2cBusConnection = tcs34725->i2cBusConnection;
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, TCS34725_ADDRESS);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, TCS34725_COMMAND_BIT | 0x66);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
}

void tcs34725_setIntLimits(Tcs34725* tcs34725, uint16_t low, uint16_t high) {
#ifdef TCS34725_DEBUG
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendString(debugOutputStream, "tcs34725_setIntLimits\n");
#endif

    I2cBusConnection* i2cBusConnection = tcs34725->i2cBusConnection;
    tcs34725_write8(i2cBusConnection, 0x04, low & 0xFF);
    tcs34725_write8(i2cBusConnection, 0x05, low >> 8);
    tcs34725_write8(i2cBusConnection, 0x06, high & 0xFF);
    tcs34725_write8(i2cBusConnection, 0x07, high >> 8);
}