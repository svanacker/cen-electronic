#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

#include "../../common/io/outputStream.h"

// Define the type of LOG_LEVEL (to avoid to manipulate int and avoid type error)
enum LogLevel {
    /** the minimal log level, reserved for fine log. */
    LOG_LEVEL_TRACE = 0,
    
    /** debug level. */
    LOG_LEVEL_DEBUG = 1,
    
    /** default level. */
    LOG_LEVEL_INFO = 2,
    
    /** warning level. */
    LOG_LEVEL_WARNING = 3,
    
    /** Reserved for blocking error. */
    LOG_LEVEL_ERROR = 4,

    /** To ensure that it's always logged. */
    LOG_LEVEL_ALWAYS = 5
};

/**
 * Transforms a level into his string representation.
 * @param level the level in int value
 * @return the string representation of the level
 */
char* getLevelAsString(enum LogLevel level);

void appendLevelAsString(OutputStream* outputStream, enum LogLevel logLevel);

#endif
