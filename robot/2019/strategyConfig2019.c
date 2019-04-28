#include "strategyConfig2019.h"

#include "../../common/error/error.h"

#include "../../motion/motionConstants.h"
#include "../../motion/extended/bsplineMotion.h"

#include "../../robot/config/robotConfig.h"

const float MOTION_ACCELERATION_FACTORS[8] = { MOTION_ACCELERATION_FACTOR_0, MOTION_ACCELERATION_FACTOR_1, MOTION_ACCELERATION_FACTOR_2, MOTION_ACCELERATION_FACTOR_3,
                   MOTION_ACCELERATION_FACTOR_4, MOTION_ACCELERATION_FACTOR_5, MOTION_ACCELERATION_FACTOR_6, MOTION_ACCELERATION_FACTOR_7 };

const float MOTION_SPEED_FACTORS[8] = { MOTION_SPEED_FACTOR_0, MOTION_SPEED_FACTOR_1, MOTION_SPEED_FACTOR_2, MOTION_SPEED_FACTOR_3,
                   MOTION_SPEED_FACTOR_4, MOTION_SPEED_FACTOR_5, MOTION_SPEED_FACTOR_6, MOTION_SPEED_FACTOR_7 };

float getAccelerationFactor(RobotConfig* robotConfig) {
    unsigned int config = robotConfig->robotConfigReadInt(robotConfig);
    unsigned int accelerationFactorIndex = (config & CONFIG_SPEED_MASK) >> CONFIG_SHIFT_BIT_VALUE;
    if (accelerationFactorIndex >= 0 && accelerationFactorIndex <= 7) {
        return MOTION_ACCELERATION_FACTORS[accelerationFactorIndex];
    }
    writeError(ROBOT_CONFIG_ERROR);

    return MOTION_ACCELERATION_FACTOR_0;
}

float getSpeedFactor(RobotConfig* robotConfig) {
    unsigned int config = robotConfig->robotConfigReadInt(robotConfig);
    unsigned int speedFactorIndex = (config & CONFIG_SPEED_MASK) >> CONFIG_SHIFT_BIT_VALUE;
    if (speedFactorIndex >= 0 && speedFactorIndex <= 7) {
        return MOTION_SPEED_FACTORS[speedFactorIndex];
    }
    writeError(ROBOT_CONFIG_ERROR);

    return MOTION_SPEED_FACTOR_0;
}

float getSonarDistanceCheckFactor(RobotConfig* robotConfig) {
    if (isConfigSet(robotConfig, CONFIG_SONAR_FAR_MASK)) {
        // Both Far & Near means average
        if (isConfigSet(robotConfig, CONFIG_SONAR_NEAR_MASK)) {
            return 0.75f;
        }
        return 1.0f;
    }
    else if (isConfigSet(robotConfig, CONFIG_SONAR_NEAR_MASK)) {
        return 0.50f;
    }
    // To avoid to detect something too far !
    return 8.0f;
}