#include "strategyTofSensorList.h"

#include "../../client/motion/position/clientTrajectory.h"
#include "../../client/motion/simple/clientMotion.h"

#include "../../common/2d/2d.h"
#include "../../common/2d/2dDebug.h"

#include "../../common/math/cenMath.h"

#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../drivers/tof/tofList.h"

#include "../../robot/robot.h"
#include "../../robot/gameboard/gameboard.h"
#include "../../robot/match/startMatch.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameStrategyMotionHandler.h"
#include "../../drivers/ioExpander/ioExpanderList.h"

// TOF MANAGEMENT

void setTofListNameAndOrientationAngle(TofSensorList* tofSensorList, float distanceFactor) {
    unsigned int tofSensorListSize = getTofSensorListSize(tofSensorList);
    // Be careful, the position must be defined with an angle of Robot of 0
    // What means the Robot going along the X axis
    if (tofSensorListSize > BACK_RIGHT_SENSOR_INDEX) {
        TofSensor* backRightSensor = getTofSensorByIndex(tofSensorList, BACK_RIGHT_SENSOR_INDEX);
        backRightSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        backRightSensor->angleFromRobotCenterRadian = degToRad(BACK_RIGHT_SENSOR_ANGLE_DEGREE);
        backRightSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        backRightSensor->orientationRadian = backRightSensor->angleFromRobotCenterRadian;
        backRightSensor->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int ) (distanceFactor * BACK_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        backRightSensor->name = "BACK RIGHT";
        backRightSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;
    }
    
    if (tofSensorListSize > BACK_MIDDLE_SENSOR_INDEX) {
        TofSensor* backMiddleSensor = getTofSensorByIndex(tofSensorList, BACK_MIDDLE_SENSOR_INDEX);
        backMiddleSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        backMiddleSensor->angleFromRobotCenterRadian = degToRad(BACK_MIDDLE_SENSOR_ANGLE_DEGREE);
        backMiddleSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        backMiddleSensor->orientationRadian = backMiddleSensor->angleFromRobotCenterRadian;
        backMiddleSensor->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_MIDDLE_SENSOR_DISTANCE_THRESHOLD);
        backMiddleSensor->name = "BACK MIDDLE";
        backMiddleSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;
    }

    if (tofSensorListSize > BACK_LEFT_SENSOR_INDEX) {
        TofSensor* backLeftSensor = getTofSensorByIndex(tofSensorList, BACK_LEFT_SENSOR_INDEX);
        backLeftSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        backLeftSensor->angleFromRobotCenterRadian = degToRad(BACK_LEFT_SENSOR_ANGLE_DEGREE);
        backLeftSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        backLeftSensor->orientationRadian = backLeftSensor->angleFromRobotCenterRadian;
        backLeftSensor->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_LEFT_SENSOR_DISTANCE_THRESHOLD);
        backLeftSensor->name = "BACK LEFT";
        backLeftSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;
    }
    // FRONT
    if (tofSensorListSize > FRONT_RIGHT_SENSOR_INDEX) {
        TofSensor* frontRightSensor = getTofSensorByIndex(tofSensorList, FRONT_RIGHT_SENSOR_INDEX);
        frontRightSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        frontRightSensor->angleFromRobotCenterRadian = degToRad(FRONT_RIGHT_SENSOR_ANGLE_DEGREE);
        frontRightSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        frontRightSensor->orientationRadian = frontRightSensor->angleFromRobotCenterRadian;
        frontRightSensor->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        frontRightSensor->name = "FRONT RIGHT";
        frontRightSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;
    }
    
    if (tofSensorListSize > FRONT_MIDDLE_SENSOR_INDEX) {
        TofSensor* frontMiddleSensor = getTofSensorByIndex(tofSensorList, FRONT_MIDDLE_SENSOR_INDEX);
        frontMiddleSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        frontMiddleSensor->angleFromRobotCenterRadian = degToRad(FRONT_MIDDLE_SENSOR_ANGLE_DEGREE);
        frontMiddleSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        frontMiddleSensor->orientationRadian = frontMiddleSensor->angleFromRobotCenterRadian;
        frontMiddleSensor->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_MIDDLE_SENSOR_DISTANCE_THRESHOLD);
        frontMiddleSensor->name = "FRONT MIDDLE";
        frontMiddleSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;
    }
    
    if (tofSensorListSize > FRONT_LEFT_SENSOR_INDEX) {
        TofSensor* frontLeftSensor = getTofSensorByIndex(tofSensorList, FRONT_LEFT_SENSOR_INDEX);
        frontLeftSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        frontLeftSensor->angleFromRobotCenterRadian = degToRad(FRONT_LEFT_SENSOR_ANGLE_DEGREE);
        frontLeftSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        frontLeftSensor->orientationRadian = frontLeftSensor->angleFromRobotCenterRadian;
        frontLeftSensor->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_LEFT_SENSOR_DISTANCE_THRESHOLD);
        frontLeftSensor->name = "FRONT LEFT";
        frontLeftSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;
    }
    
    // SIDE
    if (tofSensorListSize > FRONT_SIDE_LEFT_SENSOR_INDEX) {
        TofSensor* frontSideLeftSensor = getTofSensorByIndex(tofSensorList, FRONT_SIDE_LEFT_SENSOR_INDEX);
        frontSideLeftSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        frontSideLeftSensor->angleFromRobotCenterRadian = degToRad(75.0f);
        frontSideLeftSensor->distanceFromRobotCenter = 150.0f;
        frontSideLeftSensor->orientationRadian = degToRad(FRONT_SIDE_LEFT_SENSOR_ANGLE_DEGREE);
        frontSideLeftSensor->thresholdDistanceMM = FRONT_SIDE_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_SIDE_LEFT_SENSOR_DISTANCE_THRESHOLD);
        frontSideLeftSensor->name = "FRONT SIDE L";
        frontSideLeftSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;
    }
    if (tofSensorListSize > FRONT_SIDE_RIGHT_SENSOR_INDEX) {
        TofSensor* frontSideRightSensor = getTofSensorByIndex(tofSensorList, FRONT_SIDE_RIGHT_SENSOR_INDEX);
        frontSideRightSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        frontSideRightSensor->angleFromRobotCenterRadian = degToRad(-75.0f);
        frontSideRightSensor->distanceFromRobotCenter = 150.0f;
        frontSideRightSensor->orientationRadian = degToRad(FRONT_SIDE_RIGHT_SENSOR_ANGLE_DEGREE);
        frontSideRightSensor->thresholdDistanceMM = FRONT_SIDE_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_SIDE_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        frontSideRightSensor->name = "FRONT SIDE R";
        frontSideRightSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;
    }
    if (tofSensorListSize > BACK_SIDE_LEFT_SENSOR_INDEX) {
        TofSensor* backSideLeftSensor = getTofSensorByIndex(tofSensorList, BACK_SIDE_LEFT_SENSOR_INDEX); 
        backSideLeftSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        backSideLeftSensor->angleFromRobotCenterRadian = degToRad(105.0f);
        backSideLeftSensor->distanceFromRobotCenter = 150.0f;
        backSideLeftSensor->orientationRadian = degToRad(BACK_SIDE_LEFT_SENSOR_ANGLE_DEGREE);
        backSideLeftSensor->thresholdDistanceMM = FRONT_SIDE_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_SIDE_LEFT_SENSOR_DISTANCE_THRESHOLD);
        backSideLeftSensor->name = "BACK SIDE L";
        backSideLeftSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;
    }
   if (tofSensorListSize > BACK_SIDE_RIGHT_SENSOR_INDEX) {
        TofSensor* backSideRightSensor = getTofSensorByIndex(tofSensorList, BACK_SIDE_RIGHT_SENSOR_INDEX);
        backSideRightSensor->usageType = TOF_SENSOR_USAGE_TYPE_COLLISION;
        backSideRightSensor->angleFromRobotCenterRadian = degToRad(-105.0f);
        backSideRightSensor->distanceFromRobotCenter = 150.0f;
        backSideRightSensor->orientationRadian = degToRad(BACK_SIDE_RIGHT_SENSOR_ANGLE_DEGREE);
        backSideRightSensor->thresholdDistanceMM = FRONT_SIDE_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_SIDE_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        backSideRightSensor->name = "BACK SIDE R";
        backSideRightSensor->detectionThreshold = STRATEGY_DETECTION_THRESHOLD;
    }
}
    
void handleTofSensorList(GameStrategyContext* gameStrategyContext, StartMatch* startMatch, TofSensorList* tofSensorList, GameBoard* gameBoard) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    // We only lookup if the match is started !
    if (!startMatch->isMatchStartedFunction(startMatch)) {
        tofSensorListBeep(tofSensorList, false);
        return;
    }
    // If Sonar is disabled, we don't check it !
    if (!isSonarActivated(robotConfig)) {
        tofSensorListBeep(tofSensorList, false);
        return;
    }
    unsigned int index;
    enum TrajectoryType trajectoryType = gameStrategyContext->trajectoryType;
    if (trajectoryType == TRAJECTORY_TYPE_NONE || trajectoryType == TRAJECTORY_TYPE_ROTATION) {
        tofSensorListBeep(tofSensorList, false);
        return;
    }
    for (index = 0; index < tofSensorList->size; index++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);
        if (!tofSensor->enabled) {
            continue;
        }
        if (tofSensor->usageType != TOF_SENSOR_USAGE_TYPE_COLLISION) {
            continue;
        }
        
        bool tofBackward = isTofSensorBackwardOriented(tofSensor);
        
        // Don't manage Backward TofSensor if we go forward
        if (tofBackward && trajectoryType == TRAJECTORY_TYPE_FORWARD) {
            continue;
        }
        
        // Don't manage Forward TofSensor if we go backward
        if (!tofBackward && trajectoryType == TRAJECTORY_TYPE_BACKWARD) {
            continue;
        }
        
        unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);
        // If the distance is not in the range
        if (distance >= tofSensor->thresholdDistanceMM || distance <= SENSOR_DISTANCE_MIN_TRESHOLD) {
            if (tofSensor->detectedCount > 0) {
                tofSensor->detectedCount--;
            }
        }
        else {
            tofSensor->detectedCount++;
        }
        
        if (tofSensor->detectedCount < tofSensor->detectionThreshold) {
            continue;
        }

        // Recompute the real detected point
        Point detectedPoint;
        Point* pointOfView = gameStrategyContext->robotPosition;
        float pointOfViewAngleRadian = gameStrategyContext->robotAngleRadian;
        bool detected = tofComputeDetectedPointIfAny(tofSensor, pointOfView, pointOfViewAngleRadian, &detectedPoint);
        
        if (!detected) {
            continue;
        }
        
        /* We don't need this section anymore because trajectory notification on UART 5 works well !!
        // Update the position from the MOTOR BOARD. If we don't do it,
        // The board keep the original value from the latest move / notification or the latest callback
        // TODO : Clarify the usage of Robot Position
        updateIfNeededRobotPositionFromMotorBoardToMainBoard(gameStrategyContext);
        detected = tofComputeDetectedPointIfAny(tofSensor, pointOfView, pointOfViewAngleRadian, &detectedPoint);

        if (!detected) {
            continue;
        }
        */
        
        // We must know if it's in the gameboard
        if (isPointInTheCollisionArea(gameBoard, &detectedPoint)) {
            tofSensorListBeep(tofSensorList, detected);

            // motionDriverStop();
            motionDriverCancel();
            // Then we notify !
            OutputStream* alwaysOutputStream = getAlwaysOutputStreamLogger();
            println(alwaysOutputStream);
            appendStringAndDec(alwaysOutputStream, "Tof:", index);
            appendString(alwaysOutputStream, ",");
            appendString(alwaysOutputStream, tofSensor->name);
            appendCRLF(alwaysOutputStream);

            // Print the position of the robot
            appendStringCRLF(alwaysOutputStream, "Robot Position:");
            printPoint(alwaysOutputStream, pointOfView, "");

            // Print the detected Point 
            appendStringCRLF(alwaysOutputStream, "Detected Point :");
            printPoint(alwaysOutputStream, &detectedPoint, "");
            // Block the notification system !
            gameStrategyContext->trajectoryType = TRAJECTORY_TYPE_NONE;
            
            tofSensorListResetDetectionCount(tofSensorList);
            
            // TODO 2018 : handleObstacle(gameStrategyContext);
            break;
        }
    }
}