#ifndef LOGGER_DEBUG_H
#define LOGGER_DEBUG_H

#include "logger.h"
#include "logHandlerList.h"

#include "../../common/io/outputStream.h"


/**
 * Write the content of the log.
 * @param outputStream the outputStream in which we write the content of the log
 * @param logHandler the logHandler that we want to write
 */
void printLogHandler(OutputStream* outputStream,
        LogHandler* logHandler);

/**
 * Write the configuration of the logger.
 * @param outputStream the stream in which we write
 */
void printLogger(OutputStream* outputStream);


#endif
