#include "clock.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/** Singleton of clock (private) */
static Clock globalClock;

Clock* getGlobalClock() {
    return &globalClock;
}

void printClock(OutputStream* outputStream, Clock* clock){
    appendHex2(outputStream, clock->hour);
    append(outputStream, ':');
    appendHex2(outputStream, clock->minute);
    append(outputStream, ':');
    appendHex2(outputStream, clock->second);

    append(outputStream, ' ');
    appendHex2(outputStream, clock->day);

    append(outputStream, '/');
    appendHex2(outputStream, clock->month);
    append(outputStream, '/');
    appendHex2(outputStream, clock->year);
}
