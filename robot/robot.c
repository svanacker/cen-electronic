#include "robot.h"


#include "../common/commons.h"
#include "../common/2d/2d.h"
#include "../common/delay/delay30F.h"

#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/reader.h"
#include "../common/io/stream.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

#include "../drivers/driver.h"
#include "../drivers/driverList.h"

#include "../drivers/motion/motionDriver.h"

#include "../drivers/dispatcher/driverDataDispatcher.h"
#include "../drivers/dispatcher/driverDataDispatcherList.h"

#include "../device/motion/simple/motionDeviceInterface.h"
#include "../robot/match/endMatchDetectorDevice.h"

#include "../main/motorBoard/motorBoard.h"

// ROBOT POSITIONG
// x / y
static int robotPositionX;
static int robotPositionY;

// orientation in ddeg
static int robotAngle;

/** Global variable to know if the robot must stop.*/
static unsigned int robotMustStop = FALSE;

static unsigned int timeAtLastCollision = 0;

unsigned int isRobotMustStop() {
    return robotMustStop;
}

void updateRobotPosition(int x, int y, int angle) {
	robotPositionX = x;
	robotPositionY = y;
	robotAngle = angle;
}

void setRobotMustStop(unsigned int value) {
    // Comment this if we want that robot doesn't stop on collision
    robotMustStop = value;
}

void stopRobot(void) {
    motionDriverStop();

    // notifyEnd();
    appendString(getOutputStreamLogger(WARNING), "Robot stopped");
}

void stopRobotObstacle(void) {
    int currentTime = getCurrentTimeInSecond();
    appendString(getOutputStreamLogger(WARNING), "Current Time=");
    appendDec(getOutputStreamLogger(WARNING), currentTime);
    appendString(getOutputStreamLogger(WARNING), " secs\n");

    if (currentTime > timeAtLastCollision + TIME_FOR_OBSTACLE_NEW_NOTIFICATION) {
        timeAtLastCollision = currentTime;
        motionDriverObstacle();

        // notifyEnd();
        appendString(getOutputStreamLogger(WARNING), "Robot stopped(Obstacle)\n");
    } else {
        appendString(getOutputStreamLogger(WARNING), "Wait for new notification \n");
    }

}
