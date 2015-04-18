#include <math.h>
#include "motion.h"

#include "../common/commons.h"

#include "../common/delay/cenDelay.h"

#include "../common/io/buffer.h"
#include "../common/io/outputStream.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

#include "../common/math/cenMath.h"

#include "pid/pid.h"

#include "position/coders.h"
#include "position/trajectory.h"

enum DetectedMotionType handleInstructionAndMotion(void) {
    updateCoders();
    updateTrajectory();

    // OPTIONAL
    // checkCoders();

    // MANDATORY

    enum DetectedMotionType result = updateMotors();

    /* TODO https://github.com/svanacker/cen-electronic/issues/28
    Buffer* buffer = getI2CSlaveOutputBuffer();
    OutputStream* outputStream = getOutputStream(buffer);
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();

    if (value == NO_POSITION_TO_REACH) {
        // don't do anything
    }
    if (value == POSITION_TO_MAINTAIN) {
        // does not end
    } else if (value == POSITION_IN_PROGRESS) {
        // don't do anything, wait
    } else if (value == POSITION_REACHED) {
        notifyReached(outputStream);
        notifyReached(debugOutputStream);
        stopPosition(true);
    } else if (value == POSITION_BLOCKED_WHEELS) {
        notifyFailed(outputStream);
        notifyFailed(debugOutputStream);
        stopPosition(true);
    } else if (value == POSITION_OBSTACLE) {
        notifyObstacle(outputStream);
        stopPosition(true);
    }
    */
    return result;
}

enum DetectedMotionType handleAndWaitFreeMotion(void) {
    enum DetectedMotionType result = DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH;
    while (true) {
        result = handleInstructionAndMotion();
        // POSITION_BLOCKED_WHEELS is not necessary because we block the position after
        if (result == DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH || result == DETECTED_MOTION_TYPE_POSITION_TO_MAINTAIN || result == DETECTED_MOTION_TYPE_POSITION_OBSTACLE) {
            // if (value == NO_POSITION_TO_REACH || value == POSITION_OBSTACLE) {
            appendString(getDebugOutputStreamLogger(), "handleAndWaitFreeMotion->break=");
            appendDec(getDebugOutputStreamLogger(), result);
            break;
        }
    }
    return result;
}

void handleAndWaitMSec(unsigned long delayMs) {
    unsigned long DELAY = 10;
    unsigned long counter;
    for (counter = 0; counter < delayMs; counter += DELAY) {
        delaymSec(DELAY);
        handleInstructionAndMotion();
    }
}
