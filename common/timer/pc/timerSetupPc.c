#include "../timerSetup.h"
#include "../cenTimer.h"

#include "../../../common/delay/cenDelay.h"
#include "../../../common/delay/pc/cenDelayPc.h"
#include "../../../common/timer/timerInterrupt.h"
#include "../../../common/timer/timerList.h"

#include <Windows.h>
#include <stdio.h>

static HANDLE timerThreadHandle;
static DWORD  timerThreadId = 0;

DWORD WINAPI timerCallback(LPVOID lpvParam) {
    printf("PC : I2C Master -> Timer listening !\r\n");
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);

    LONGLONG totalElapsedMicroseconds = 0;
    LONGLONG elapsedMicrosecondsTriggered = 0;

    const STEP_IN_MILLISECONDS = 10000;

    while (true) {
        delaymSec(1);
        totalElapsedMicroseconds = getElapsedTimeInMicroSeconds(startTime);
        if (totalElapsedMicroseconds - elapsedMicrosecondsTriggered > STEP_IN_MILLISECONDS) {
            elapsedMicrosecondsTriggered += STEP_IN_MILLISECONDS;

            int increment = (int)((STEP_IN_MILLISECONDS * TIME_DIVIDER_1_HERTZ) / 1000000L);
            _internalUpdateTimerListValues(increment);
        }
        // handleI2CDataFromMaster();
    }
    printf("timerCallback exiting.\n");

    return 1;
}

/**
 * @private
 */
void _initTimers() {
    // Create a thread to handle timer
    timerThreadHandle = CreateThread(
        NULL,              // no security attribute 
        0,                 // default stack size 
        timerCallback,    // thread proc
        (LPVOID) timerThreadHandle,    // thread parameter 
        0,                 // not suspended 
        &timerThreadId);      // returns thread ID 
}
