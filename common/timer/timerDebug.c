#include "cenTimer.h"
#include "timerList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printTimer(OutputStream* outputStream, Timer* timer) {
	appendStringAndDec(outputStream, "Timer:code=", timer->timerCode);
	appendStringAndDec(outputStream, ",div=", timer->timeDiviser);
	appendStringAndDec(outputStream, ",time=", timer->time);
	appendStringAndDec(outputStream, ",timeInternalCounter=", timer->timeInternalCounter);
	appendStringAndDec(outputStream, ",markTime=", timer->markTime);

	appendStringAndDec(outputStream, ",enabled=", timer->enabled);
	appendStringAndDec(outputStream, ",working=", timer->working);
}

void printTimerList(OutputStream* outputStream, TimerList* timerList) {
	int i;
	for (i = 0; i < timerList->size; i++) {
		Timer* timer = (Timer*) timerList->timers;
	 	timer += i;

		printTimer(outputStream, timer);
		appendCRLF(outputStream);
	}
}
