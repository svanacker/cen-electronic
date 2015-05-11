#include "pcf8573p.h"

#include "../../common/clock/clock.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

I2cBus* _pcf8573GetI2c(Clock* clock) {
    I2cBus* result = (I2cBus*) clock->object;

    return result;
}

/**
 * @see clock.h
 * @private 
 * Read the hour and the date from the Pcf8573, and store in the structure.
 * @param clock the clock
 */
ClockData* _readPcf8573Clock(Clock* clock) {
    I2cBus* i2cBus = _pcf8573GetI2c(clock);
    ClockData* clockData = &(clock->clockData);
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, PCF8573P_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    // TODO JJ : Magic Constant
    portableMasterWriteI2C(i2cBus, 0x00);
    WaitI2C(i2cBus);
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, PCF8573P_READ_ADDRESS);
    WaitI2C(i2cBus);
    clockData->hour = portableMasterReadI2C(i2cBus);
    portableAckI2C(i2cBus);
    WaitI2C(i2cBus);
    clockData->minute = portableMasterReadI2C(i2cBus);
    portableAckI2C(i2cBus);
    WaitI2C(i2cBus);
    clockData->day = portableMasterReadI2C(i2cBus);
    portableAckI2C(i2cBus);
    WaitI2C(i2cBus);
    clockData->month = portableMasterReadI2C(i2cBus);
    portableNackI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterCloseI2C(i2cBus);
    WaitI2C(i2cBus);

    return clockData;
}

/**
 * @see clock.h
 * @private 
 * Set the Clock into the Pcf8573.
 * @param clock the new value of clock
 */
void _writePcf8573Clock(Clock* clock) {
    I2cBus* i2cBus = _pcf8573GetI2c(clock);
    ClockData* clockData = &(clock->clockData);
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, PCF8573P_WRITE_ADDRESS);
    // TODO JJ : Magic Constant
    portableMasterWriteI2C(i2cBus, 0x00);
    portableMasterWriteI2C(i2cBus, clockData->hour);
    portableMasterWriteI2C(i2cBus, clockData->minute);
    portableMasterWriteI2C(i2cBus, clockData->day);
    portableMasterWriteI2C(i2cBus, clockData->month);
    portableMasterCloseI2C(i2cBus);
    WaitI2C(i2cBus);
}

void initClockPCF8573(Clock* clock, I2cBus* i2cBus) {
    initClock(clock, _writePcf8573Clock, _readPcf8573Clock, (int*) i2cBus);
}