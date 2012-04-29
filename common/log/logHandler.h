#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/**
 * Defines a structure to wrap a handler arround outputStream.
 */
typedef struct {
    /** A level corresponding to logLevel. */
    unsigned int logLevel;
    /** name of handler. */
    char* handlerName;
    /** The underlying outputStream. */
    OutputStream* outputStream;
} LogHandler;

/**
 * Init a logHandler.
 * @param logHandler the struct to initialize
 * @param handlerName the name of the handler
 * @param outputStream the outputStream used to write log
 * @param logLevel the level of the logHandler
 */
void initHandler(
        LogHandler* logHandler,
        char* handlerName,
        OutputStream* outputStream,
        unsigned int logLevel);

/**
 * Write the content of the log.
 * @param outputStream the outputStream in which we write the content of the log
 * @param logHandler the logHandler that we want to write
 */
void printLogHandler(OutputStream* outputStream,
        LogHandler* logHandler);

#endif

