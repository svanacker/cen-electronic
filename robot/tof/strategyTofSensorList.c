#include "strategyTofSensorList.h"

#include "../../client/motion/position/clientTrajectory.h"
#include "../../client/motion/simple/clientMotion.h"

#include "../../common/2d/2d.h"
#include "../../common/2d/2dDebug.h"

#include "../../common/math/cenMath.h"

#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../drivers/tof/tofList.h"
#include "../../drivers/tof/tofDetectionUtils.h"

#include "../../robot/robot.h"
#include "../../robot/gameboard/gameboard.h"
#include "../../robot/match/startMatch.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameStrategyMotionHandler.h"
#include "../../drivers/ioExpander/ioExpanderList.h"

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
        
        tofSensor->tofGetDistanceMM(tofSensor);
        // If the last distance is not in the range
        if (isTofDistanceInRange(tofSensor)) {
            tofSensor->detectedCount++;
        }
        else {
            if (tofSensor->detectedCount > 0) {
                tofSensor->detectedCount--;
            }
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