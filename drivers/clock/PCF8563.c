#include "PCF8563.h"

#include <peripheral/legacy/i2c_legacy.h>

#include "../../common/clock/clock.h"
#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

/**
 * @see clock.h
 * @private
 * Read the hour and the date from the Pcf8563, and store in the structure.
 * @param clock the clock
 */
ClockData* _readPcf8563Clock(Clock* clock) {
    ClockData* clockData = &(clock->clockData);

    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(PCF8563_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(PCF8563_CLOCK_REGISTER);
    WaitI2C(i2cBus);
    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);

    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(PCF8563_READ_ADDRESS);
    WaitI2C(i2cBus);

    clockData->second = portableMasterReadI2C(i2cBus);
    portableAckI2C(i2cBus);
    WaitI2C(i2cBus);
    clockData->minute = portableMasterReadI2C(i2cBus);
    portableAckI2C(i2cBus);
    WaitI2C(i2cBus);
    clockData->hour = portableMasterReadI2C(i2cBus);
    portableAckI2C(i2cBus);
    WaitI2C(i2cBus);
    clockData->day = portableMasterReadI2C(i2cBus);
    portableAckI2C(i2cBus);
    WaitI2C(i2cBus);
    clockData->dayofweek = portableMasterReadI2C(i2cBus);
    portableAckI2C(i2cBus);
    WaitI2C(i2cBus);
    clockData->month = portableMasterReadI2C(i2cBus);
    portableAckI2C(i2cBus);
    WaitI2C(i2cBus);
    clockData->year = portableMasterReadI2C(i2cBus);
    portableNackI2C(i2cBus);
    WaitI2C(i2cBus);
    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);
    clockData->second = clockData->second & 0b01111111;
    clockData->minute = clockData->minute & 0b01111111;
    clockData->hour = clockData->hour & 0b00111111;
    clockData->day = clockData->day & 0b00111111;
    clockData->dayofweek = clockData->dayofweek & 0b00001111;
    clockData->month = clockData->month & 0b00011111;

}

/**
 * @see clock.h
 * @private
 * Set the Clock into the Pcf8563.
 * @param clock the new value of clock
 */
void _writePcf8563Clock(Clock* clock) {
    ClockData* clockData = &(clock->clockData);

    portableMasterWaitSendI2C(i2cBus);
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(PCF8563_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(PCF8563_CLOCK_REGISTER);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(clockData->second);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(clockData->minute);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(clockData->hour);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(clockData->day);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(clockData->dayofweek);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(clockData->month);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(clockData->year);
    WaitI2C(i2cBus);
    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);
}

void initClockPCF8563(Clock* clock) {
    initClock(clock, _writePcf8563Clock, _readPcf8563Clock);
}