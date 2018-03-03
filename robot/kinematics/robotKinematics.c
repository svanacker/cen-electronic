#include "robotKinematics.h"

#include "../../common/math/cenMath.h"

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

float getLeftWheelPulseCountForOneMillimeter(RobotKinematics* robotKinematics) {
    return 1.0f / getLeftWheelLengthForOnePulse(robotKinematics);
}

float getRightWheelPulseCountForOneMillimeter(RobotKinematics* robotKinematics) {
    return 1.0f / getRightWheelLengthForOnePulse(robotKinematics);
}

float rotationInDeciDegreeToRealDistanceForLeftWheel(RobotKinematics* robotKinematics, float angleDeciDegree) {
    float angleRadius = angleDeciDegree * PI_DIVIDE_1800;
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);
    float result = -(wheelsDistanceFromCenter * angleRadius) / leftWheelLengthForOnePulse;
    
    return result;
}

float rotationInDeciDegreeToRealDistanceForRightWheel(RobotKinematics* robotKinematics, float angleDeciDegree) {
    float angleRadius = angleDeciDegree * PI_DIVIDE_1800;
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);
    float result = (wheelsDistanceFromCenter * angleRadius) / rightWheelLengthForOnePulse;
    
    return result;
}
