#ifndef LOGGER_H
#define LOGGER_H

#include "logLevel.h"
#include "logHandler.h"
#include "logHandlerList.h"

#include "../../common/io/outputStream.h"

typedef struct Logger {
    /** A level corresponding to the minimal logLevel which must be loggued. */
    LogLevel globalLogLevel;
    /** the level that we used to write. */
    LogLevel writeLogLevel;
    /** the list of handler. */
    LogHandlerList* logHandlerList;
    /** The outputStream as an interface to the developper. */
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
 * @param globalLevel the global level of log (independant of each handler level)
 */
void initLog(LogLevel globalLevel);

/**
 * Add a log Handler to the system.
 * @param logHandler the logHandler structure
 * @param handlerName the name of the logHandler
 * @param outputStream the stream in which we write
 * @param logLevel the log level for this handler
 */
void addLogHandler(LogHandler* logHandler,
        char* handlerName,
        OutputStream* outputStream,
        LogLevel logLevel);

/**
 * Get a compatible outputStream (to be used with printWriter) in which we write.
 * @param writeLogLevel The log level which will be used to write the underlying log.
 * @return the compatible outputStream (to be used with printWriter) in which we write
 */
OutputStream* getOutputStreamLogger(LogLevel writeLogLevel);

/**
* Get an outputStream for log with DEBUG level.
* @return an outputStream for log with DEBUG level
*/
OutputStream* getDebugOutputStreamLogger();

/**
* Get an outputStream for log with ERROR level.
* @return an outputStream for log with ERROR level
*/
OutputStream* getErrorOutputStreamLogger();

/**
 * Returns the singleton for logger.
 */
Logger* getLoggerInstance();

#endif
