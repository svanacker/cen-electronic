#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>

#include "../common/commons.h"
#include "../common/io/outputStream.h"

#include "robotType.h"

/**
 * Define the Structure which stores RobotPosition.
 */
typedef struct RobotPosition {
    // x in millimeter
    float x;
    // y in millimeter
    float y;
    // orientation Angle
    float angleRadian;
} RobotPosition;

void setRobotType(enum RobotType robotType);

enum RobotType getRobotType();


#endif
