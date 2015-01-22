#include "logger.h"
#include "logHandler.h"
#include "logHandlerList.h"

#include "../../common/io/outputStream.h"

void printLogHandler(OutputStream* outputStream, LogHandler* logHandler) {
    appendKeyAndName(outputStream, "HdlName=", logHandler->handlerName);
    char* logLevelAsString = getLevelAsString(logHandler->logLevel);
    appendKeyAndName(outputStream, ",lvl=", logLevelAsString);
    println(outputStream);
}

void printLogger(OutputStream* outputStream) {
    Logger* logger = getLoggerInstance();
    appendKeyAndName(outputStream, "GlbLogLvl=", getLevelAsString(logger->globalLogLevel));
    appendKeyAndName(outputStream, ",writeLogLvl=", getLevelAsString(logger->writeLogLevel));
    println(outputStream);

    // For Each LogHandler
    LogHandlerList* logHandlerList = getLoggerHandlerList();
    int count = getLogHandlerCount(logHandlerList);
    int i;
    for (i = 0; i < count; i++) {
        LogHandler* logHandler = getLogHandler(logHandlerList, i);
        appendStringAndDec(outputStream, "log(", i);
        appendString(outputStream, ")=");
        printLogHandler(outputStream, logHandler);
    }
}
