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
#include "../../robot/strategy/gameStrategyMotionHandler.h"
#include "../../robot/strategy/gameStrategyPositionHandler.h"
#include "../../robot/strategy/gameStrategyCollisionHandler.h"
#include "../../robot/strategy/gameTargetList.h"

#include "../../robot/robot.h"
#include "../../robot/tof/strategyTofSensorList.h"
#include "../../robot/gameboard/gameboard.h"

// 2019
#include "../../robot/2019/mainBoard2019.h"
#include "../../robot/2019/gameboard/gameBoardElement2019.h"
#include "../../robot/2019/strategy/score2019.h"
#include "cenDelay.h"

static GameStrategyContext* gameStrategyContext;
static Navigation* navigation;
static GameBoard* gameBoard;

// Forward declaration
void mainBoardDeviceHandleTrajectoryDeviceNotification(const Device* device, const unsigned char commandHeader, InputStream* inputStream);

void mainBoardCommonStrategyAddDevices(unsigned char serialIndex) {
    addLocalDevice(getStrategyDeviceInterface(), getStrategyDeviceDescriptor(gameStrategyContext));
    addLocalDevice(getGameboardDeviceInterface(), getGameboardDeviceDescriptor(gameBoard));
    addLocalDevice(getNavigationDeviceInterface(), getNavigationDeviceDescriptor(navigation));
    addUartRemoteDeviceWithNotification(getTrajectoryDeviceInterface(), serialIndex, &mainBoardDeviceHandleTrajectoryDeviceNotification);
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


void mainBoardDeviceHandleTrajectoryDeviceNotification(const Device* device, const unsigned char commandHeader, InputStream* notificationInputStream) {
    // append(getDebugOutputStreamLogger(), device->deviceInterface->deviceHeader);
    // println(getDebugOutputStreamLogger());
  
    if (device->deviceInterface->deviceHeader == TRAJECTORY_DEVICE_HEADER) {
        if (commandHeader == NOTIFY_TRAJECTORY_CHANGED) {
            updateNewPositionFromNotification(notificationInputStream);
            checkIsSeparator(notificationInputStream);
            readHex(notificationInputStream);
            // enum TrajectoryType trajectoryType = readHex(notificationInputStream);
            // WE DO NOT MODIFY the Trajectory Type, The master data management of 
            // This data must be either the MAIN_BOARD or the MOTOR_BOARD on a MOTION_DEVICE_HEADER 
            // and not on a TRAJECTORY_DEVICE_HEADER
            
            // gameStrategyContext->trajectoryType = trajectoryType;
            
            if (isLoggerDebugEnabled()) {
                appendStringCRLF(getDebugOutputStreamLogger(), "Traj. Dev. Notif. !");
            }
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

void mainBoardDeviceHandleMotionDeviceNotification(const Device* device, const unsigned char commandHeader, InputStream* notificationInputStream) {
    if (device->deviceInterface->deviceHeader == MOTION_DEVICE_HEADER) {
        if (
                commandHeader == NOTIFY_MOTION_STATUS_FAILED
                || commandHeader == NOTIFY_MOTION_STATUS_MOVING
                || commandHeader == NOTIFY_MOTION_STATUS_OBSTACLE
                || commandHeader == NOTIFY_MOTION_STATUS_REACHED
                || commandHeader == NOTIFY_MOTION_STATUS_BLOCKED
                || commandHeader == NOTIFY_MOTION_STATUS_SHOCKED) {
            updateNewPositionFromNotification(notificationInputStream);
            // FAKE DATA To Align with TrajectoryDevice
            checkIsSeparator(notificationInputStream);
            checkIsChar(notificationInputStream, 'F');
            
            gameStrategyContext->trajectoryType = TRAJECTORY_TYPE_NONE;

            if (isLoggerDebugEnabled()) {
                appendStringCRLF(getDebugOutputStreamLogger(), "Motion Dev. Notif. !");
            }
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

GameStrategyContext* mainBoardCommonStrategyMainInitDrivers(RobotConfig* robotConfig) {
    // 2019
    navigation = initNavigation2019();
    EndMatch* endMatch = mainBoardCommonMatchGetEndMatch();
    TofSensorList* tofSensorList = mainBoardCommonTofGetTofSensorList();
    ServoList* servoList = mainBoardCommonGetServoList();

    gameStrategyContext = initGameStrategyContext2019(robotConfig, endMatch, tofSensorList, servoList);
    gameBoard = initGameBoard2019(gameStrategyContext);
    
    return gameStrategyContext;
}

void mainBoardCommonStrategyMainEndInit(void) {      
    // Update this on the MOTOR BOARD to synchronize the position !
    appendStringLN(getDebugOutputStreamLogger(), "Update Robot Position MainBoard->Motor Board");
    updateRobotPositionFromMainBoardToMotorBoard(gameStrategyContext);

    appendStringLN(getDebugOutputStreamLogger(), "mainBoardCommonStrategyMainEndInit2019");
    mainBoardCommonStrategyMainEndInit2019(gameStrategyContext);
}


void mainBoardCommonStrategyHandleStreamInstruction(void) {
    StartMatch* startMatch = mainBoardCommonMatchGetStartMatch();

    // Tof / Collision management
    TofSensorList* tofSensorList = mainBoardCommonTofGetTofSensorList();
    handleTofSensorList(gameStrategyContext, startMatch, tofSensorList, gameBoard);
    
    // Motion Management
    updateIfNeededRobotPositionFromMotorBoardToMainBoard(gameStrategyContext);
}

void mainBoardCommonStrategyMainLoop(void) {
    StartMatch* startMatch = mainBoardCommonMatchGetStartMatch();
    EndMatch* endMatch = mainBoardCommonMatchGetEndMatch();
    
    mainBoardCommonMatchLoopUntilStart();

    while (true) {
        if (!startMatch->matchHandleInstructionFunction(startMatch)) {
            break;
        }
        
        // Protection against the start before the match
        if (gameStrategyContext->loopTargetAndActions) {
            nextTargetOrNextStep(gameStrategyContext);
        }
        // After each instruction => Export the score to endMatch Device
        if (showEndAndScoreIfNeeded(endMatch, getAlwaysOutputStreamLogger())) {
            break;
        }
    }
}