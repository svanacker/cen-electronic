#ifndef STRATEGY_TOF_SENSOR_LIST_H
#define STRATEGY_TOF_SENSOR_LIST_H

#include "../../drivers/tof/tofList.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/match/startMatch.h"
#include "../../robot/strategy/gameStrategyContext.h"

// TOF MANAGEMENT
#define BACK_RIGHT_SENSOR_INDEX          0
#define BACK_MIDDLE_SENSOR_INDEX         1
#define BACK_LEFT_SENSOR_INDEX           2

#define FRONT_RIGHT_SENSOR_INDEX         3
#define FRONT_MIDDLE_SENSOR_INDEX        4
#define FRONT_LEFT_SENSOR_INDEX          5

// ORIENTATION
#define BACK_RIGHT_SENSOR_ANGLE_DEGREE   -160.0f
#define BACK_MIDDLE_SENSOR_ANGLE_DEGREE  -180.0f
#define BACK_LEFT_SENSOR_ANGLE_DEGREE   -200.0f

#define FRONT_RIGHT_SENSOR_ANGLE_DEGREE   -20.0f
#define FRONT_MIDDLE_SENSOR_ANGLE_DEGREE  0.0f
#define FRONT_LEFT_SENSOR_ANGLE_DEGREE   20.0f

// THRESHOLD
#define BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE      150
#define BACK_RIGHT_SENSOR_DISTANCE_THRESHOLD    300
#define BACK_MIDDLE_SENSOR_DISTANCE_THRESHOLD   400
#define BACK_LEFT_SENSOR_DISTANCE_THRESHOLD     300

#define FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE    100
#define FRONT_RIGHT_SENSOR_DISTANCE_THRESHOLD   300
#define FRONT_MIDDLE_SENSOR_DISTANCE_THRESHOLD  400
#define FRONT_LEFT_SENSOR_DISTANCE_THRESHOLD    300

// MIN TRESHOLD : Do not detect too close of TOF (physically impossible because 
// TOF are at the center of the robot !)
#define SENSOR_DISTANCE_MIN_TRESHOLD            100

/**
 * INIT
 * @param tofSensorList
 * @param distanceFactor
 */
void setTofListOrientationAngle(TofSensorList* tofSensorList, float distanceFactor);

/**
 * TOF MANAGEMENT
 * @param gameStrategyContext
 */
void handleTofSensorList(GameStrategyContext* gameStrategyContext, StartMatch* startMatch, TofSensorList* tofSensorList, GameBoard* gameBoard);

#endif
