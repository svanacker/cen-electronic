#include "logLevel.h"

char* getLevelAsString(enum LogLevel level) {
    switch (level) {
        case LOG_LEVEL_TRACE: return "TRACE(0)";
        case LOG_LEVEL_DEBUG: return "DEBUG(1)";
        case LOG_LEVEL_INFO: return "INFO(2)";
        case LOG_LEVEL_WARNING: return "WARNING(3)";
        case LOG_LEVEL_ERROR: return "ERROR(4)";
        case LOG_LEVEL_ALWAYS: return "ALWAYS(5)";
    }
    return "?";
}
