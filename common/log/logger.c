#include "logger.h"

/** Singleton, used for instanciate memory necessary for struct */
static Logger logger;
static LogHandlerList logHandlerList;
static OutputStream logOutputStream;

LogHandlerList* getLoggerHandlerList() {
    return &logHandlerList;
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
        LogHandler* logHandler = logHandlerList.logHandlers[i];
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

/**
 * @private
 */
void flushLog(OutputStream* outputStream) {
    // don't do anything for the moment
}

void initLog(LogLevel globalLogLevel) {
    // Init logger structure
    logger.globalLogLevel = globalLogLevel;
    logger.writeLogLevel = globalLogLevel;
    logger.logHandlerList = &logHandlerList;
    logger.outputStream = &logOutputStream;
    // Init OutputStream
    logOutputStream.writeChar = writeLogChar;
    logOutputStream.flush = flushLog;
}

void addLogHandler(LogHandler* logHandler,
        char* handlerName,
        OutputStream* outputStream,
        LogLevel logLevel) {
    initHandler(logHandler, handlerName, outputStream, logLevel);
    addLogHandlerToList(&logHandlerList, logHandler);
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
