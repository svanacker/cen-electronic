#include "robotKinematics.h"

#include "../../common/math/cenMath.h"

#include <stdbool.h>
#include <stdlib.h>


// Singleton
static RobotKinematics robotKinematicsInstance;

RobotKinematics* getRobotKinematics(void) {
    return &robotKinematicsInstance;
}

// WHEEL CODER VALUES

float getCoderWheelAverageDiameterMM(RobotKinematics* robotKinematics) {
    return robotKinematics->coderWheelAverageDiameterMM;
}

void setCoderWheelAverageDiameterMM(RobotKinematics* robotKinematics, float value) {
    robotKinematics->coderWheelAverageDiameterMM = value;
}

float getCoderWheelAverageDeltaDiameterMM(RobotKinematics* robotKinematics) {
    return robotKinematics->coderWheelAverageDeltaDiameterMM;
}

void setCoderWheelAverageDeltaDiameterMM(RobotKinematics* robotKinematics, float value) {
    robotKinematics->coderWheelAverageDeltaDiameterMM = value;
}

float getCoderWheelDistanceBetweenWheelsMM(RobotKinematics* robotKinematics) {
    return robotKinematics->coderWheelDistanceBetweenWheelsMM;
}

void setCoderWheelDistanceBetweenWheelsMM(RobotKinematics* robotKinematics, float value) {
    robotKinematics->coderWheelDistanceBetweenWheelsMM = value;
}

float getCoderWheelPulseByRotation(RobotKinematics* robotKinematics) {
    return robotKinematics->coderWheelPulseByRotation;
}

void setCoderWheelPulseByRotation(RobotKinematics* robotKinematics, float value) {
    robotKinematics->coderWheelPulseByRotation = value;
}

// MOTOR WHEEL VALUES

float getMotorWheelAverageDiameterMM(RobotKinematics* robotKinematics) {
    return robotKinematics->motorWheelAverageDiameterMM;
}

void setMotorWheelAverageDiameterMM(RobotKinematics* robotKinematics, float value) {
    robotKinematics->motorWheelAverageDiameterMM = value;
}

float getMotorWheelDistanceBetweenWheelsMM(RobotKinematics* robotKinematics) {
    return robotKinematics->motorWheelDistanceBetweenWheelsMM;
}

void setMotorWheelDistanceBetweenWheelsMM(RobotKinematics* robotKinematics, float value) {
    robotKinematics->motorWheelDistanceBetweenWheelsMM = value;
}

float getMotorWheelRotationBySecondAtFullSpeed(RobotKinematics* robotKinematics) {
    return robotKinematics->motorWheelRotationBySecondAtFullSpeed;
}

void setMotorWheelRotationBySecondAtFullSpeed(RobotKinematics* robotKinematics, float value) {
    robotKinematics->motorWheelRotationBySecondAtFullSpeed = value;
}

// COMPUTED VALUES

float getCoderLeftWheelDiameter(RobotKinematics* robotKinematics) {
    return robotKinematics->coderWheelAverageDiameterMM + robotKinematics->coderWheelAverageDeltaDiameterMM;
}

float getCoderRightWheelDiameter(RobotKinematics* robotKinematics) {
    return robotKinematics->coderWheelAverageDiameterMM - robotKinematics->coderWheelAverageDeltaDiameterMM;
}

float getCoderWheelsDistanceFromCenter(RobotKinematics* robotKinematics) {
    return robotKinematics->coderWheelDistanceBetweenWheelsMM / 2.0f;
}

// DIFFERENT LENGTH FOR ONE PULSE (left, right, average)

float getCoderLeftWheelLengthForOnePulse(RobotKinematics* robotKinematics) {
    return (getCoderLeftWheelDiameter(robotKinematics) * PI) / robotKinematics->coderWheelPulseByRotation;
}

float getCoderRightWheelLengthForOnePulse(RobotKinematics* robotKinematics) {
    return (getCoderRightWheelDiameter(robotKinematics) * PI) / robotKinematics->coderWheelPulseByRotation;
}

float getCoderAverageWheelLengthForOnePulse(RobotKinematics* robotKinematics) {
    return (getCoderWheelAverageDiameterMM(robotKinematics) * PI) / robotKinematics->coderWheelPulseByRotation;
}

// COMPUTE INVOLVING MOTOR AND CODERS

float getCoderWheelAndMotorWheelAverageDiameterFactor(RobotKinematics* robotKinematics) {
    return robotKinematics->coderWheelAverageDiameterMM / robotKinematics->motorWheelAverageDiameterMM;
}

float getCoderWheelPulseBySecondsAtFullSpeed(RobotKinematics* robotKinematics, bool rotationMode) {
    float coderMotorWheelsFactor = getCoderWheelAndMotorWheelAverageDiameterFactor(robotKinematics);
    // coder rotation are depending on the rotation of motor, but by integrating the motor / coder diameter factor
    float coderRotationBySecond = (robotKinematics->motorWheelRotationBySecondAtFullSpeed / coderMotorWheelsFactor);
    if (rotationMode) {
        // In this case, when we rotate, if motor distance is less than coder distance,
        // there will be more pulse at coder than if coder & motor was at the same distance
        coderRotationBySecond *= robotKinematics->coderWheelDistanceBetweenWheelsMM / robotKinematics->motorWheelDistanceBetweenWheelsMM;
    }
    // We multiply by the amount of pulse by rotation
    float result = robotKinematics->coderWheelPulseByRotation * coderRotationBySecond;
    return result;
}

float rotationInDeciDegreeToRealDistanceForLeftWheel(RobotKinematics* robotKinematics, float angleDeciDegree) {
    float angleRadius = angleDeciDegree * PI_DIVIDE_1800;
    float leftWheelLengthForOnePulse = getCoderLeftWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getCoderWheelsDistanceFromCenter(robotKinematics);
    float result = -(wheelsDistanceFromCenter * angleRadius) / leftWheelLengthForOnePulse;
    
    return result;
}

float rotationInDeciDegreeToRealDistanceForRightWheel(RobotKinematics* robotKinematics, float angleDeciDegree) {
    float angleRadius = angleDeciDegree * PI_DIVIDE_1800;
    float rightWheelLengthForOnePulse = getCoderRightWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getCoderWheelsDistanceFromCenter(robotKinematics);
    float result = (wheelsDistanceFromCenter * angleRadius) / rightWheelLengthForOnePulse;
    
    return result;
}
