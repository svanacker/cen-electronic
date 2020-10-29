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

#include "../../motion/simulation/motionSimulation.h"

#include "../../robot/robot.h"
#include "../../robot/gameboard/gameboard.h"
#include "../../robot/match/startMatch.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameStrategyMotionHandler.h"
#include "../../drivers/ioExpander/ioExpanderList.h"

void handleTofSensorList(GameStrategyContext* gameStrategyContext, StartMatch* startMatch, TofSensorList* tofSensorList, GameBoard* gameBoard) {
    // TODO : Reactivate code
    /*
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
    */
    unsigned int index;
    enum TrajectoryType trajectoryType = gameStrategyContext->trajectoryType;
    // Do not beep when no move, or rotation (could not hurt something when rotating)
    if (trajectoryType == TRAJECTORY_TYPE_NONE || trajectoryType == TRAJECTORY_TYPE_ROTATION) {
        tofSensorListBeep(tofSensorList, false);
//        return;
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

        // LED MANAGEMENT
        unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);
        unsigned char ledArrayIndex = tofSensor->ledArrayIndex;
        unsigned char ledIndex = tofSensor->ledIndex;
        LedArray* ledArray = NULL;
        if (ledArrayIndex == 0) {
            ledArray = tofSensorList->ledArray0;
        }
        else if (ledArrayIndex == 1) {
            ledArray = tofSensorList->ledArray1;
        }
        if (ledArray != NULL) {
            setLedColorAsDistance(ledArray, ledIndex, distance / 10);
        }
        
        // If the last distance is not in the range
        if (isTofDistanceInRange(tofSensor)) {
            tofSensor->detectedCount++;
        } else {
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

        // We must know if it's in the gameboard or in a area where we could have a collision
        if (isPointInTheCollisionArea(gameBoard, &detectedPoint)) {

            // motionDriverStop();
            if (gameStrategyContext->simulateMove) {
#ifdef PC_COMPILER   
                simulateMotionCancel(gameStrategyContext);
#endif
            } else {
                motionDriverCancel();
            }
            // We beep after to gain some ms !
            tofSensorListBeep(tofSensorList, detected);
            PathData* currentPath = gameStrategyContext->currentPath;
            if (currentPath != NULL) {
                // Good value to find
                updateObstacleCostIfObstacle(currentPath);
            }

            /*
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
            updateStrategyContextTrajectoryType(gameStrategyContext, TRAJECTORY_TYPE_NONE);

            tofSensorListResetDetectionCount(tofSensorList);

            // TODO 2018 : handleObstacle(gameStrategyContext);
            break;
            */
        }
    }
}