#include "logger.h"
#include "logHandlerList.h"
#include "logHandler.h"

/** Singleton, used for instantiate memory necessary for struct */
static Logger logger;
static LogHandlerList logHandlerList;
static OutputStream logOutputStream;

LogHandlerList* getLoggerHandlerList() {
    return &logHandlerList;
}

/**
* @private
*/
void flushLog(OutputStream* outputStream) {
	// don't do anything for the moment
}

/**
 * @private
 */
void writeLogChar(OutputStream* outputStream, char c) {
    // if the write Log Level is not enough grave to be logged in the global configuration
    if (logger.writeLogLevel < logger.globalLogLevel) {
        return;
    }
    int i;
    int count = getLogHandlerCount(&logHandlerList);
    int writeLoggerLevel = logger.writeLogLevel;
    for (i = 0; i < count; i++) {
        LogHandler* logHandler = getLogHandler(&logHandlerList, i);
        LogLevel logHandlerLevel = logHandler->logLevel;
        // we only write data which are with higher level
        if (writeLoggerLevel < logHandlerLevel) {
            continue;
        }
        OutputStream* outputStream = logHandler->outputStream;
        // write the char of the corresponding stream of the handler
        outputStream->writeChar(outputStream, c);
    }
}

void initLogs(LogLevel globalLogLevel, LogHandler(*handlerListArray)[], unsigned char handlerListSize) {
	// Init logger structure
	logger.globalLogLevel = globalLogLevel;
	logger.writeLogLevel = globalLogLevel;
	logger.logHandlerList = &logHandlerList;
	logger.outputStream = &logOutputStream;
	// Init OutputStream
	logOutputStream.writeChar = writeLogChar;
	logOutputStream.flush = flushLog;
	// Init the LogHandlerList
	initLogHandlerList(&logHandlerList, handlerListArray, handlerListSize);
}

LogHandler* addLogHandler(char* handlerName,
                            OutputStream* outputStream,
                            LogLevel logLevel) {
    LogHandler* result = addLogHandlerToList(&logHandlerList, logLevel, handlerName, outputStream);

    return result;
}

OutputStream* getOutputStreamLogger(LogLevel writeLogLevel) {
    logger.writeLogLevel = writeLogLevel;
    return logger.outputStream;
}

OutputStream* getDebugOutputStreamLogger() {
    logger.writeLogLevel = DEBUG;
    return logger.outputStream;
}

OutputStream* getErrorOutputStreamLogger() {
    logger.writeLogLevel = LOG_LEVEL_ERROR;
    return logger.outputStream;
}

Logger* getLoggerInstance() {
    return &logger;
}
