#include "clock.h"

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

void initClock(Clock* clock, WriteClockFunction* writeClock, ReadClockFunction* readClock) {
    clock->writeClock = writeClock;
    clock->readClock = readClock;
}