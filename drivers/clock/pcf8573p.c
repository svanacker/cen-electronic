#include <plib.h>

#include "pcf8573p.h"

#include "../../common/clock/clock.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/**
 * @see clock.h
 * @private 
 * Read the hour and the date from the Pcf8573, and store in the structure.
 * @param clock the clock
 */
ClockData* _readPcf8573Clock(Clock* clock) {
    ClockData* clockData = &(clock->clockData);
    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(PCF8573P_WRITE_ADDRESS);
    WaitI2C();
    // TODO JJ : Magic Constant
    portableMasterWriteI2C(0x00);
    WaitI2C();
    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(PCF8573P_READ_ADDRESS);
    WaitI2C();
    clockData->hour = portableMasterReadI2C();
    AckI2C1();
    WaitI2C();
    clockData->minute = portableMasterReadI2C();
    AckI2C1();
    WaitI2C();
    clockData->day = portableMasterReadI2C();
    AckI2C1();
    WaitI2C();
    clockData->month = portableMasterReadI2C();
    NotAckI2C1();
    WaitI2C();
    portableCloseI2C();
    WaitI2C();

    return clockData;
}

/**
 * @see clock.h
 * @private 
 * Set the Clock into the Pcf8573.
 * @param clock the new value of clock
 */
void _writePcf8573Clock(Clock* clock) {
    ClockData* clockData = &(clock->clockData);
    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(PCF8573P_WRITE_ADDRESS);
    // TODO JJ : Magic Constant
    portableMasterWriteI2C(0x00);
    portableMasterWriteI2C(clockData->hour);
    portableMasterWriteI2C(clockData->minute);
    portableMasterWriteI2C(clockData->day);
    portableMasterWriteI2C(clockData->month);
    portableCloseI2C();
    WaitI2C();
}

void initClockPCF8573(Clock* clock) {
    initClock(clock, _writePcf8573Clock, _readPcf8573Clock);
}