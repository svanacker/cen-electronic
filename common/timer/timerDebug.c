#include "cenTimer.h"
#include "timerList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printTimer(OutputStream* outputStream, Timer* timer) {
	appendString(outputStream, "Timer:code=");
	appendDec(outputStream, timer->timerCode);
	appendString(outputStream, ",div=");
	appendDec(outputStream, timer->timeDiviser);
	appendString(outputStream, ",enabled=");
	appendDec(outputStream, timer->enabled);
	appendString(outputStream, ",working=");
	appendDec(outputStream, timer->working);
}

void printTimerList(TimerList* timerList, OutputStream* outputStream) {
	int i;
	for (i = 0; i < timerList->size; i++) {
		Timer* timer = timerList->timers[i];
		printTimer(outputStream, timer);
		appendCRLF(outputStream);
	}
}
