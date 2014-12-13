#include "PCF8563.h"

//#include <plib.h>
#include <peripheral/legacy/i2c_legacy.h>

#include "../../common/clock/clock.h"
#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/serial/32/serial32.h"

/**
 * @see clock.h
 * @private
 * Read the hour and the date from the Pcf8563, and store in the structure.
 * @param clock the clock
 */
ClockData* _readPcf8563Clock(Clock* clock) {
    ClockData* clockData = &(clock->clockData);
    
    WaitI2C();
    portableMasterWriteI2C(PCF8563_WRITE_ADDRESS);
    WaitI2C();
    portableMasterWriteI2C(PCF8563_CLOCK_REGISTER);
    WaitI2C();
    portableStopI2C();
    WaitI2C();

    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(PCF8563_READ_ADDRESS);
    WaitI2C();

    clockData->second = portableMasterReadI2C();
    portableAckI2C();
    WaitI2C();
    clockData->minute = portableMasterReadI2C();
    portableAckI2C();
    WaitI2C();
    clockData->hour = portableMasterReadI2C();
    portableAckI2C();
    WaitI2C();
    clockData->day = portableMasterReadI2C();
    portableAckI2C();
    WaitI2C();
    clockData->dayofweek = portableMasterReadI2C();
    portableAckI2C();
    WaitI2C();
    clockData->month = portableMasterReadI2C();
    portableAckI2C();
    WaitI2C();
    clockData->year = portableMasterReadI2C();
    portableNackI2C();
    WaitI2C();
    portableStopI2C();
    WaitI2C();
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

    portableMasterWaitSendI2C();
    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(PCF8563_WRITE_ADDRESS);
    WaitI2C();
    portableMasterWriteI2C(PCF8563_CLOCK_REGISTER);
    WaitI2C();
    portableMasterWriteI2C(clockData->second);
    WaitI2C();
    portableMasterWriteI2C(clockData->minute);
    WaitI2C();
    portableMasterWriteI2C(clockData->hour);
    WaitI2C();
    portableMasterWriteI2C(clockData->day);
    WaitI2C();
    portableMasterWriteI2C(clockData->dayofweek);
    WaitI2C();
    portableMasterWriteI2C(clockData->month);
    WaitI2C();
    portableMasterWriteI2C(clockData->year);
    WaitI2C();
    portableStopI2C();
    WaitI2C();
}

void initClockPCF8563(Clock* clock) {
    initClock(clock, _writePcf8563Clock, _readPcf8563Clock);
}