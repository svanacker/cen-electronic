#include "logLevel.h"

char* getLevelAsString(LogLevel level) {
    switch (level) {
        case TRACE: return "TRACE(0)";
        case DEBUG: return "DBG(1)";
        case INFO: return "INF(2)";
        case WARNING: return "WARN(3)";
        case ERROR: return "ERR(4)";
        case ALWAYS: return "ALWAYS(5)";
    }
    return "?";
}
