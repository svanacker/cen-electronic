#include "robotKinematics.h"

#include <stdbool.h>
#include <stdlib.h>


// Singleton
static RobotKinematics robotKinematicsInstance;

RobotKinematics* getRobotKinematics(void) {
    return &robotKinematicsInstance;
}


float getLeftWheelLengthForOnePulse(RobotKinematics* robotKinematics) {
    return (robotKinematics->wheelAverageLengthForOnePulse + robotKinematics->wheelDeltaLengthForOnePulse);
}

float getRightWheelLengthForOnePulse(RobotKinematics* robotKinematics) {
    return (robotKinematics->wheelAverageLengthForOnePulse - robotKinematics->wheelDeltaLengthForOnePulse);
}

float getWheelPulseBySecondsAtFullSpeed(RobotKinematics* robotKinematics) {
    return (robotKinematics->wheelRotationBySecondsAtFullSpeed * robotKinematics->pulseByRotation);
}
 
float getWheelsDistanceFromCenter(RobotKinematics* robotKinematics) {
    return robotKinematics->wheelsDistance / 2.0f;
}
