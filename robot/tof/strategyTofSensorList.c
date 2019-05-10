#include "strategyTofSensorList.h"

#include "../../client/motion/simple/clientMotion.h"

#include "../../common/2d/2d.h"
#include "../../common/2d/2dDebug.h"

#include "../../common/math/cenMath.h"

#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../drivers/tof/tofList.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/match/startMatch.h"
#include "../../robot/strategy/gameStrategyContext.h"

// TOF MANAGEMENT

void setTofListNameAndOrientationAngle(TofSensorList* tofSensorList, float distanceFactor) {
    unsigned int tofSensorListSize = getTofSensorListSize(tofSensorList);
    
    if (tofSensorListSize > BACK_RIGHT_SENSOR_INDEX) {
        TofSensor* backRightSensor = getTofSensorByIndex(tofSensorList, BACK_RIGHT_SENSOR_INDEX);
        backRightSensor->orientationRadian = degToRad(BACK_RIGHT_SENSOR_ANGLE_DEGREE);
        backRightSensor->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int ) (distanceFactor * BACK_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        backRightSensor->name = "BACK RIGHT";
    }
    
    if (tofSensorListSize > BACK_MIDDLE_SENSOR_INDEX) {
        TofSensor* backMiddleSensor = getTofSensorByIndex(tofSensorList, BACK_MIDDLE_SENSOR_INDEX);
        backMiddleSensor->orientationRadian = degToRad(BACK_MIDDLE_SENSOR_ANGLE_DEGREE);
        backMiddleSensor->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_MIDDLE_SENSOR_DISTANCE_THRESHOLD);
        backMiddleSensor->name = "BACK MIDDLE";
    }

    if (tofSensorListSize > BACK_LEFT_SENSOR_INDEX) {
        TofSensor* backLeftSensor = getTofSensorByIndex(tofSensorList, BACK_LEFT_SENSOR_INDEX);
        backLeftSensor->orientationRadian = degToRad(BACK_LEFT_SENSOR_ANGLE_DEGREE);
        backLeftSensor->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_LEFT_SENSOR_DISTANCE_THRESHOLD);
        backLeftSensor->name = "BACK LEFT";
    }
    // FRONT
    if (tofSensorListSize > FRONT_RIGHT_SENSOR_INDEX) {
        TofSensor* frontRightSensor = getTofSensorByIndex(tofSensorList, FRONT_RIGHT_SENSOR_INDEX); 
        frontRightSensor->orientationRadian = degToRad(FRONT_RIGHT_SENSOR_ANGLE_DEGREE);
        frontRightSensor->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        frontRightSensor->name = "FRONT RIGHT";
    }
    
    if (tofSensorListSize > FRONT_MIDDLE_SENSOR_INDEX) {
        TofSensor* frontMiddleSensor = getTofSensorByIndex(tofSensorList, FRONT_MIDDLE_SENSOR_INDEX);
        frontMiddleSensor->orientationRadian = degToRad(FRONT_MIDDLE_SENSOR_ANGLE_DEGREE);
        frontMiddleSensor->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_MIDDLE_SENSOR_DISTANCE_THRESHOLD);
        frontMiddleSensor->name = "FRONT MIDDLE";
    }
    
    if (tofSensorListSize > FRONT_LEFT_SENSOR_INDEX) {
        TofSensor* frontLeftSensor = getTofSensorByIndex(tofSensorList, FRONT_LEFT_SENSOR_INDEX);
        frontLeftSensor->orientationRadian = degToRad(FRONT_LEFT_SENSOR_ANGLE_DEGREE);
        frontLeftSensor->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_LEFT_SENSOR_DISTANCE_THRESHOLD);
        frontLeftSensor->name = "FRONT LEFT";
    }
    
    // SIDE
    if (tofSensorListSize > FRONT_SIDE_LEFT_SENSOR_INDEX) {
        TofSensor* frontSideLeftSensor = getTofSensorByIndex(tofSensorList, FRONT_SIDE_LEFT_SENSOR_INDEX); 
        frontSideLeftSensor->orientationRadian = degToRad(FRONT_SIDE_LEFT_SENSOR_ANGLE_DEGREE);
        frontSideLeftSensor->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_SIDE_LEFT_SENSOR_DISTANCE_THRESHOLD);
        frontSideLeftSensor->name = "FRONT SIDE L";
    }
    if (tofSensorListSize > FRONT_SIDE_RIGHT_SENSOR_INDEX) {
        TofSensor* frontSideRightSensor = getTofSensorByIndex(tofSensorList, FRONT_SIDE_RIGHT_SENSOR_INDEX); 
        frontSideRightSensor->orientationRadian = degToRad(FRONT_SIDE_RIGHT_SENSOR_ANGLE_DEGREE);
        frontSideRightSensor->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_SIDE_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        frontSideRightSensor->name = "FRONT SIDE R";
    }
    if (tofSensorListSize > BACK_SIDE_LEFT_SENSOR_INDEX) {
        TofSensor* backSideLeftSensor = getTofSensorByIndex(tofSensorList, BACK_SIDE_LEFT_SENSOR_INDEX); 
        backSideLeftSensor->orientationRadian = degToRad(BACK_SIDE_LEFT_SENSOR_ANGLE_DEGREE);
        backSideLeftSensor->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_SIDE_LEFT_SENSOR_DISTANCE_THRESHOLD);
        backSideLeftSensor->name = "BACK SIDE L";
    }
   if (tofSensorListSize > BACK_SIDE_RIGHT_SENSOR_INDEX) {
        TofSensor* backSideRightSensor = getTofSensorByIndex(tofSensorList, BACK_SIDE_RIGHT_SENSOR_INDEX); 
        backSideRightSensor->orientationRadian = degToRad(BACK_SIDE_RIGHT_SENSOR_ANGLE_DEGREE);
        backSideRightSensor->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_SIDE_RIGHT_SENSOR_DISTANCE_THRESHOLD);
        backSideRightSensor->name = "BACK SIDE R";
    }
}
    
void handleTofSensorList(GameStrategyContext* gameStrategyContext, StartMatch* startMatch, TofSensorList* tofSensorList, GameBoard* gameBoard) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    // We only lookup if the match is started !
    
    if (!startMatch->isMatchStartedFunction(startMatch)) {
        return;
    }
    // If Sonar is disabled, we don't check it !
    if (!isSonarActivated(robotConfig)) {
        return;
    }
    unsigned int index;
    enum TrajectoryType trajectoryType = gameStrategyContext->trajectoryType;
    if (trajectoryType == TRAJECTORY_TYPE_NONE || trajectoryType == TRAJECTORY_TYPE_ROTATION) {
        return;
    }
    for (index = 0; index < tofSensorList->size; index++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);
        if (!tofSensor->enabled) {
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

        // DetectedPoint if any
        Point detectedPoint;
        Point* pointOfView = gameStrategyContext->robotPosition;
        float pointOfViewAngleRadian = gameStrategyContext->robotAngleRadian;
        bool detected = tofComputeDetectedPointIfAny(tofSensor, pointOfView, pointOfViewAngleRadian, &detectedPoint);

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
            printPoint(alwaysOutputStream, &detectedPoint, "");
            println(alwaysOutputStream);
            // Block the notification system !
            gameStrategyContext->trajectoryType = TRAJECTORY_TYPE_NONE;
            
            // TODO 2018 : handleObstacle(gameStrategyContext);
            break;
        }
    }
}