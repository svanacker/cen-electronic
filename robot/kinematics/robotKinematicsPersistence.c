#include "robotKinematics.h"
#include "robotKinematicsPersistence.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/eepromAreas.h"
#include "../../common/error/error.h"

void loadRobotKinematicsParameters(RobotKinematics* robotKinematics, Eeprom* eeprom_, bool loadDefaultValues) {
    if (eeprom_ == NULL) {
        writeError(ROBOT_KINEMATICS_NO_EEPROM);
        return;
    }

    if (loadDefaultValues) {
        // Coder Value
        robotKinematics->coderWheelAverageDiameterMM = KINEMATICS_CODER_WHEEL_AVERAGE_DIAMETER_MM_DEFAULT_VALUE;
        robotKinematics->coderWheelAverageDeltaDiameterMM = KINEMATICS_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_MM_DEFAULT_VALUE;
        robotKinematics->coderWheelDistanceBetweenWheelsMM = KINEMATICS_CODER_WHEEL_DISTANCE_BETWEEN_WHEELS_MM_DEFAULT_VALUE;
        robotKinematics->coderWheelPulseByRotation = KINEMATICS_CODER_WHEEL_PULSE_BY_ROTATION_DEFAULT_VALUE;
        // Motor Value
        robotKinematics->motorWheelAverageDiameterMM = KINEMATICS_MOTOR_WHEEL_AVERAGE_DIAMETER_MM_DEFAULT_VALUE;
        robotKinematics->motorWheelDistanceBetweenWheelsMM = KINEMATICS_MOTOR_WHEEL_DISTANCE_BETWEEN_WHEELS_MM_DEFAULT_VALUE;
        robotKinematics->motorWheelRotationBySecondAtFullSpeed = KINEMATICS_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED_DEFAULT_VALUE;
        robotKinematics->motorMaxTorqueMilliNewton = KINEMATICS_MOTOR_MAX_TORQUE_MILLI_NEWTON_DEFAULT_VALUE;
        robotKinematics->motorReductorRatio = KINEMATICS_MOTOR_REDUCTOR_RATIO_DEFAULT_VALUE;
        // Robot Value
        robotKinematics->robotWeightGrams = KINEMATICS_ROBOT_WEIGHT_GRAMS;
    }
    else {
        bool eepromKinematicsAreaInitialized = isEepromAreaInitialized(eeprom_, EEPROM_KINETICS_AREA_MARKER_INDEX);
        if (!eepromKinematicsAreaInitialized) {
            writeError(ROBOT_KINEMATICS_EEPROM_NOT_INITIALIZED);
            return;
        }
        // CODER VALUES
        // We store a value * 10^3 (millimeter->nanometer)
        robotKinematics->coderWheelAverageDiameterMM = eepromReadUnsignedFloat(eeprom_, EEPROM_CODER_WHEEL_AVERAGE_DIAMETER_INDEX, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->coderWheelAverageDeltaDiameterMM = eepromReadUnsignedFloat(eeprom_, EEPROM_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_INDEX, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->coderWheelDistanceBetweenWheelsMM = eepromReadUnsignedFloat(eeprom_, EEPROM_CODER_WHEEL_DISTANCE_BETWEEN_WHEELS_INDEX, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->coderWheelPulseByRotation = eepromReadUnsignedFloat(eeprom_, EEPROM_CODER_WHEEL_PULSE_BY_ROTATION_INDEX, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        // MOTOR VALUES
        robotKinematics->motorWheelAverageDiameterMM = eepromReadUnsignedFloat(eeprom_, EEPROM_MOTOR_WHEEL_AVERAGE_DIAMETER_INDEX, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->motorWheelDistanceBetweenWheelsMM = eepromReadUnsignedFloat(eeprom_, EEPROM_MOTOR_WHEEL_DISTANCE_BETWEEN_WHEELS_INDEX, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->motorWheelRotationBySecondAtFullSpeed = eepromReadUnsignedFloat(eeprom_, EEPROM_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED_INDEX, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->motorMaxTorqueMilliNewton = eepromReadUnsignedFloat(eeprom_, EEPROM_MOTOR_MAX_TORQUE_MILLI_NEWTON_INDEX, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->motorReductorRatio = eepromReadUnsignedFloat(eeprom_, EEPROM_MOTOR_REDUCTOR_RATIO_INDEX, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        // ROBOT VALUES
        robotKinematics->robotWeightGrams = eepromReadUnsignedFloat(eeprom_, EEPROM_ROBOT_WEIGHT_GRAMS_INDEX, ROBOT_KINEMATICS_WEIGHT_DIGIT_PRECISION);
    }
}

void saveRobotKinematicsParameters(RobotKinematics* robotKinematics, Eeprom* eeprom_) {
    if (eeprom_ == NULL) {
        writeError(ROBOT_KINEMATICS_NO_EEPROM);
        return;
    }
    initEepromArea(eeprom_, EEPROM_KINETICS_AREA_MARKER_INDEX);
    // CODER VALUE
    eepromWriteUnsignedFloat(eeprom_, EEPROM_CODER_WHEEL_AVERAGE_DIAMETER_INDEX, robotKinematics->coderWheelAverageDiameterMM, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
    eepromWriteUnsignedFloat(eeprom_, EEPROM_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_INDEX, robotKinematics->coderWheelAverageDeltaDiameterMM, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
    eepromWriteUnsignedFloat(eeprom_, EEPROM_CODER_WHEEL_DISTANCE_BETWEEN_WHEELS_INDEX, robotKinematics->coderWheelDistanceBetweenWheelsMM, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
    eepromWriteUnsignedFloat(eeprom_, EEPROM_CODER_WHEEL_PULSE_BY_ROTATION_INDEX, robotKinematics->coderWheelPulseByRotation, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
    // MOTOR VALUE
    eepromWriteUnsignedFloat(eeprom_, EEPROM_MOTOR_WHEEL_AVERAGE_DIAMETER_INDEX, robotKinematics->motorWheelAverageDiameterMM, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
    eepromWriteUnsignedFloat(eeprom_, EEPROM_MOTOR_WHEEL_DISTANCE_BETWEEN_WHEELS_INDEX, robotKinematics->motorWheelDistanceBetweenWheelsMM, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
    eepromWriteUnsignedFloat(eeprom_, EEPROM_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED_INDEX, robotKinematics->motorWheelRotationBySecondAtFullSpeed, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
    eepromWriteUnsignedFloat(eeprom_, EEPROM_MOTOR_MAX_TORQUE_MILLI_NEWTON_INDEX, robotKinematics->motorMaxTorqueMilliNewton, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
    eepromWriteUnsignedFloat(eeprom_, EEPROM_MOTOR_REDUCTOR_RATIO_INDEX, robotKinematics->motorReductorRatio, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
    // ROBOT VALUE
    eepromWriteUnsignedFloat(eeprom_, EEPROM_ROBOT_WEIGHT_GRAMS_INDEX, robotKinematics->robotWeightGrams, ROBOT_KINEMATICS_WEIGHT_DIGIT_PRECISION);
}
