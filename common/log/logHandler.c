#include "logHandler.h"
#include "logLevel.h"

void initHandler(
        LogHandler* logHandler,
        char* handlerName,
        OutputStream* outputStream,
        unsigned int logLevel) {
    logHandler->handlerName = handlerName;
    logHandler->outputStream = outputStream;
    logHandler->logLevel = logLevel;
}

void printLogHandler(OutputStream* outputStream,
        LogHandler* logHandler) {
    appendKeyAndName(outputStream, "HdlName=", logHandler->handlerName);
    char* logLevelAsString = getLevelAsString(logHandler->logLevel);
    appendKeyAndName(outputStream, ",lvl=", logLevelAsString);
    appendCRLF(outputStream);
}
