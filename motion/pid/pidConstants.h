#ifndef PID_CONSTANTS_H
#define PID_CONSTANTS_H

#include "instructionType.h"
#include "pidType.h"

// PID CONSTANT

/** How many Item of PID Computation Values we store */
#define PID_HISTORY_ITEM_COUNT                                              1000


// -> TEST MODE (to test with a rolling board instead of real motion)

#define TEST_MODE_COUNT 2

/** we use test mode */
#define ROLLING_BOARD_TEST_MODE_OFF        false

/** We use the pid at the adress for test mode. */
#define ROLLING_BOARD_TEST_MODE_ON        true


/**
 * Limit value to next PID value.
 */
#define PID_NEXT_VALUE_LIMIT 1000.0f

/**
 * Constant to have good PID range.
 */
#define PID_GLOBAL_DIVISER 500.0f

/** 
 The factor which defines by which factor we divide the expected acceleration.
 The real acceleration has for unit : coder count / time_sample^2
 If we want to convert to m / s-2, we use the following formula :

 a = (a_coder_count / count_by_meter) / (time_sample^2)
 Ex : 
  a_coder_count = 10, count_by_meter = 10000, time_sample = 0.005 (200 Hz)
  (10 / 10000) / 0.005Hz = 40 m s-2 which is too much
 If we increase this factor, we must enhanced the acceleration value to have the same acceleration
 */
#define A_FACTOR 0.3f

/**
 * The factor for improving speed.
 */
#define SPEED_FACTOR 20.0f

/**
 * Defines the error for which we apply strong PID and not normal PID.
 */
// TODO : Use a parameter in Eeprom
#define ERROR_FOR_STRONG_PID                     20

/**
 * Defines the number of pid interrupt after the end (t3) to apply strong PID.
 */
// TODO : Use a parameter in Eeprom
#define TIME_PERIOD_AFTER_END_FOR_STRONG_PID     40

/** The total number of PID values (INSTRUCTION_TYPE_COUNT * PID_TYPE_COUNT). */
#define PID_COUNT (INSTRUCTION_TYPE_COUNT * PID_TYPE_COUNT)

#endif