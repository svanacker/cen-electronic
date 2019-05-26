#include "../timerSetup.h"
#include "../cenTimer.h"

#include "../../../common/delay/cenDelay.h"
#include "../../../common/delay/pc/cenDelayPc.h"
#include "../../../common/timer/timerInterrupt.h"
#include "../../../common/timer/timerList.h"

#include "../../../common/pc/thread/threadHelper.h"

#include <Windows.h>
#include <stdio.h>

static HANDLE timerThreadHandle;
static DWORD  timerThreadId = 0;

DWORD WINAPI timerCallback(LPVOID lpvParam) {
    printf("Timer Callback start !\r\n");
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);

    LONGLONG totalElapsedMicroseconds = 0;
    LONGLONG elapsedMicrosecondsTriggered = 0;

    const STEP_IN_MILLISECONDS = 10000;

    while (true) {
        delayMilliSecs(1);
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
    timerThreadHandle = createStandardThread(
        timerCallback,    // thread proc
        (LPVOID) timerThreadHandle,    // thread parameter 
        &timerThreadId);      // returns thread ID 
}
