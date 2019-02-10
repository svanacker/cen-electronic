#include "mainBoardCommonStrategy.h"
#include "mainBoardCommonTof.h"
#include "mainBoardCommonMatch.h"

#include "../../common/2d/2d.h"
#include "../../common/error/error.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"

#include "../../device/deviceConstants.h"

#include "../../device/motion/position/trajectoryDeviceInterface.h"

#include "../../robot/strategy/gameStrategyContext.h"

#include "../../device/deviceList.h"

// Motion
#include "../../device/motion/pid/pidDeviceInterface.h"
#include "../../device/motion/position/codersDeviceInterface.h"
#include "../../device/motion/position/trajectoryDeviceInterface.h"
#include "../../device/motion/simple/motionDeviceInterface.h"
#include "../../device/motion/extended/extendedMotionDeviceInterface.h"

#include "../../device/gameboard/gameboardDeviceInterface.h"
#include "../../device/gameboard/gameboardDevice.h"

// Navigation
#include "../../device/navigation/navigationDevice.h"
#include "../../device/navigation/navigationDeviceInterface.h"

// Strategy
#include "../../device/strategy/strategyDevice.h"
#include "../../device/strategy/strategyDeviceInterface.h"

// Trajectory
#include "../../device/motion/position/trajectoryDeviceInterface.h"
#include "../../device/motion/position/trajectoryDevice.h"

// MOTION
#include "../../motion/simple/simpleMotion.h"

// NAVIGATION
#include "../../navigation/navigation.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/gameboard/gameboardElementList.h"

#include "../../robot/strategy/teamColor.h"
#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameTargetList.h"

#include "../../robot/robot.h"
#include "../../robot/tof/strategyTofSensorList.h"
#include "../../robot/gameboard/gameboard.h"

// 2019
#include "../../robot/2019/mainBoard2019.h"
#include "../../robot/2019/gameBoardElement2019.h"
#include "../../robot/2019/score2019.h"

static GameStrategyContext* gameStrategyContext;
static Navigation* navigation;
static GameBoard* gameBoard;

// Forward declaration
void mainBoardDeviceHandleTrajectoryDeviceNotification(const Device* device, const char commandHeader, InputStream* inputStream);

void mainBoardCommonStrategyAddDevices(unsigned char serialIndex) {
    addLocalDevice(getStrategyDeviceInterface(), getStrategyDeviceDescriptor(gameStrategyContext));
    addLocalDevice(getGameboardDeviceInterface(), getGameboardDeviceDescriptor(gameBoard));
    addLocalDevice(getNavigationDeviceInterface(), getNavigationDeviceDescriptor(navigation));
    addUartRemoteDeviceWithNotification(getTrajectoryDeviceInterface(), serialIndex, &mainBoardDeviceHandleTrajectoryDeviceNotification);
//    addLocalDevice(getStrategy2018DeviceInterface(), getStrategy2018DeviceDescriptor(&distributor));
}

void updateNewPositionFromNotification(InputStream* inputStream) {
    float x = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
    checkIsSeparator(inputStream);
    float y = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
    checkIsSeparator(inputStream);
    float angleDegree = readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION);
    
    gameStrategyContext->robotPosition->x = x;
    gameStrategyContext->robotPosition->y = y;
    gameStrategyContext->robotAngleRadian = degToRad(angleDegree);
    
    /*
    printPoint(getDebugOutputStreamLogger(), gameStrategyContext->robotPosition, "");
    println(getDebugOutputStreamLogger());
    */
}


void mainBoardDeviceHandleTrajectoryDeviceNotification(const Device* device, const char commandHeader, InputStream* inputStream) {
    // append(getDebugOutputStreamLogger(), device->deviceInterface->deviceHeader);
    // println(getDebugOutputStreamLogger());
  
    if (device->deviceInterface->deviceHeader == TRAJECTORY_DEVICE_HEADER) {
        if (commandHeader == NOTIFY_TRAJECTORY_CHANGED) {
            /*
            append(getDebugOutputStreamLogger(), commandHeader);
            println(getDebugOutputStreamLogger());
            */
            updateNewPositionFromNotification(inputStream);
            checkIsSeparator(inputStream);
            enum TrajectoryType trajectoryType = readHex(inputStream);
            gameStrategyContext->trajectoryType = trajectoryType;
        }
        else {
            writeError(NOTIFICATION_BAD_DEVICE_COMMAND_HANDLER_NOT_HANDLE);
            appendString(getAlwaysOutputStreamLogger(), "header");
            append(getAlwaysOutputStreamLogger(), commandHeader);
            println(getAlwaysOutputStreamLogger());
        }
    }
    else {
        writeError(NOTIFICATION_BAD_DEVICE);
    }
}

void mainBoardDeviceHandleMotionDeviceNotification(const Device* device, const char commandHeader, InputStream* inputStream) {
    if (device->deviceInterface->deviceHeader == MOTION_DEVICE_HEADER) {
        if (
                commandHeader == NOTIFY_MOTION_STATUS_FAILED
                || commandHeader == NOTIFY_MOTION_STATUS_MOVING
                || commandHeader == NOTIFY_MOTION_STATUS_OBSTACLE
                || commandHeader == NOTIFY_MOTION_STATUS_REACHED
                || commandHeader == NOTIFY_MOTION_STATUS_BLOCKED
                || commandHeader == NOTIFY_MOTION_STATUS_SHOCKED) {
            updateNewPositionFromNotification(inputStream);
            // FAKE DATA To Align with TrajectoryDevice
            checkIsSeparator(inputStream);
            checkIsChar(inputStream, 'F');
            
            gameStrategyContext->trajectoryType = TRAJECTORY_TYPE_NONE;
            // To know if we have reached the target
            /*
            appendStringLN(getDebugOutputStreamLogger(), "M:");
            */
            // handleNotificationInstructionCounter(gameStrategyContext, commandHeader); -> 2018
        }
        else {
            writeError(NOTIFICATION_BAD_DEVICE_COMMAND_HANDLER_NOT_HANDLE);
            appendString(getAlwaysOutputStreamLogger(), "header");
            append(getAlwaysOutputStreamLogger(), commandHeader);
            println(getAlwaysOutputStreamLogger());
        }
    }
    else {
        writeError(NOTIFICATION_BAD_DEVICE);
    }
}

void mainBoardCommonStrategyMainInitDrivers(RobotConfig* robotConfig) {
    // 2019
    navigation = initNavigation2019();
    EndMatch* endMatch = mainBoardCommonMatchGetEndMatch();
    TofSensorList* tofSensorList = mainBoardCommonTofGetTofSensorList();

    gameStrategyContext = initGameStrategyContext2019(robotConfig, endMatch, tofSensorList);
    gameBoard = initGameBoard2019(gameStrategyContext);
}

void mainBoardCommonStrategyMainEndInit(void) {      
    // Update this on the MOTOR BOARD to be synchronized !
    updateMotorBoardRobotPosition(gameStrategyContext);
    
    // initInstructionCounter(gameStrategyContext); -> 2018

    // Just after, we could increment the counter
    // startInstructionCounter(gameStrategyContext); -> 2018
}


void mainBoardCommonStrategyHandleStreamInstruction(void) {
    StartMatch* startMatch = mainBoardCommonMatchGetStartMatch();
    TofSensorList* tofSensorList = mainBoardCommonTofGetTofSensorList();
    
    handleTofSensorList(gameStrategyContext, startMatch, tofSensorList, gameBoard);
//    handleNextInstructionCounter(gameStrategyContext); -> 2018
}

void mainBoardCommonStrategyMainLoop(void) {
    StartMatch* startMatch = mainBoardCommonMatchGetStartMatch();
    EndMatch* endMatch = mainBoardCommonMatchGetEndMatch();

    while (1) {
        if (!startMatch->matchHandleInstructionFunction(startMatch)) {
            break;
        }
        // After each instruction => Export the score to endMatch Device
        endMatch->scoreToShow = gameStrategyContext->score;
        if (showEndAndScoreIfNeeded(endMatch, getAlwaysOutputStreamLogger())) {
            break;
        }
    }
}