#ifndef TIMER_CONSTANTS_H
#define TIMER_CONSTANTS_H

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

// Timer Index for Robot infrared
#define ROBOT_INFRARED_DETECTOR_TIMER_CODE             15

/**
* Defines the index for the timer which detects end of the match.
*/
#define END_MATCH_DETECTOR_TIMER_CODE                  20

#define TIMER_SOFT_CLOCK_CODE                          96

#define ROBOT_SONAR_DETECTOR_TIMER_CODE               123

#define DEMO_TIMER_CODE                               124

#endif
