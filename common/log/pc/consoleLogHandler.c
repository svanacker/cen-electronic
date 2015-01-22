#include "consoleLogHandler.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"
#include "../../../common/log/logHandler.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/pc/consoleOutputStream.h"

static OutputStream consoleOutputStream;

LogHandler* addConsoleLogHandler(LogLevel consoleLogLevel) {
    initConsoleOutputStream(&consoleOutputStream);
	LogHandler* result = addLogHandler("CONSOLE", &consoleOutputStream, consoleLogLevel);
    return result;
}
