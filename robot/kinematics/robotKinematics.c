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

float getMotorMaxTorqueMilliNewton(RobotKinematics* robotKinematics) {
    return robotKinematics->motorMaxTorqueMilliNewton;
}

void setMotorMaxTorqueMilliNewton(RobotKinematics* robotKinematics, float value) {
    robotKinematics->motorMaxTorqueMilliNewton = value;
}

float getMotorReductorRatio(RobotKinematics* robotKinematics) {
    return robotKinematics->motorReductorRatio;
}

void setMotorReductorRatio(RobotKinematics* robotKinematics, float value) {
    robotKinematics->motorReductorRatio = value;
}

// ROBOT VALUES

float getRobotSpeedMaxMillimeterBySecond(RobotKinematics* robotKinematics) {
    return robotKinematics->motorWheelRotationBySecondAtFullSpeed * robotKinematics->motorWheelAverageDiameterMM * PI;
}

float getRobotWeightGrams(RobotKinematics* robotKinematics) {
    return robotKinematics->robotWeightGrams;
}

void setRobotWeightGrams(RobotKinematics* robotKinematics, float value) {
    robotKinematics->robotWeightGrams = value;
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

float getCoderLeftWheelFactor(RobotKinematics* robotKinematics) {
    return 1.0f + robotKinematics->coderWheelAverageDeltaDiameterMM / robotKinematics->coderWheelAverageDiameterMM;
}

float getCoderRightWheelFactor(RobotKinematics* robotKinematics) {
    return 1.0f - robotKinematics->coderWheelAverageDeltaDiameterMM / robotKinematics->coderWheelAverageDiameterMM;
}

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

float getCoderWheelDistanceMMBySecondsAtFullSpeed(RobotKinematics* robotKinematics, bool rotationMode) {
    float result = getCoderWheelPulseBySecondsAtFullSpeed(robotKinematics, rotationMode);
    result *= getCoderAverageWheelLengthForOnePulse(robotKinematics);
    return result;
}

// -> Rotation in Radians

float rotationInRadiansToRealDistanceForLeftWheel(RobotKinematics* robotKinematics, float angleRadius) {
    float wheelsDistanceFromCenter = getCoderWheelsDistanceFromCenter(robotKinematics);
    float factor = getCoderLeftWheelFactor(robotKinematics);
    float result = -(wheelsDistanceFromCenter * angleRadius) * factor;
    
    return result;
}

float rotationInRadiansToRealDistanceForRightWheel(RobotKinematics* robotKinematics, float angleRadius) {
    float wheelsDistanceFromCenter = getCoderWheelsDistanceFromCenter(robotKinematics);
    float factor = getCoderRightWheelFactor(robotKinematics);
    float result = (wheelsDistanceFromCenter * angleRadius) * factor;

    return result;
}

// -> Rotation in Degrees

float rotationInDegreeToRealDistanceForLeftWheel(RobotKinematics* robotKinematics, float angleDegree) {
    float angleRadius = degToRad(angleDegree);
    return rotationInRadiansToRealDistanceForLeftWheel(robotKinematics, angleRadius);
}

float rotationInDegreeToRealDistanceForRightWheel(RobotKinematics* robotKinematics, float angleDegree) {
    float angleRadius = degToRad(angleDegree);
    return rotationInRadiansToRealDistanceForRightWheel(robotKinematics, angleRadius);
}

// ROBOT PART

float getRobotAccelerationMaxMillimeterBySecondSquare(RobotKinematics* robotKinematics) {
    // * Acceleration = Force / Weight
    // * Force = Torque / Radius
    // Torque = MotorTorque * motorReductorRadio
    // * Radius = Diameter / 2
    // 2*  Motors which provider power
    // => Robot Acceleration = (Motor Torque * motorReductorRadio / Motor Diameter) / Weight

    float result = (robotKinematics->motorMaxTorqueMilliNewton * 0.001f); // Torque in Newton Meter
    result *= robotKinematics->motorReductorRatio;
    result /= (robotKinematics->motorWheelAverageDiameterMM * 0.001f); // Diameter in Meter
    result /= (robotKinematics->robotWeightGrams * 0.001f);            // Weight in kg
    result *= 1000.0f;                                                 // In Millimeter
    return result;
}
