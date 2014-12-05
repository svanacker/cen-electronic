#include "logHandler.h"
#include "logLevel.h"
#include "../../common/io/outputStream.h"

void initHandler(
        LogHandler* logHandler,
        char* handlerName,
        OutputStream* outputStream,
        LogLevel logLevel) {
    logHandler->handlerName = handlerName;
    logHandler->outputStream = outputStream;
    logHandler->logLevel = logLevel;
}

