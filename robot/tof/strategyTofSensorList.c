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
        backRightSensor->type = TOF_SENSOR_TYPE_COLLISION;
        backRightSensor->angleFromRobotCenter = degToRad(BACK_RIGHT_SENSOR_ANGLE_DEGREE);
        backRightSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        backRightSensor->orientationRadian = backRightSensor->angleFromRobotCenter;
        backRightSensor->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int ) (distanceFactor * BACK_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        backRightSensor->name = "BACK RIGHT";
    }
    
    if (tofSensorListSize > BACK_MIDDLE_SENSOR_INDEX) {
        TofSensor* backMiddleSensor = getTofSensorByIndex(tofSensorList, BACK_MIDDLE_SENSOR_INDEX);
        backMiddleSensor->type = TOF_SENSOR_TYPE_COLLISION;
        backMiddleSensor->angleFromRobotCenter = degToRad(BACK_MIDDLE_SENSOR_ANGLE_DEGREE);
        backMiddleSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        backMiddleSensor->orientationRadian = backMiddleSensor->angleFromRobotCenter;
        backMiddleSensor->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_MIDDLE_SENSOR_DISTANCE_THRESHOLD);
        backMiddleSensor->name = "BACK MIDDLE";
    }

    if (tofSensorListSize > BACK_LEFT_SENSOR_INDEX) {
        TofSensor* backLeftSensor = getTofSensorByIndex(tofSensorList, BACK_LEFT_SENSOR_INDEX);
        backLeftSensor->type = TOF_SENSOR_TYPE_COLLISION;
        backLeftSensor->angleFromRobotCenter = degToRad(BACK_LEFT_SENSOR_ANGLE_DEGREE);
        backLeftSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        backLeftSensor->orientationRadian = backLeftSensor->angleFromRobotCenter;
        backLeftSensor->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_LEFT_SENSOR_DISTANCE_THRESHOLD);
        backLeftSensor->name = "BACK LEFT";
    }
    // FRONT
    if (tofSensorListSize > FRONT_RIGHT_SENSOR_INDEX) {
        TofSensor* frontRightSensor = getTofSensorByIndex(tofSensorList, FRONT_RIGHT_SENSOR_INDEX);
        frontRightSensor->type = TOF_SENSOR_TYPE_COLLISION;
        frontRightSensor->angleFromRobotCenter = degToRad(FRONT_RIGHT_SENSOR_ANGLE_DEGREE);
        frontRightSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        frontRightSensor->orientationRadian = frontRightSensor->angleFromRobotCenter;
        frontRightSensor->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        frontRightSensor->name = "FRONT RIGHT";
    }
    
    if (tofSensorListSize > FRONT_MIDDLE_SENSOR_INDEX) {
        TofSensor* frontMiddleSensor = getTofSensorByIndex(tofSensorList, FRONT_MIDDLE_SENSOR_INDEX);
        frontMiddleSensor->type = TOF_SENSOR_TYPE_COLLISION;
        frontMiddleSensor->angleFromRobotCenter = degToRad(FRONT_MIDDLE_SENSOR_ANGLE_DEGREE);
        frontMiddleSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        frontMiddleSensor->orientationRadian = frontMiddleSensor->angleFromRobotCenter;
        frontMiddleSensor->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_MIDDLE_SENSOR_DISTANCE_THRESHOLD);
        frontMiddleSensor->name = "FRONT MIDDLE";
    }
    
    if (tofSensorListSize > FRONT_LEFT_SENSOR_INDEX) {
        TofSensor* frontLeftSensor = getTofSensorByIndex(tofSensorList, FRONT_LEFT_SENSOR_INDEX);
        frontLeftSensor->type = TOF_SENSOR_TYPE_COLLISION;
        frontLeftSensor->angleFromRobotCenter = degToRad(FRONT_LEFT_SENSOR_ANGLE_DEGREE);
        frontLeftSensor->distanceFromRobotCenter = 30.0f;
        // Same value than angleFromRobotCenter because placed on a circle
        frontLeftSensor->orientationRadian = frontLeftSensor->angleFromRobotCenter;
        frontLeftSensor->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_LEFT_SENSOR_DISTANCE_THRESHOLD);
        frontLeftSensor->name = "FRONT LEFT";
    }
    
    // SIDE
    if (tofSensorListSize > FRONT_SIDE_LEFT_SENSOR_INDEX) {
        TofSensor* frontSideLeftSensor = getTofSensorByIndex(tofSensorList, FRONT_SIDE_LEFT_SENSOR_INDEX);
        frontSideLeftSensor->type = TOF_SENSOR_TYPE_COLLISION;
        frontSideLeftSensor->angleFromRobotCenter = degToRad(75.0f);
        frontSideLeftSensor->distanceFromRobotCenter = 150.0f;
        frontSideLeftSensor->orientationRadian = degToRad(FRONT_SIDE_LEFT_SENSOR_ANGLE_DEGREE);
        frontSideLeftSensor->thresholdDistanceMM = FRONT_SIDE_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_SIDE_LEFT_SENSOR_DISTANCE_THRESHOLD);
        frontSideLeftSensor->name = "FRONT SIDE L";
    }
    if (tofSensorListSize > FRONT_SIDE_RIGHT_SENSOR_INDEX) {
        TofSensor* frontSideRightSensor = getTofSensorByIndex(tofSensorList, FRONT_SIDE_RIGHT_SENSOR_INDEX);
        frontSideRightSensor->type = TOF_SENSOR_TYPE_COLLISION;
        frontSideRightSensor->angleFromRobotCenter = degToRad(-75.0f);
        frontSideRightSensor->distanceFromRobotCenter = 150.0f;
        frontSideRightSensor->orientationRadian = degToRad(FRONT_SIDE_RIGHT_SENSOR_ANGLE_DEGREE);
        frontSideRightSensor->thresholdDistanceMM = FRONT_SIDE_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_SIDE_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        frontSideRightSensor->name = "FRONT SIDE R";
    }
    if (tofSensorListSize > BACK_SIDE_LEFT_SENSOR_INDEX) {
        TofSensor* backSideLeftSensor = getTofSensorByIndex(tofSensorList, BACK_SIDE_LEFT_SENSOR_INDEX); 
        backSideLeftSensor->type = TOF_SENSOR_TYPE_COLLISION;
        backSideLeftSensor->angleFromRobotCenter = degToRad(105.0f);
        backSideLeftSensor->distanceFromRobotCenter = 150.0f;
        backSideLeftSensor->orientationRadian = degToRad(BACK_SIDE_LEFT_SENSOR_ANGLE_DEGREE);
        backSideLeftSensor->thresholdDistanceMM = FRONT_SIDE_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_SIDE_LEFT_SENSOR_DISTANCE_THRESHOLD);
        backSideLeftSensor->name = "BACK SIDE L";
    }
   if (tofSensorListSize > BACK_SIDE_RIGHT_SENSOR_INDEX) {
        TofSensor* backSideRightSensor = getTofSensorByIndex(tofSensorList, BACK_SIDE_RIGHT_SENSOR_INDEX);
        backSideRightSensor->type = TOF_SENSOR_TYPE_COLLISION;
        backSideRightSensor->angleFromRobotCenter = degToRad(-105.0f);
        backSideRightSensor->distanceFromRobotCenter = 150.0f;
        backSideRightSensor->orientationRadian = degToRad(BACK_SIDE_RIGHT_SENSOR_ANGLE_DEGREE);
        backSideRightSensor->thresholdDistanceMM = FRONT_SIDE_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_SIDE_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        backSideRightSensor->name = "BACK SIDE R";
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
        if (tofSensor->type != TOF_SENSOR_TYPE_COLLISION) {
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
        if (distance <= SENSOR_DISTANCE_MIN_TRESHOLD) {
            continue;
        }
        // Recompute the real detected point
        Point detectedPoint;
        Point* pointOfView = gameStrategyContext->robotPosition;
        float pointOfViewAngleRadian = gameStrategyContext->robotAngleRadian;
        bool detected = tofComputeDetectedPointIfAny(tofSensor, pointOfView, pointOfViewAngleRadian, &detectedPoint);
        
        tofSensorListBeep(tofSensorList, detected);

        if (!detected) {
            continue;
        }
        
        // Update the position from the MOTOR BOARD. If we don't do it,
        // The board keep the original value from the latest move / notification or the latest callback
        // TODO : Clarify the usage of Robot Position
        updateIfNeededRobotPositionFromMotorBoardToMainBoard(gameStrategyContext);
        detected = tofComputeDetectedPointIfAny(tofSensor, pointOfView, pointOfViewAngleRadian, &detectedPoint);

        if (!detected) {
            continue;
        }
        
        
        // We must know if it's in the gameboard
        if (isPointInTheCollisionArea(gameBoard, &detectedPoint)) {
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
            
            // TODO 2018 : handleObstacle(gameStrategyContext);
            break;
        }
    }
}