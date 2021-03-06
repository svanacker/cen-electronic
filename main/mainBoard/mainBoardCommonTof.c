#include <math.h>

#include "mainBoardCommonTof.h"

#include "../../common/math/cenMath.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusList.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../common/math/cenMath.h"

#include "../../device/deviceList.h"

// IO Expander
#include "../../device/ioExpander/ioExpanderDeviceInterface.h"
#include "../../device/ioExpander/ioExpanderDevice.h"

// Multiplexer
#include "../../device/i2c/multiplexer/multiplexerDeviceInterface.h"
#include "../../device/i2c/multiplexer/multiplexerDevice.h"

// Tof
#include "../../device/tof/tofDevice.h"
#include "../../device/tof/tofDeviceInterface.h"

// -> IO EXPANDER
#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderDebug.h"
#include "../../drivers/ioExpander/ioExpanderList.h"

// MULTIPLEXER
#include "../../drivers/i2c/multiplexer/multiplexer.h"
#include "../../drivers/i2c/multiplexer/multiplexerDebug.h"
#include "../../drivers/i2c/multiplexer/multiplexerList.h"

// Tof
#include "../../drivers/tof/tof.h"

// 2019 Specific
#include "../../robot/2020/strategy/strategyConfig2020.h"
#include "../../robot/strategy/gameStrategyContext.h"

static TofSensorList tofSensorList;
static TofSensor tofSensorArray[MAIN_BOARD_TOF_SENSOR_LIST_LENGTH];

void mainBoardCommonUpdateTofMaxDistanceMM(GameStrategyContext* gameStrategyContext, float marginDistanceMM, float maxDistanceMM) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    float distanceFactor = (float) getSonarDistanceCheckFactor(robotConfig);
    unsigned int tofIndex;
    for (tofIndex = 0; tofIndex < tofSensorList.size; tofIndex++) {
        TofSensor* tofSensor = getTofSensorByIndex(&tofSensorList, tofIndex);
        if (!tofSensor->enabled || tofSensor->usageType != TOF_SENSOR_USAGE_TYPE_COLLISION) {
            continue;
        }
        float distanceToStopMM = 0.0f;
        if (gameStrategyContext->robotSpeed > 0.0f) {
            // Ex : At 2 m ^s -2, we need timeToDecelerate = currentSpeed / maxDeceleration  = time to stop
            // distanceToStop = (currentSpeedē) / (maxDeceleration * 2.0f)
            // TODO : Remove Magic Number
            float maxDeceleration = 500.0f; // 500 mm^s-2 on the robot
            // We convert the speed in m^s-1
            float robotSpeed = gameStrategyContext->robotSpeed;
            // We multiply by 2.0f because the opponent robot could do the same
            // We divide by a factor of 
            distanceToStopMM = ((robotSpeed * robotSpeed) / maxDeceleration) * distanceFactor;
        }
        // Min (to reach the border of the robot) + distanceToStop + small Margin
        tofSensor->thresholdMaxDistanceMM = (unsigned int) (tofSensor->thresholdMinDistanceMM + distanceToStopMM + marginDistanceMM);
        if (distanceToStopMM > maxDistanceMM) {
            tofSensor->thresholdMaxDistanceMM = (unsigned int) maxDistanceMM;
        }
    }
}

TofSensorList* mainBoardCommonTofInitDrivers(RobotConfig* robotConfig, MultiplexerList* multiplexerList) {
    (&tofSensorList)->tofSensorArray = (TofSensor(*)[]) & tofSensorArray;

    float distanceFactor = (float) getSonarDistanceCheckFactor(robotConfig);
    bool collisionEnabled = isSonarActivated(robotConfig);

    // TOF
#pragma warning( disable : 6326)
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > FRONT_RIGHT_SENSOR_INDEX) {
        TofSensor* frontRightSensor = &(tofSensorArray[FRONT_RIGHT_SENSOR_INDEX]);
        frontRightSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        frontRightSensor->angleFromRobotCenterRadian = degToRad(FRONT_RIGHT_SENSOR_ANGLE_DEGREE);
        frontRightSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        frontRightSensor->orientationRadian = frontRightSensor->angleFromRobotCenterRadian;
        frontRightSensor->thresholdMinDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE;
        frontRightSensor->thresholdMaxDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        frontRightSensor->name = "FRONT RIGHT";
        frontRightSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;

        frontRightSensor->enabled = collisionEnabled;
        frontRightSensor->changeAddress = true;
        frontRightSensor->targetAddress = VL530X_ADDRESS_0;
        frontRightSensor->multiplexer = getMultiplexerByIndex(multiplexerList, 1);
        frontRightSensor->multiplexerChannel = MULTIPLEXER_CHANNEL_0;
        
        frontRightSensor->ledArrayIndex = LED_ARRAY_INDEX_1;
        frontRightSensor->ledIndex = 1;
    }
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > FRONT_MIDDLE_SENSOR_INDEX) {
        TofSensor* frontMiddleSensor = &(tofSensorArray[FRONT_MIDDLE_SENSOR_INDEX]);
        frontMiddleSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        frontMiddleSensor->angleFromRobotCenterRadian = degToRad(FRONT_MIDDLE_SENSOR_ANGLE_DEGREE);
        frontMiddleSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        frontMiddleSensor->orientationRadian = frontMiddleSensor->angleFromRobotCenterRadian;
        frontMiddleSensor->thresholdMinDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE;
        frontMiddleSensor->thresholdMaxDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_MIDDLE_SENSOR_DISTANCE_THRESHOLD);
        frontMiddleSensor->name = "FRONT MIDDLE";
        frontMiddleSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;

        frontMiddleSensor->enabled = collisionEnabled;
        frontMiddleSensor->changeAddress = true;
        frontMiddleSensor->targetAddress = VL530X_ADDRESS_1;
        frontMiddleSensor->multiplexer = getMultiplexerByIndex(multiplexerList, 1);
        frontMiddleSensor->multiplexerChannel = MULTIPLEXER_CHANNEL_1;

        frontMiddleSensor->ledArrayIndex = LED_ARRAY_INDEX_1;
        frontMiddleSensor->ledIndex = 0;
    }
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > FRONT_LEFT_SENSOR_INDEX) {
        TofSensor* frontLeftSensor = &(tofSensorArray[FRONT_LEFT_SENSOR_INDEX]);
        frontLeftSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        frontLeftSensor->angleFromRobotCenterRadian = degToRad(FRONT_LEFT_SENSOR_ANGLE_DEGREE);
        frontLeftSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        frontLeftSensor->orientationRadian = frontLeftSensor->angleFromRobotCenterRadian;
        frontLeftSensor->thresholdMinDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE;
        frontLeftSensor->thresholdMaxDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_LEFT_SENSOR_DISTANCE_THRESHOLD);
        frontLeftSensor->name = "FRONT LEFT";
        frontLeftSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;

        frontLeftSensor->enabled = collisionEnabled;
        frontLeftSensor->changeAddress = true;
        frontLeftSensor->targetAddress = VL530X_ADDRESS_2;
        frontLeftSensor->multiplexer = getMultiplexerByIndex(multiplexerList, 1);
        frontLeftSensor->multiplexerChannel = MULTIPLEXER_CHANNEL_2;

        frontLeftSensor->ledArrayIndex = LED_ARRAY_INDEX_0;
        frontLeftSensor->ledIndex = 2;
    }
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > BACK_RIGHT_SENSOR_INDEX) {
        TofSensor* backRightSensor = &(tofSensorArray[BACK_RIGHT_SENSOR_INDEX]);
        backRightSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        backRightSensor->angleFromRobotCenterRadian = degToRad(BACK_RIGHT_SENSOR_ANGLE_DEGREE);
        backRightSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        backRightSensor->orientationRadian = backRightSensor->angleFromRobotCenterRadian;
        backRightSensor->thresholdMinDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE;
        backRightSensor->thresholdMaxDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        backRightSensor->name = "BACK RIGHT";
        backRightSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;

        backRightSensor->enabled = collisionEnabled;
        backRightSensor->changeAddress = true;
        backRightSensor->targetAddress = VL530X_ADDRESS_3;
        backRightSensor->multiplexer = getMultiplexerByIndex(multiplexerList, 1);
        backRightSensor->multiplexerChannel = MULTIPLEXER_CHANNEL_3;
        
        backRightSensor->ledArrayIndex = LED_ARRAY_INDEX_1;
        backRightSensor->ledIndex = 4;
    }
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > BACK_MIDDLE_SENSOR_INDEX) {
        TofSensor* backMiddleSensor = &(tofSensorArray[BACK_MIDDLE_SENSOR_INDEX]);
        backMiddleSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        backMiddleSensor->angleFromRobotCenterRadian = degToRad(BACK_MIDDLE_SENSOR_ANGLE_DEGREE);
        backMiddleSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        backMiddleSensor->orientationRadian = backMiddleSensor->angleFromRobotCenterRadian;
        backMiddleSensor->thresholdMinDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE;
        backMiddleSensor->thresholdMaxDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_MIDDLE_SENSOR_DISTANCE_THRESHOLD);
        backMiddleSensor->name = "BACK MIDDLE";
        backMiddleSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;

        backMiddleSensor->enabled = collisionEnabled;
        backMiddleSensor->changeAddress = true;
        backMiddleSensor->targetAddress = VL530X_ADDRESS_4;
        backMiddleSensor->multiplexer = getMultiplexerByIndex(multiplexerList, 1);
        backMiddleSensor->multiplexerChannel = MULTIPLEXER_CHANNEL_4;
        
        backMiddleSensor->ledArrayIndex = LED_ARRAY_INDEX_0;
        backMiddleSensor->ledIndex = 3;
    }
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > BACK_LEFT_SENSOR_INDEX) {
        TofSensor* backLeftSensor = &(tofSensorArray[BACK_LEFT_SENSOR_INDEX]);
        backLeftSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        backLeftSensor->angleFromRobotCenterRadian = degToRad(BACK_LEFT_SENSOR_ANGLE_DEGREE);
        backLeftSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        backLeftSensor->orientationRadian = backLeftSensor->angleFromRobotCenterRadian;
        backLeftSensor->thresholdMinDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE;
        backLeftSensor->thresholdMaxDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_LEFT_SENSOR_DISTANCE_THRESHOLD);
        backLeftSensor->name = "BACK LEFT";
        backLeftSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;

        backLeftSensor->enabled = collisionEnabled;
        backLeftSensor->changeAddress = true;
        backLeftSensor->targetAddress = VL530X_ADDRESS_5;
        backLeftSensor->multiplexer = getMultiplexerByIndex(multiplexerList, 1);
        backLeftSensor->multiplexerChannel = MULTIPLEXER_CHANNEL_5;
        
        backLeftSensor->ledArrayIndex = LED_ARRAY_INDEX_0;
        backLeftSensor->ledIndex = 4;
    }

    // NOT USED
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > 6) {
        tofSensorArray[6].enabled = false;

    }
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > 7) {
        tofSensorArray[7].enabled = false;
    }

    // TCA9548A_ADDRESS_0 -----------------------------------------
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > FRONT_SIDE_LEFT_SENSOR_INDEX) {
        TofSensor* frontSideLeftSensor = &(tofSensorArray[FRONT_SIDE_LEFT_SENSOR_INDEX]);
        frontSideLeftSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        frontSideLeftSensor->angleFromRobotCenterRadian = degToRad(75.0f);
        frontSideLeftSensor->distanceFromRobotCenter = 150.0f;
        frontSideLeftSensor->orientationRadian = degToRad(FRONT_SIDE_LEFT_SENSOR_ANGLE_DEGREE);
        frontSideLeftSensor->thresholdMinDistanceMM = FRONT_SIDE_TOF_TO_FRONT_OF_ROBOT_DISTANCE;
        frontSideLeftSensor->thresholdMaxDistanceMM = FRONT_SIDE_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_SIDE_LEFT_SENSOR_DISTANCE_THRESHOLD);
        frontSideLeftSensor->name = "FRONT SIDE L";
        frontSideLeftSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;

        frontSideLeftSensor->enabled = collisionEnabled;
        frontSideLeftSensor->changeAddress = true;
        frontSideLeftSensor->targetAddress = VL530X_ADDRESS_8;
        frontSideLeftSensor->multiplexer = getMultiplexerByIndex(multiplexerList, 0);
        frontSideLeftSensor->multiplexerChannel = MULTIPLEXER_CHANNEL_0;
        
        frontSideLeftSensor->ledArrayIndex = LED_ARRAY_INDEX_0;
        frontSideLeftSensor->ledIndex = 1;
    }
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > FRONT_SIDE_RIGHT_SENSOR_INDEX) {
        TofSensor* frontSideRightSensor = &(tofSensorArray[FRONT_SIDE_RIGHT_SENSOR_INDEX]);
        frontSideRightSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        frontSideRightSensor->angleFromRobotCenterRadian = degToRad(-75.0f);
        frontSideRightSensor->distanceFromRobotCenter = 150.0f;
        frontSideRightSensor->orientationRadian = degToRad(FRONT_SIDE_RIGHT_SENSOR_ANGLE_DEGREE);
        frontSideRightSensor->thresholdMinDistanceMM = FRONT_SIDE_TOF_TO_FRONT_OF_ROBOT_DISTANCE;
        frontSideRightSensor->thresholdMaxDistanceMM = FRONT_SIDE_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_SIDE_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        frontSideRightSensor->name = "FRONT SIDE R";
        frontSideRightSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;

        frontSideRightSensor->enabled = collisionEnabled;
        frontSideRightSensor->changeAddress = true;
        frontSideRightSensor->targetAddress = VL530X_ADDRESS_9;
        frontSideRightSensor->multiplexer = getMultiplexerByIndex(multiplexerList, 0);
        frontSideRightSensor->multiplexerChannel = MULTIPLEXER_CHANNEL_1;

        frontSideRightSensor->ledArrayIndex = LED_ARRAY_INDEX_1;
        frontSideRightSensor->ledIndex = 2;
    }
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > BACK_SIDE_RIGHT_SENSOR_INDEX) {
        TofSensor* backSideRightSensor = &(tofSensorArray[BACK_SIDE_RIGHT_SENSOR_INDEX]);
        backSideRightSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        backSideRightSensor->angleFromRobotCenterRadian = degToRad(-105.0f);
        backSideRightSensor->distanceFromRobotCenter = 150.0f;
        backSideRightSensor->orientationRadian = degToRad(BACK_SIDE_RIGHT_SENSOR_ANGLE_DEGREE);
        backSideRightSensor->thresholdMinDistanceMM = FRONT_SIDE_TOF_TO_BACK_OF_ROBOT_DISTANCE;
        backSideRightSensor->thresholdMaxDistanceMM = FRONT_SIDE_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_SIDE_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        backSideRightSensor->name = "BACK SIDE R";
        backSideRightSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;

        backSideRightSensor->enabled = collisionEnabled;
        backSideRightSensor->changeAddress = true;
        backSideRightSensor->targetAddress = VL530X_ADDRESS_10;
        backSideRightSensor->multiplexer = getMultiplexerByIndex(multiplexerList, 0);
        backSideRightSensor->multiplexerChannel = MULTIPLEXER_CHANNEL_2;

        backSideRightSensor->ledArrayIndex = LED_ARRAY_INDEX_1;
        backSideRightSensor->ledIndex = 3;
    }
    // TOF 11 & 12 are defined in forkScan2019.c
    if (MAIN_BOARD_TOF_SENSOR_LIST_LENGTH > BACK_SIDE_LEFT_SENSOR_INDEX) {
        TofSensor* backSideLeftSensor = &(tofSensorArray[BACK_SIDE_LEFT_SENSOR_INDEX]);
        backSideLeftSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        backSideLeftSensor->angleFromRobotCenterRadian = degToRad(105.0f);
        backSideLeftSensor->distanceFromRobotCenter = 150.0f;
        backSideLeftSensor->orientationRadian = degToRad(BACK_SIDE_LEFT_SENSOR_ANGLE_DEGREE);
        backSideLeftSensor->thresholdMinDistanceMM = FRONT_SIDE_TOF_TO_BACK_OF_ROBOT_DISTANCE;
        backSideLeftSensor->thresholdMaxDistanceMM = FRONT_SIDE_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_SIDE_LEFT_SENSOR_DISTANCE_THRESHOLD);
        backSideLeftSensor->name = "BACK SIDE L";
        backSideLeftSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;

        backSideLeftSensor->enabled = collisionEnabled;
        backSideLeftSensor->changeAddress = true;
        backSideLeftSensor->targetAddress = VL530X_ADDRESS_13;
        backSideLeftSensor->multiplexer = getMultiplexerByIndex(multiplexerList, 0);
        backSideLeftSensor->multiplexerChannel = MULTIPLEXER_CHANNEL_5;
        
        backSideLeftSensor->ledArrayIndex = LED_ARRAY_INDEX_0;
        backSideLeftSensor->ledIndex = 0;        
    }

    return &tofSensorList;
}

TofSensorList* mainBoardCommonTofGetTofSensorList(void) {
    return &tofSensorList;
}
