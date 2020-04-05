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
void writeLogChar(OutputStream* outputStream, unsigned char c) {
    // if the write Log Level is not enough grave to be logged in the global configuration
    if (logger.writeLogLevel < logger.globalLogLevel) {
        return;
    }
    int i;
    int count = getLogHandlerCount(&logHandlerList);
    int writeLoggerLevel = logger.writeLogLevel;
    for (i = 0; i < count; i++) {
        LogHandler* logHandler = getLogHandler(&logHandlerList, i);
        enum LogLevel logHandlerLevel = logHandler->logLevel;
        // we only write data which are with higher level
        if (logHandlerLevel != LOG_LEVEL_ALWAYS && writeLoggerLevel < logHandlerLevel) {
            continue;
        }
        // To exclude logger which does not correspond to the category
        if ((logHandler->logCategoryMask & logger.logCategoryMask) == 0) {
            continue;
        }
        OutputStream* logHandlerOutputStream = logHandler->outputStream;
        // write the char of the corresponding stream of the handler
        logHandlerOutputStream->writeChar(logHandlerOutputStream, c);
    }
}

void initLogs(enum LogLevel globalLogLevel, LogHandler(*handlerListArray)[], unsigned char handlerListSize, unsigned long defaultLogCategoryMask) {
    // Init logger structure
    logger.globalLogLevel = globalLogLevel;
    logger.writeLogLevel = globalLogLevel;
    logger.defaultLogCategoryMask = defaultLogCategoryMask;
    logger.logCategoryMask = defaultLogCategoryMask;
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
        enum LogLevel logLevel,
        unsigned long logCategoryMask) {
    LogHandler* result = addLogHandlerToList(&logHandlerList, logLevel, logCategoryMask, handlerName, outputStream);

    return result;
}

OutputStream* getOutputStreamLogger(enum LogLevel writeLogLevel, unsigned long logCategoryMask) {
    logger.writeLogLevel = writeLogLevel;
    logger.logCategoryMask = logCategoryMask;
    return logger.outputStream;
}

OutputStream* getTraceOutputStreamLogger() {
    logger.writeLogLevel = LOG_LEVEL_TRACE;
    logger.logCategoryMask = logger.defaultLogCategoryMask;
    return logger.outputStream;
}

OutputStream* getDebugOutputStreamLogger() {
    logger.writeLogLevel = LOG_LEVEL_DEBUG;
    logger.logCategoryMask = logger.defaultLogCategoryMask;
    return logger.outputStream;
}

OutputStream* getInfoOutputStreamLogger() {
    logger.writeLogLevel = LOG_LEVEL_INFO;
    logger.logCategoryMask = logger.defaultLogCategoryMask;
    return logger.outputStream;
}

OutputStream* getWarningOutputStreamLogger() {
    logger.writeLogLevel = LOG_LEVEL_WARNING;
    logger.logCategoryMask = logger.defaultLogCategoryMask;
    return logger.outputStream;
}

OutputStream* getErrorOutputStreamLogger() {
    logger.writeLogLevel = LOG_LEVEL_ERROR;
    logger.logCategoryMask = logger.defaultLogCategoryMask;
    return logger.outputStream;
}

OutputStream* getAlwaysOutputStreamLogger() {
    logger.writeLogLevel = LOG_LEVEL_ALWAYS;
    logger.logCategoryMask = logger.defaultLogCategoryMask;
    return logger.outputStream;
}

// Convenient method to avoid to consume time for logging when not enabled

bool isLoggerTraceEnabled(void) {
    return logger.globalLogLevel <= LOG_LEVEL_TRACE;
}

bool isLoggerDebugEnabled(void) {
    return logger.globalLogLevel <= LOG_LEVEL_DEBUG;
}

bool isLoggerInfoEnabled(void) {
    return logger.globalLogLevel <= LOG_LEVEL_INFO;
}

bool isLoggerWarningEnabled(void) {
    return logger.globalLogLevel <= LOG_LEVEL_WARNING;
}

bool isLoggerErrorEnabled(void) {
    return logger.globalLogLevel <= LOG_LEVEL_ERROR;
}

bool isLoggerAlwaysEnabled(void) {
    return logger.globalLogLevel <= LOG_LEVEL_ALWAYS;
}

Logger* getLoggerInstance() {
    return &logger;
}
