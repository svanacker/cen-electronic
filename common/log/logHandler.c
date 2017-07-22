#include "logHandler.h"
#include "logLevel.h"

#include "../../common/io/outputStream.h"

void initHandler(
        LogHandler* logHandler,
        char* handlerName,
        OutputStream* outputStream,
        enum LogLevel logLevel,
        unsigned long logCategoryMask) {
    logHandler->handlerName = handlerName;
    logHandler->outputStream = outputStream;
    logHandler->logLevel = logLevel;
    logHandler->logCategoryMask = logCategoryMask;
}

