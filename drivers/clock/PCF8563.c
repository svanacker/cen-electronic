#include "PCF8563.h"

#include <peripheral/legacy/i2c_legacy.h>

#include "../../device/clock/clock.h"
#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/io/buffer.h"

#define PCF8563_CLOCK_BUFFER_LENGTH     10
static Buffer pcf8563Buffer;
static char pcf8563BufferArray[PCF8563_CLOCK_BUFFER_LENGTH];
static Buffer pcf8563Buffer;

void updateClockFromHardware (Clock* clock){
    bool bufferInitialized = isBufferInitialized(&pcf8563Buffer);
    if (!bufferInitialized) {
        initBuffer(&pcf8563Buffer, &pcf8563BufferArray, PCF8563_CLOCK_BUFFER_LENGTH, "CLOCK_BUFFER", "");
    }
    i2cMasterRegisterReadBuffer(PCF8563_ADDRESS, PCF8563_CLOCK_REGISTER, 7, &pcf8563Buffer);
    int d = bufferReadChar(&pcf8563Buffer);
    clock->second = d & 0b01111111;
    d = bufferReadChar(&pcf8563Buffer);
    clock->minute = d & 0b01111111;
    d = bufferReadChar(&pcf8563Buffer);
    clock->hour = d & 0b00111111;
    d = bufferReadChar(&pcf8563Buffer);
    clock->day = d & 0b00111111;
    d = bufferReadChar(&pcf8563Buffer);
    clock->dayofweek = d & 0b00001111;
    d = bufferReadChar(&pcf8563Buffer);
    clock->month = d & 0b00011111;
    d = bufferReadChar(&pcf8563Buffer);
    clock->year = d ;
}

void updateClockToHardware (Clock* clock){
    portableMasterWaitSendI2C();

    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(PCF8563_ADDRESS);
    WaitI2C();
    portableMasterWriteI2C(PCF8563_CLOCK_REGISTER);
    WaitI2C();
    portableMasterWriteI2C(clock->second);
    WaitI2C();
    portableMasterWriteI2C(clock->minute);
    WaitI2C();
    portableMasterWriteI2C(clock->hour);
    WaitI2C();
    portableMasterWriteI2C(clock->day);
    WaitI2C();
    portableMasterWriteI2C(clock->dayofweek);
    WaitI2C();
    portableMasterWriteI2C(clock->month);
    WaitI2C();
    portableMasterWriteI2C(clock->year);
    WaitI2C();

    portableStopI2C();
}
