#ifndef CONSOLE_LOG_HANDLER_H
#define CONSOLE_LOG_HANDLER_H

#include "../../../common/log/logHandler.h"

// This class must not be included into the micro-controller, because it will include otherwise function that are not wanted like fprintf or getchar() from stdio.h !
#ifdef PROG_32
MUST FAIL !!!
#endif
#ifdef PROG_30
MUST FAIL !!!
#endif

/**
 * Add a console Handler to the list of logs, so that every log will be written on the console (with printf !).
 * @param consoleLogLevel the level of log for console
 */
LogHandler* addConsoleLogHandler(int consoleLogLevel, unsigned long categoryLogMask);

#endif
