#include "PCF8563.h"

#include <peripheral/legacy/i2c_legacy.h>

//#include "../../device/clock/clock.h"
#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/io/buffer.h"

#define PCF8563_CLOCK_BUFFER_LENGTH     10
static Buffer pcf8563Buffer;
static char pcf8563BufferArray[PCF8563_CLOCK_BUFFER_LENGTH];
static Buffer pcf8563Buffer;

void updateClockFromHardware (ClockData* clockData){
    bool bufferInitialized = isBufferInitialized(&pcf8563Buffer);
    if (!bufferInitialized) {
        initBuffer(&pcf8563Buffer, &pcf8563BufferArray, PCF8563_CLOCK_BUFFER_LENGTH, "CLOCK_BUFFER", "");
    }
    i2cMasterRegisterReadBuffer(PCF8563_ADDRESS, PCF8563_CLOCK_REGISTER, 7, &pcf8563Buffer);
    int d = bufferReadChar(&pcf8563Buffer);
    ClockData->second = d & 0b01111111;
    d = bufferReadChar(&pcf8563Buffer);
    ClockData->minute = d & 0b01111111;
    d = bufferReadChar(&pcf8563Buffer);
    ClockData->hour = d & 0b00111111;
    d = bufferReadChar(&pcf8563Buffer);
    ClockData->day = d & 0b00111111;
    d = bufferReadChar(&pcf8563Buffer);
    ClockData->dayofweek = d & 0b00001111;
    d = bufferReadChar(&pcf8563Buffer);
    ClockData->month = d & 0b00011111;
    d = bufferReadChar(&pcf8563Buffer);
    ClockData->year = d ;
}

void updateClockToHardware (ClockData* clock){
    portableMasterWaitSendI2C();

    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(PCF8563_ADDRESS);
    WaitI2C();
    portableMasterWriteI2C(PCF8563_CLOCK_REGISTER);
    WaitI2C();
    portableMasterWriteI2C(ClockData->second);
    WaitI2C();
    portableMasterWriteI2C(ClockData->minute);
    WaitI2C();
    portableMasterWriteI2C(ClockData->hour);
    WaitI2C();
    portableMasterWriteI2C(ClockData->day);
    WaitI2C();
    portableMasterWriteI2C(ClockData->dayofweek);
    WaitI2C();
    portableMasterWriteI2C(ClockData->month);
    WaitI2C();
    portableMasterWriteI2C(ClockData->year);
    WaitI2C();

    portableStopI2C();
}
