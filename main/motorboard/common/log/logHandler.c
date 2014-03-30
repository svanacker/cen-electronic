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

