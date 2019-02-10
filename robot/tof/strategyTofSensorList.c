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

void setTofListOrientationAngle(TofSensorList* tofSensorList, float distanceFactor) {
    unsigned int tofSensorListSize = getTofSensorListSize(tofSensorList);
    
    // Tof Sensor 0
    if (tofSensorListSize > BACK_RIGHT_SENSOR_INDEX) {
        TofSensor* backRightSensor0 = getTofSensorByIndex(tofSensorList, BACK_RIGHT_SENSOR_INDEX);
        backRightSensor0->orientationRadian = degToRad(BACK_RIGHT_SENSOR_ANGLE_DEGREE);
        backRightSensor0->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int ) (distanceFactor * BACK_RIGHT_SENSOR_DISTANCE_THRESHOLD);
    }
    
    // Tof Sensor 1
    if (tofSensorListSize > BACK_MIDDLE_SENSOR_INDEX) {
        TofSensor* backMiddleSensor1 = getTofSensorByIndex(tofSensorList, BACK_MIDDLE_SENSOR_INDEX);
        backMiddleSensor1->orientationRadian = degToRad(BACK_MIDDLE_SENSOR_ANGLE_DEGREE);
        backMiddleSensor1->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_MIDDLE_SENSOR_DISTANCE_THRESHOLD);
    }

    // Tof Sensor 2
    if (tofSensorListSize > BACK_LEFT_SENSOR_INDEX) {
        TofSensor* backLeftSensor2 = getTofSensorByIndex(tofSensorList, BACK_LEFT_SENSOR_INDEX);
        backLeftSensor2->orientationRadian = degToRad(BACK_LEFT_SENSOR_ANGLE_DEGREE);
        backLeftSensor2->thresholdDistanceMM = BACK_TOF_TO_BACK_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * BACK_LEFT_SENSOR_DISTANCE_THRESHOLD);
    }

    // Tof Sensor 3
    if (tofSensorListSize > FRONT_RIGHT_SENSOR_INDEX) {
        TofSensor* frontRightSensor3 = getTofSensorByIndex(tofSensorList, FRONT_RIGHT_SENSOR_INDEX); 
        frontRightSensor3->orientationRadian = degToRad(FRONT_RIGHT_SENSOR_ANGLE_DEGREE);
        frontRightSensor3->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_RIGHT_SENSOR_DISTANCE_THRESHOLD);
    }
    
    // Tof Sensor 4
    if (tofSensorListSize > FRONT_MIDDLE_SENSOR_INDEX) {
        TofSensor* frontMiddleSensor4 = getTofSensorByIndex(tofSensorList, FRONT_MIDDLE_SENSOR_INDEX);
        frontMiddleSensor4->orientationRadian = degToRad(FRONT_MIDDLE_SENSOR_ANGLE_DEGREE);
        frontMiddleSensor4->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_MIDDLE_SENSOR_DISTANCE_THRESHOLD);
    }
    
    // Tof Sensor 5
    if (tofSensorListSize > FRONT_LEFT_SENSOR_INDEX) {
        TofSensor* frontLeftSensor5 = getTofSensorByIndex(tofSensorList, FRONT_LEFT_SENSOR_INDEX);
        frontLeftSensor5->orientationRadian = degToRad(FRONT_LEFT_SENSOR_ANGLE_DEGREE);
        frontLeftSensor5->thresholdDistanceMM = FRONT_TOF_TO_FRONT_OF_ROBOT_DISTANCE + (unsigned int) (distanceFactor * FRONT_LEFT_SENSOR_DISTANCE_THRESHOLD);
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
        
        // TO DO : Manage if we must use Back Sonar or Front Sonar !
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