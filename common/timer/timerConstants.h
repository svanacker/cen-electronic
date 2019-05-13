#ifndef TIMER_CONSTANTS_H
#define TIMER_CONSTANTS_H

/**
 * Define a "functional" code of the timer (we do not list the index in 
 * the timer list which could vary a lot by adding or removing timer.
 */

/** The code of timer used for coders. */
#define CODERS_TIMER_CODE                              1

/** The code of the timer used for delay based on clock. */
#define SYSTEM_TIMER_DELAY_CODE                        2

/**
* Defines the index for the timer to check if robot has detect something.
*/
#define ROBOT_OBSTACLE_TIMER_CODE                      3

/** The code of the timer (used to update value of servo). */
#define SERVO_TIMER_CODE                               10

/**
 * Defines the timer used by the strategy to continously get the robot
 * position
 */
#define TIMER_STRATEGY_MOTION_HANDLER_UPDATE_ROBOT_POSITION           15

/**
* Defines the index for the timer which detects end of the match.
*/
#define END_MATCH_DETECTOR_TIMER_CODE                  20

#define TIMER_SOFT_CLOCK_CODE                          96

// 2019 Specific

#define ELECTRON_LAUNCHER_2019_TIMER_CODE              99

// DEMO
#define DEMO_TIMER_CODE                               124

#endif
