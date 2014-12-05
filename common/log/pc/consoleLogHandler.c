#include "consoleLogHandler.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"
#include "../../../common/log/logHandler.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/pc/consoleOutputStream.h"

static OutputStream consoleOutputStream;
static LogHandler consoleLogHandler;

LogHandler* addConsoleLogHandler(LogLevel consoleLogLevel) {
	initConsoleOutputStream(&consoleOutputStream);
	addLogHandler(&consoleLogHandler, "CONSOLE", &consoleOutputStream, consoleLogLevel);
	return &consoleLogHandler;
}
