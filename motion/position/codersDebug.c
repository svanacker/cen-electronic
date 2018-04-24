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

#define CODERS_DEVICE_INDEX_COLUMN_LENGTH			    8
// Dec
#define CODERS_DEVICE_LEFT_PULSE_DEC_COLUMN_LENGTH		15
#define CODERS_DEVICE_RIGHT_PULSE_DEC_COLUMN_LENGTH		15
// Distance
#define CODERS_DEVICE_LEFT_DISTANCE_COLUMN_LENGTH		15
#define CODERS_DEVICE_RIGHT_DISTANCE_COLUMN_LENGTH		15
// Hex
#define CODERS_DEVICE_LEFT_PULSE_HEX_COLUMN_LENGTH		15
#define CODERS_DEVICE_RIGHT_PULSE_HEX_COLUMN_LENGTH		15

#define CODERS_DEVICE_LAST_COLUMN_LENGTH                0

static CoderDataHistory coderDataHistory;

/**
* Private.
*/
void printCoderListHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    // First Line
    appendStringHeader(outputStream, "Index", CODERS_DEVICE_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Left", CODERS_DEVICE_LEFT_PULSE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Right", CODERS_DEVICE_RIGHT_PULSE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Left", CODERS_DEVICE_LEFT_DISTANCE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Right", CODERS_DEVICE_RIGHT_DISTANCE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Left", CODERS_DEVICE_LEFT_PULSE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Right", CODERS_DEVICE_RIGHT_PULSE_HEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, CODERS_DEVICE_LAST_COLUMN_LENGTH);

    // Second Line
    appendStringHeader(outputStream, "", CODERS_DEVICE_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Pulse (Dec)", CODERS_DEVICE_LEFT_PULSE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Pulse (Dec)", CODERS_DEVICE_RIGHT_PULSE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm (Dec)", CODERS_DEVICE_LEFT_DISTANCE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm (Dec)", CODERS_DEVICE_RIGHT_DISTANCE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Pulse (Hex)", CODERS_DEVICE_LEFT_PULSE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Pulse (Hex)", CODERS_DEVICE_RIGHT_PULSE_HEX_COLUMN_LENGTH);

    appendEndOfTableColumn(outputStream, CODERS_DEVICE_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);
}

/**
 * @private
 */
void printCoderDebug(OutputStream* outputStream, unsigned int index, signed long leftValue, float leftWheelFactor, signed long rightValue, float rightWheelFactor) {
    appendDecTableData(outputStream, index, CODERS_DEVICE_INDEX_COLUMN_LENGTH);

    // Pulse
    appendDecTableData(outputStream, leftValue, CODERS_DEVICE_LEFT_PULSE_DEC_COLUMN_LENGTH);
    appendDecTableData(outputStream, rightValue, CODERS_DEVICE_RIGHT_PULSE_DEC_COLUMN_LENGTH);

    // Distance
    appendDecfTableData(outputStream, ((float)leftValue) * leftWheelFactor, CODERS_DEVICE_LEFT_DISTANCE_COLUMN_LENGTH);
    appendDecfTableData(outputStream, ((float)rightValue) * rightWheelFactor, CODERS_DEVICE_RIGHT_DISTANCE_COLUMN_LENGTH);

    // Pulse (hex)
    appendHex6TableData(outputStream, leftValue, CODERS_DEVICE_LEFT_PULSE_HEX_COLUMN_LENGTH);
    appendHex6TableData(outputStream, rightValue, CODERS_DEVICE_RIGHT_PULSE_HEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, CODERS_DEVICE_LAST_COLUMN_LENGTH);
}

void printCurrentCoderTable(OutputStream* outputStream) {
    // We get the coder Value first to avoid to be interrupt by sending uart chars for example
    updateCoders();

    signed long leftCoderValue = getCoderValue(CODER_LEFT);
    signed long rightCoderValue = getCoderValue(CODER_RIGHT);
    printCoderListHeader(outputStream);

    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getCoderLeftWheelLengthForOnePulse(robotKinematics);
    float rightWheelLengthForOnePulse = getCoderRightWheelLengthForOnePulse(robotKinematics);

    printCoderDebug(outputStream, 0, leftCoderValue, leftWheelLengthForOnePulse, rightCoderValue, rightWheelLengthForOnePulse);
    appendTableHeaderSeparatorLine(outputStream);
}

/**
 * @private.
 */
void clearCoderHistoryDebug(void) {
    unsigned int i;
    coderDataHistory.writeIndex = 0;
    coderDataHistory.sampleToAcquire = 0;
    for (i = 0; i < CODER_DEBUG_HISTORY_COUNT; i++) {
        CoderData* coderData = &(coderDataHistory.coderHistory[i]);
        coderData->left = 0L;
        coderData->right = 0L;
    }
}

// TIMER MANAGEMENT to get CODER VALUE

bool acquireNextCoderSample() {
    if (coderDataHistory.sampleToAcquire <= 0) {
        return false;
    }
    coderDataHistory.sampleToAcquire--;
    CoderData* coderData = &(coderDataHistory.coderHistory[coderDataHistory.writeIndex]);

    coderData->left = getCoderValue(CODER_LEFT);
    coderData->right = getCoderValue(CODER_RIGHT);
    coderDataHistory.writeIndex++;
    return true;
}

/**
* Callback.
*/
void debugGetWheelCallback(Timer* timer) {
    // If we don't need to acquire anymore
    if (!acquireNextCoderSample()) {
        Timer* timer = getTimerByCode(CODERS_TIMER_CODE);
        // we disable the timer
        if (timer == NULL) {
            timer->enabled = false;
        }
    }
}

void enableCoderSampleRecording(unsigned int sampleCountParam, unsigned int samplingRateMilliSeconds) {
    clearCoderHistoryDebug();
    Timer* timer = getTimerByCode(CODERS_TIMER_CODE);
    if (sampleCountParam < CODER_DEBUG_HISTORY_COUNT) {
        coderDataHistory.sampleToAcquire = sampleCountParam;
    }
    else {
        coderDataHistory.sampleToAcquire = CODER_DEBUG_HISTORY_COUNT;
    }
    unsigned long timeDiviser = TIME_DIVIDER_1000_HERTZ * samplingRateMilliSeconds;
    if (timer == NULL) {
        timer = addTimer(CODERS_TIMER_CODE, timeDiviser, &debugGetWheelCallback, "CODERS TIMER", NULL);
    }
    else {
        timer->timeDiviser = timeDiviser;
    }
    timer->enabled = true;
}

void printSampleCoderHistory(OutputStream* outputStream) {
    printCoderListHeader(outputStream);

    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getCoderLeftWheelLengthForOnePulse(robotKinematics);
    float rightWheelLengthForOnePulse = getCoderRightWheelLengthForOnePulse(robotKinematics);

    unsigned int i;
    for (i = 0; i < coderDataHistory.writeIndex; i++) {
        CoderData coderData = coderDataHistory.coderHistory[i];
        printCoderDebug(outputStream, i, coderData.left, leftWheelLengthForOnePulse, coderData.right, rightWheelLengthForOnePulse);
    }
    appendTableHeaderSeparatorLine(outputStream);
}
