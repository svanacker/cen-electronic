#include <stdlib.h>

#include "logHandlerList.h"

#include "logHandler.h"

#include "../../common/commons.h"
#include "../../common/error/error.h"

void initLogHandlerList(LogHandlerList* logHandlerList, LogHandler(*logHandlerListArray)[], unsigned char logHandlerListSize) {
	logHandlerList->logHandlers = logHandlerListArray;
	logHandlerList->maxSize = logHandlerListSize;
}

LogHandler* addLogHandlerToList(LogHandlerList* logHandlerList, LogLevel logLevel, char* handlerName, OutputStream* outputStream) {
	if (logHandlerList == NULL || logHandlerList->maxSize == 0) {
		writeError(LOG_LIST_NOT_INITIALIZED);
		return NULL;
	}
	unsigned char size = logHandlerList->size;

	if (size < logHandlerList->maxSize) {
		LogHandler* result = getLogHandler(logHandlerList, size);
		// get a pointer on a logHandler already allocated (because we provide at init a pointer on an array of logHandler
		logHandlerList->size++;
		initHandler(result, handlerName, outputStream, logLevel);
		return result;
	}
	else {
		writeError(LOG_LIST_TOO_MUCH_LOG_HANDLERS);
		return NULL;
	}
}

LogHandler* getLogHandler(LogHandlerList* logHandlerList, int logHandlerIndex) {
	if (logHandlerList == NULL || logHandlerList->maxSize == 0) {
		writeError(LOG_LIST_NOT_INITIALIZED);
		return NULL;
	}
	if (logHandlerIndex < 0 || logHandlerIndex >= logHandlerList->maxSize) {
		writeError(LOG_LIST_OUT_OF_BOUNDS);
		return NULL;
	}
	LogHandler* result = (LogHandler*)logHandlerList->logHandlers;
	// we don't need use sizeof because our pointer is a LogHandler* pointer, so the shift
	// is already of the structure, we just have to shift of index.
	result += logHandlerIndex;

	return result;
}

int getLogHandlerCount(LogHandlerList* logHandlerList) {
    return logHandlerList->size;
}
