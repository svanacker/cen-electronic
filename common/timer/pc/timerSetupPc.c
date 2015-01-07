#include "../timerSetup.h"
#include "../cenTimer.h"

#include "../../../common/delay/cenDelay.h"
#include "../../../common/timer/timerInterrupt.h"
#include "../../../common/timer/timerList.h"

#include <Windows.h>
#include <stdio.h>

static HANDLE timerThreadHandle;
static DWORD  timerThreadId = 0;

DWORD WINAPI timerCallback(LPVOID lpvParam) {
	printf("PC : I2C Master -> Timer listening !\r\n");
	while (true) {
		delaymSec(1);
		_internalUpdateTimerListValues();
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
