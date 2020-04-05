#ifndef LOGGER_H
#define LOGGER_H

#include <stdlib.h>

#include "logLevel.h"
#include "logHandler.h"
#include "logHandlerList.h"

#include "../../common/io/outputStream.h"

typedef struct Logger {
    /** A level corresponding to the minimal logLevel which must be logged. */
    enum LogLevel globalLogLevel;
    /** the level that we used to write. */
    enum LogLevel writeLogLevel;
    /** The default categoryMask when we do not define it .*/
    unsigned long defaultLogCategoryMask;
    /** the current mask that we are currently using .*/
    unsigned long logCategoryMask;
    /** the list of handler. */
    LogHandlerList* logHandlerList;
    /** The outputStream as an interface to the developer. */
    OutputStream* outputStream;
} Logger;

/**
 * Returns the singleton logger handler list object.
 * Used only it for debug
 * @return the singleton logger handler list object
 */
LogHandlerList* getLoggerHandlerList();

/**
 * Init the log system.
 * @param globalLevel the global level of log (independent of each handler level)
 * @param handlerListArray the array containing all log Handlers
 * @param handlerListSize the size of the previous array
 */
void initLogs(enum LogLevel globalLevel, LogHandler(*handlerListArray)[], unsigned char handlerListSize, unsigned long defaultCategoryMask);

/**
 * Add a log Handler to the system.
 * @param handlerName the name of the logHandler
 * @param outputStream the stream in which we write
 * @param logLevel the log level for this handler
 * @param result the logHandler structure created
 */
LogHandler* addLogHandler(char* handlerName,
        OutputStream* outputStream,
        enum LogLevel logLevel,
        unsigned long logCategoryMask);

/**
 * Get a compatible outputStream (to be used with printWriter) in which we write.
 * @param writeLogLevel The log level which will be used to write the underlying log.
 * @param logCategoryMask the mask which is used to select right handler target
 * @return the compatible outputStream (to be used with printWriter) in which we write
 */
OutputStream* getOutputStreamLogger(enum LogLevel writeLogLevel, unsigned long logCategoryMask);

/**
 * Get an outputStream for log with TRACE level and default category level.
 * @return an outputStream for log with TRACE level and default category level
 */
OutputStream* getTraceOutputStreamLogger();

/**
 * Get an outputStream for log with DEBUG level and default category level.
 * @return an outputStream for log with DEBUG level and default category level
 */
OutputStream* getDebugOutputStreamLogger();

/**
 * Get an outputStream for log with INFO level and default category level.
 * @return an outputStream for log with INFO level and default category level
 */
OutputStream* getInfoOutputStreamLogger();

/**
 * Get an outputStream for log with WARNING level and default category level.
 * @return an outputStream for log with WARNING level and default category level
 */
OutputStream* getWarningOutputStreamLogger();

/**
 * Get an outputStream for log with ERROR level and default category level.
 * @return an outputStream for log with ERROR level and default category level
 */
OutputStream* getErrorOutputStreamLogger();

/**
 * Get an outputStream for log with ALWAYS level and default category level.
 * @return an outputStream for log with ALWAYS level and default category level
 */
OutputStream* getAlwaysOutputStreamLogger();

/**
 * Returns true if the logger handle at least the trace level
 * @return
 */
bool isLoggerTraceEnabled(void);

/**
 * Returns true if the logger handle at least the debug level
 * @return 
 */
bool isLoggerDebugEnabled(void);

bool isLoggerInfoEnabled(void);

bool isLoggerWarningEnabled(void);

bool isLoggerErrorEnabled(void);

bool isLoggerAlwaysEnabled(void);

/**
 * Returns the singleton for logger.
 */
Logger* getLoggerInstance();

#endif
