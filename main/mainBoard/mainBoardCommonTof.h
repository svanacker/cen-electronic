#ifndef MAIN_BOARD_COMMON_TOF_H
#define MAIN_BOARD_COMMON_TOF_H

#include "mainBoardCommon.h"

#include "../../common/i2c/i2cBusList.h"

// -> IO EXPANDER
#include "../../drivers/ioExpander/ioExpanderList.h"

// MULTIPLEXER
#include "../../drivers/i2c/multiplexer/multiplexerList.h"

#include "../../robot/config/robotConfig.h"
#include "../../drivers/tof/tofList.h"

#include "../../robot/strategy/gameStrategyContext.h"

// TOFS
#define MAIN_BOARD_TOF_SENSOR_LIST_LENGTH                                     14
// I2C PORT 4
#define MAIN_BOARD_TOF_SENSOR_LIST_BUS_INDEX                                   0
#define MAIN_BOARD_MULTIPLEXER_BUS_INDEX    MAIN_BOARD_TOF_SENSOR_LIST_BUS_INDEX

// BEEP MANAGEMENT
// I2C PORT 1
#define MAIN_BOARD_TOF_BEEP_IO_EXPANDER_GROUND_PIN_INDEX                       6
#define MAIN_BOARD_TOF_BEEP_IO_EXPANDER_VCC_PIN_INDEX                          7

// TOF MANAGEMENT

#define FRONT_RIGHT_SENSOR_INDEX         0
#define FRONT_MIDDLE_SENSOR_INDEX        1
#define FRONT_LEFT_SENSOR_INDEX          2

#define BACK_RIGHT_SENSOR_INDEX          3
#define BACK_MIDDLE_SENSOR_INDEX         4
#define BACK_LEFT_SENSOR_INDEX           5

#define DISABLE_SENSOR_1_INDEX           6
#define DISABLE_SENSOR_2_INDEX           7

#define FRONT_SIDE_LEFT_SENSOR_INDEX     8
#define FRONT_SIDE_RIGHT_SENSOR_INDEX    9
#define BACK_SIDE_RIGHT_SENSOR_INDEX    10
#define BACK_SIDE_LEFT_SENSOR_INDEX     13

// LED MANAGEMENT
#define LED_ARRAY_INDEX_0                0
#define LED_ARRAY_INDEX_1                1

// THRESHOLD
#define STRATEGY_DETECTION_THRESHOLD     5

// ORIENTATION
#define BACK_RIGHT_SENSOR_ANGLE_DEGREE   -160.0f
#define BACK_MIDDLE_SENSOR_ANGLE_DEGREE  -180.0f
#define BACK_LEFT_SENSOR_ANGLE_DEGREE   -200.0f

#define FRONT_RIGHT_SENSOR_ANGLE_DEGREE   -20.0f
#define FRONT_MIDDLE_SENSOR_ANGLE_DEGREE  0.0f
#define FRONT_LEFT_SENSOR_ANGLE_DEGREE   20.0f

// SIDE : Orientation = 0.0f
#define FRONT_SIDE_LEFT_SENSOR_ANGLE_DEGREE     0.0f
#define FRONT_SIDE_RIGHT_SENSOR_ANGLE_DEGREE    0.0f
#define BACK_SIDE_LEFT_SENSOR_ANGLE_DEGREE      180.0f
#define BACK_SIDE_RIGHT_SENSOR_ANGLE_DEGREE     180.0f

// THRESHOLD
#define BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE      140
#define BACK_RIGHT_SENSOR_DISTANCE_THRESHOLD    300
#define BACK_MIDDLE_SENSOR_DISTANCE_THRESHOLD   400
#define BACK_LEFT_SENSOR_DISTANCE_THRESHOLD     300

#define FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE    100
#define FRONT_RIGHT_SENSOR_DISTANCE_THRESHOLD   300
#define FRONT_MIDDLE_SENSOR_DISTANCE_THRESHOLD  400
#define FRONT_LEFT_SENSOR_DISTANCE_THRESHOLD    300

#define FRONT_SIDE_TOF_TO_FRONT_OF_ROBOT_DISTANCE    0
#define FRONT_SIDE_TOF_TO_BACK_OF_ROBOT_DISTANCE     100
#define FRONT_SIDE_LEFT_SENSOR_DISTANCE_THRESHOLD    200
#define FRONT_SIDE_RIGHT_SENSOR_DISTANCE_THRESHOLD   200
#define BACK_SIDE_LEFT_SENSOR_DISTANCE_THRESHOLD     130
#define BACK_SIDE_RIGHT_SENSOR_DISTANCE_THRESHOLD    130

/**
 * Main Part of MAIN_BOARD for Tof initialization (Driver).
 * Useful when we just want to initialize 2 tof like for Experience 2019 Main
 * Program.
 */
TofSensorList* mainBoardCommonTofInitDrivers(RobotConfig* robotConfig, MultiplexerList* multiplexerList);

/**
 * Function used to update the threshold of the Tof regarding the speed of the robot.
 */
void mainBoardCommonUpdateTofMaxDistanceMM(GameStrategyContext* gameStrategyContext, float marginDistanceMM, float maxDistanceMM);

/**
 * Returns the list of Tof Sensor.
 */
TofSensorList* mainBoardCommonTofGetTofSensorList(void);

#endif
