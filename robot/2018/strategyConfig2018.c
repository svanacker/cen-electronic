#include "strategyConfig2018.h"

#include "../../motion/extended/bsplineMotion.h"

#include "../../robot/config/robotConfig.h"

float getAccelerationFactor(RobotConfig* robotConfig) {
    if (isConfigSet(robotConfig, CONFIG_SPEED_LOW_MASK)) {
        return MOTION_ACCELERATION_FACTOR_NORMAL;
    }
    if (isConfigSet(robotConfig, CONFIG_SPEED_VERY_LOW_MASK)) {
        return MOTION_ACCELERATION_FACTOR_LOW;
    }
    if (isConfigSet(robotConfig, CONFIG_SPEED_ULTRA_LOW_MASK)) {
        return MOTION_ACCELERATION_FACTOR_MIN;
    }
    // default is MOTION_SPEED_FACTOR_HIGH
    return MOTION_ACCELERATION_FACTOR_HIGH;
}

float getSpeedFactor(RobotConfig* robotConfig) {
    if (isConfigSet(robotConfig, CONFIG_SPEED_LOW_MASK)) {
        return MOTION_SPEED_FACTOR_NORMAL;
    }
    if (isConfigSet(robotConfig, CONFIG_SPEED_VERY_LOW_MASK)) {
        return MOTION_SPEED_FACTOR_LOW;
    }
    if (isConfigSet(robotConfig, CONFIG_SPEED_ULTRA_LOW_MASK)) {
        return MOTION_SPEED_FACTOR_MIN;
    }
    // default is MOTION_SPEED_FACTOR_HIGH
    return MOTION_SPEED_FACTOR_HIGH;
}

bool isSonarActivated(RobotConfig* robotConfig) {
    return isConfigSet(robotConfig, CONFIG_SONAR_FAR_MASK | CONFIG_SONAR_NEAR_MASK);
}

float getSonarDistanceCheckFactor(RobotConfig* robotConfig) {
    if (isConfigSet(robotConfig, CONFIG_SONAR_FAR_MASK)) {
        return 1.0f;
    }
    else if (isConfigSet(robotConfig, CONFIG_SONAR_NEAR_MASK)) {
        return 0.5f;
    }
    // To avoid to detect something !
    return 5.0f;
}