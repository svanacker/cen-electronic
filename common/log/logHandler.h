#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H

#include "../../common/log/logLevel.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/**
 * Defines a structure to wrap a handler around outputStream.
 */
typedef struct {
    /** A level corresponding to logLevel. */
    LogLevel logLevel;
	/** A mask to enable to log only if it corresponds to a certain category. */
	unsigned long logCategoryMask;
    /** name of handler. */
    char* handlerName;
    /** The underlying outputStream. */
    OutputStream* outputStream;
} LogHandler;

#define LOG_HANDLER_CATEGORY_ALL_MASK	0xFFFFFFFF

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
        LogLevel logLevel,
		unsigned long logCategoryMask);

#endif
