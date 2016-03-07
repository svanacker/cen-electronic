#include "clock.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printClock(OutputStream* outputStream, Clock* clock) {
    ClockData* clockData = &(clock->clockData);
    appendHex2(outputStream, clockData->hour);
    append(outputStream, ':');
    appendHex2(outputStream, clockData->minute);
    append(outputStream, ':');
    appendHex2(outputStream, clockData->second);

    append(outputStream, ' ');
    appendHex2(outputStream, clockData->day);

    append(outputStream, '/');
    appendHex2(outputStream, clockData->month);
    append(outputStream, '/');
    appendHex2(outputStream, clockData->year);
}

void initClock(Clock* clock, WriteClockFunction* writeClock, ReadClockFunction* readClock, int* object) {
    clock->clockData.year = 0;
    clock->clockData.month = 0;
    clock->clockData.dayofweek = 0;
    clock->clockData.day = 0;
    clock->clockData.hour = 0;
    clock->clockData.minute = 0;
    clock->clockData.second = 0;
    clock->writeClock = writeClock;
    clock->readClock = readClock;
    clock->object = object;
}

bool isClockInitialized(Clock* clock) {
    if (clock->writeClock == NULL || clock->readClock == NULL) {
        return false;
    }
    return true;
}