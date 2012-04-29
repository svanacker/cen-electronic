#ifndef MOTOR_CLIENT_H
#define MOTOR_CLIENT_H

/**
 * Defines the non ambiguous command that PIC is ready.
* It's very important because PIC can send false serial data during initialization, and the pc must not handle them untile
* this notification is received by the pc.
 */
#define ROBOT_STARTED_NOTIFICATION "xXyY"

/**
* Notify the pc that the robot is ready.
*/
void notifyReady( void );

/**
* Notify the pc that the program has end. No more instruction will be handled.
*/
void notifyEnd ( void );

/**
* Send to the PC an information to indicates that position was not reached due to blocking.
*/
void notifyBlocked( void );

/**
* Send to the PC an information to indicates that position is reached.
*/
void notifyReached( void );

/**
* Notify that there is an obstacle in front of the robot
*/
void notifyObstacle( void );

/**
* Notify that the match started.
*/
void notifyMatchStarted( void );

/**
* Notify that we end the corn sequence.
*/
void notifyCornSequenceEnd();

/**
* Defines the function which must do polling
* over RS232 to know which instruction must be executed.
*/
void loadNextInstruction ( void );

/**
* Returns 0 if debug is disabled, 1 if debug is enabled.
*/
int getDebug( void );

#endif
