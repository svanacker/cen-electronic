#include "logHandlerList.h"

#include "logHandler.h"

#include "../../common/commons.h"

void addLogHandlerToList(LogHandlerList* logHandlerList, LogHandler* logHandler) {
    unsigned char size = logHandlerList->size;
    logHandlerList->logHandlers[size] = logHandler;
    logHandlerList->size++;
}

LogHandler* getLogHandler(LogHandlerList* logHandlerList, int logHandlerIndex) {
    LogHandler* result = logHandlerList->logHandlers[logHandlerIndex];
    return result;
}

int getLogHandlerCount(LogHandlerList* logHandlerList) {
    return logHandlerList->size;
}
