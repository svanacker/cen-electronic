#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

/**
 * the minimal log level, reserved for fine log.
 */
#define TRACE 	0
/**
 * debug level.
 */
#define DEBUG 	1
/**
 * default level.
 */
#define INFO 	2
/**
 * warning level.
 */
#define WARNING 3
/**
 * Reserved for blocking error.
 */
#define ERROR 	4

/**
 * To ensure that it's always logged
 */
#define ALWAYS 	5

/**
 * Transforms a level into his string representation.
 * @param level the level in int value
 * @return the string representation of the level
 */
char* getLevelAsString(int level);

#endif
