#include "cenTimer.h"
#include "timerList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define TIMER_DEBUG_IDX_COLUMN_LENGTH	            5
#define TIMER_DEBUG_CODE_COLUMN_LENGTH	            5
#define TIMER_DEBUG_NAME_COLUMN_LENGTH	            25
#define TIMER_DEBUG_DIV_COLUMN_LENGTH	            8
#define TIMER_DEBUG_TIME_COLUMN_LENGTH	            10
#define TIMER_DEBUG_INTERNAL_COUNTER_COLUMN_LENGTH	10
#define TIMER_DEBUG_MARK_TIME_COLUMN_LENGTH	        10
#define TIMER_DEBUG_ENABLED_COLUMN_LENGTH	        7
#define TIMER_DEBUG_WORKING_COLUMN_LENGTH	        7
#define TIMER_DEBUG_LAST_COLUMN_LENGTH	            10

/**
* Private.
*/
void printTimerListHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "idx", TIMER_DEBUG_CODE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "code", TIMER_DEBUG_CODE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "name", TIMER_DEBUG_NAME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "div", TIMER_DEBUG_DIV_COLUMN_LENGTH);
	appendStringHeader(outputStream, "counter", TIMER_DEBUG_INTERNAL_COUNTER_COLUMN_LENGTH);
	appendStringHeader(outputStream, "time", TIMER_DEBUG_TIME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "markTime", TIMER_DEBUG_MARK_TIME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "ON/OFF", TIMER_DEBUG_ENABLED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "working", TIMER_DEBUG_WORKING_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, TIMER_DEBUG_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);

}

void printTimer(OutputStream* outputStream, int index, Timer* timer) {
	appendDecTableData(outputStream, index, TIMER_DEBUG_IDX_COLUMN_LENGTH);
	appendDecTableData(outputStream, timer->timerCode, TIMER_DEBUG_CODE_COLUMN_LENGTH);
	appendStringTableData(outputStream, timer->name, TIMER_DEBUG_NAME_COLUMN_LENGTH);
	appendDecTableData(outputStream, timer->timeDiviser, TIMER_DEBUG_DIV_COLUMN_LENGTH);
	appendDecTableData(outputStream, timer->timeInternalCounter, TIMER_DEBUG_INTERNAL_COUNTER_COLUMN_LENGTH);
	appendDecTableData(outputStream, timer->time, TIMER_DEBUG_TIME_COLUMN_LENGTH);
	appendDecTableData(outputStream, timer->markTime, TIMER_DEBUG_MARK_TIME_COLUMN_LENGTH);
	appendDecTableData(outputStream, timer->enabled, TIMER_DEBUG_ENABLED_COLUMN_LENGTH);
	appendDecTableData(outputStream, timer->working, TIMER_DEBUG_WORKING_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, TIMER_DEBUG_LAST_COLUMN_LENGTH);
}

void printTimerList(OutputStream* outputStream, TimerList* timerList) {
	printTimerListHeader(outputStream);
    int i;
    for (i = 0; i < timerList->size; i++) {
        Timer* timer = (Timer*) timerList->timers;
        timer += i;
        printTimer(outputStream, i, timer);
    }
	appendTableHeaderSeparatorLine(outputStream);
}
