#include "codersDebug.h"

#include "coders.h"
#include "trajectory.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"
#include "../../common/timer/timerConstants.h"

#include "../../robot/kinematics/robotKinematics.h"

#define CODERS_DEVICE_NAME_COLUMN_LENGTH			8
#define CODERS_DEVICE_PULSE_DEC_COLUMN_LENGTH		15
#define CODERS_DEVICE_PULSE_HEX_COLUMN_LENGTH		15
#define CODERS_DEVICE_DISTANCE__COLUMN_LENGTH		10
#define CODERS_DEVICE_LAST_COLUMN_LENGTH            35

static unsigned int coderDebugIterationCount;

/**
* Private.
*/
void printCoderListHeader(OutputStream* outputStream) {
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "coder", CODERS_DEVICE_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "pulse (Dec)", CODERS_DEVICE_PULSE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "pulse (Hex)", CODERS_DEVICE_PULSE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "dist (mm)", CODERS_DEVICE_DISTANCE__COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, CODERS_DEVICE_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);
}


void printCoderDebug(OutputStream* outputStream, char* name, signed long value, float wheelFactor) {
    appendStringTableData(outputStream, name, CODERS_DEVICE_NAME_COLUMN_LENGTH);
    appendDecTableData(outputStream, value, CODERS_DEVICE_PULSE_DEC_COLUMN_LENGTH);
    appendHex6TableData(outputStream, value, CODERS_DEVICE_PULSE_DEC_COLUMN_LENGTH);
    float dist = ((float)value) * wheelFactor;
    appendDecfTableData(outputStream, dist, CODERS_DEVICE_PULSE_DEC_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, CODERS_DEVICE_LAST_COLUMN_LENGTH);
}

void printCoderTable(OutputStream* outputStream) {
    println(outputStream);
    printCoderListHeader(outputStream);
    signed long coderValue0 = getCoderValue(CODER_LEFT);
    signed long coderValue1 = getCoderValue(CODER_RIGHT);

    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getCoderLeftWheelLengthForOnePulse(robotKinematics);
    float rightWheelLengthForOnePulse = getCoderRightWheelLengthForOnePulse(robotKinematics);

    printCoderDebug(outputStream, "left", coderValue0, leftWheelLengthForOnePulse);
    printCoderDebug(outputStream, "right", coderValue1, rightWheelLengthForOnePulse);
    appendTableHeaderSeparatorLine(outputStream);
}

/**
* Callback.
*/
void debugGetWheelCallback(Timer* timer) {
    if (coderDebugIterationCount <= 0) {
        Timer* timer = getTimerByCode(CODERS_TIMER_INDEX);        
        if (timer == NULL) {
            timer->enabled = false;
        }
        return;
    }
    updateTrajectory();
    coderDebugIterationCount--;
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();

    printCoderTable(debugOutputStream);
}

void enableCoderDebug(unsigned int coderDebugIterationCountParam, unsigned int durationInDeciSec) {
    Timer* timer = getTimerByCode(CODERS_TIMER_INDEX);
    coderDebugIterationCount = coderDebugIterationCountParam;
    if (timer == NULL) {
        timer = addTimer(CODERS_TIMER_INDEX, TIME_DIVIDER_10_HERTZ* durationInDeciSec, &debugGetWheelCallback, "CODERS TIMER", NULL);
    }
    timer->enabled = true;
}
