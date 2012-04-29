#ifndef COMMON_COMMAND_H
#define COMMON_COMMAND_H

/**
 * Defines the common commands which must be used in any program
 * to have a consistency between all commands
 */
#define COMMAND_ACK 'a'

/**
 * Command to cancel any instruction in progress.
 */
#define CANCEL_COMMAND 'z'

/**
 * Command to reset the micro-controller.
 */
#define RESET_COMMAND 'r'

/**
 * Command to shutdown all devices.
 */
#define SHUTDOWN 'S'

/**
 * Defines the separator used to split each arguments
 * (useful when using arguments of 4 or 8 Hexadecimal char).
 */
#define ARGUMENT_SEPARATOR '-';


#endif
