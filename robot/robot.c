#include "robot.h"
#include "robotType.h"

static enum RobotType robotType;

void setRobotType(enum RobotType robotTypeParam) {
    robotType = robotTypeParam;
}

enum RobotType getRobotType(void) {
    return robotType;
}