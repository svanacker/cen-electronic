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
        robotKinematics->coderWheelAverageDiameterMM = (float) eepromReadLong(eeprom_, EEPROM_CODER_WHEEL_AVERAGE_DIAMETER_INDEX) / MILLI_TO_MICRO_FACTOR;
        robotKinematics->coderWheelAverageDeltaDiameterMM = (float) eepromReadLong(eeprom_, EEPROM_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_INDEX) / MILLI_TO_MICRO_FACTOR;
        robotKinematics->coderWheelDistanceBetweenWheelsMM = (float) eepromReadLong(eeprom_, EEPROM_CODER_WHEEL_DISTANCE_BETWEEN_WHEELS_INDEX) / MILLI_TO_MICRO_FACTOR;
        robotKinematics->coderWheelPulseByRotation = (float) eepromReadLong(eeprom_, EEPROM_CODER_WHEEL_PULSE_BY_ROTATION_INDEX);
        // MOTOR VALUES
        robotKinematics->motorWheelAverageDiameterMM = (float) eepromReadLong(eeprom_, EEPROM_MOTOR_WHEEL_AVERAGE_DIAMETER_INDEX) / MILLI_TO_MICRO_FACTOR;
        robotKinematics->motorWheelDistanceBetweenWheelsMM = (float)eepromReadLong(eeprom_, EEPROM_MOTOR_WHEEL_DISTANCE_BETWEEN_WHEELS_INDEX) / MILLI_TO_MICRO_FACTOR;
        robotKinematics->motorWheelRotationBySecondAtFullSpeed = (float)eepromReadLong(eeprom_, EEPROM_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED_INDEX);
        robotKinematics->motorMaxTorqueMilliNewton = (float)eepromReadLong(eeprom_, EEPROM_MOTOR_MAX_TORQUE_MILLI_NEWTON_INDEX);
        robotKinematics->motorReductorRatio = (float)eepromReadLong(eeprom_, EEPROM_MOTOR_REDUCTOR_RATIO_INDEX);
        // ROBOT VALUES
        robotKinematics->robotWeightGrams = (float)eepromReadLong(eeprom_, EEPROM_ROBOT_WEIGHT_GRAMS_INDEX);
    }
}

void saveRobotKinematicsParameters(RobotKinematics* robotKinematics, Eeprom* eeprom_) {
    if (eeprom_ == NULL) {
        writeError(ROBOT_KINEMATICS_NO_EEPROM);
        return;
    }
    initEepromArea(eeprom_, EEPROM_KINETICS_AREA_MARKER_INDEX);
    // CODER VALUE
    eepromWriteLong(eeprom_, EEPROM_CODER_WHEEL_AVERAGE_DIAMETER_INDEX, (long) (robotKinematics->coderWheelAverageDiameterMM * MILLI_TO_MICRO_FACTOR));
    eepromWriteLong(eeprom_, EEPROM_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_INDEX, (long) (robotKinematics->coderWheelAverageDeltaDiameterMM * MILLI_TO_MICRO_FACTOR));
    eepromWriteLong(eeprom_, EEPROM_CODER_WHEEL_DISTANCE_BETWEEN_WHEELS_INDEX, (long) (robotKinematics->coderWheelDistanceBetweenWheelsMM * MILLI_TO_MICRO_FACTOR));
    eepromWriteLong(eeprom_, EEPROM_CODER_WHEEL_PULSE_BY_ROTATION_INDEX, (long) (robotKinematics->coderWheelPulseByRotation));
    // MOTOR VALUE
    eepromWriteLong(eeprom_, EEPROM_MOTOR_WHEEL_AVERAGE_DIAMETER_INDEX, (long) (robotKinematics->motorWheelAverageDiameterMM * MILLI_TO_MICRO_FACTOR));
    eepromWriteLong(eeprom_, EEPROM_MOTOR_WHEEL_DISTANCE_BETWEEN_WHEELS_INDEX, (long)(robotKinematics->motorWheelDistanceBetweenWheelsMM * MILLI_TO_MICRO_FACTOR));
    eepromWriteLong(eeprom_, EEPROM_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED_INDEX, (long)(robotKinematics->motorWheelRotationBySecondAtFullSpeed));
    eepromWriteLong(eeprom_, EEPROM_MOTOR_MAX_TORQUE_MILLI_NEWTON_INDEX, (long)(robotKinematics->motorMaxTorqueMilliNewton));
    eepromWriteLong(eeprom_, EEPROM_MOTOR_REDUCTOR_RATIO_INDEX, (long)(robotKinematics->motorReductorRatio));
    // ROBOT VALUE
    eepromWriteLong(eeprom_, EEPROM_ROBOT_WEIGHT_GRAMS_INDEX, (long)(robotKinematics->robotWeightGrams));
}
