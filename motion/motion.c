#include <math.h>
#include "motion.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../common/commons.h"

#include "../common/delay/cenDelay.h"

#include "../common/error/error.h"

#include "../common/io/buffer.h"
#include "../common/io/outputStream.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

#include "../common/math/cenMath.h"

#include "../device/motion/simple/motionDevice.h"

#include "../motion/simple/simpleMotion.h"

#include "pid/detectedMotionType.h"
#include "pid/pid.h"
#include "pid/pidMotion.h"

#include "position/coders.h"
#include "position/trajectory.h"

enum DetectedMotionType handleInstructionAndMotion(PidMotion* pidMotion) {
    updateCoders();
    updateTrajectory();

    // OPTIONAL
    // checkCoders();

    // MANDATORY

    enum DetectedMotionType result = updateMotors(pidMotion);

    OutputStream* outputStream = NULL;
	PidMotionDefinition* currentMotionDefinition = pidMotionGetCurrentMotionDefinition(pidMotion);
	if (currentMotionDefinition != NULL) {
		outputStream = currentMotionDefinition->notificationOutputStream;
	}
	else {
		writeError(MOTION_DEFINITION_NO_CURRENT_DEFINITION);
	}

    if (result == DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH) {
        // don't do anything
    }
    if (result == DETECTED_MOTION_TYPE_POSITION_TO_MAINTAIN) {
        // does not end
    } else if (result == DETECTED_MOTION_TYPE_POSITION_IN_PROGRESS) {
        // don't do anything, wait
    } else if (result == DETECTED_MOTION_TYPE_POSITION_REACHED) {
        notifyReached(outputStream);
        stopPosition(pidMotion, true, outputStream);
    } else if (result == DETECTED_MOTION_TYPE_POSITION_BLOCKED_WHEELS) {
        notifyFailed(outputStream);
        stopPosition(pidMotion, true, outputStream);
    } else if (result == DETECTED_MOTION_TYPE_POSITION_OBSTACLE) {
        notifyObstacle(outputStream);
        stopPosition(pidMotion, true, outputStream);
    }
	if (outputStream != NULL) {
		outputStream->flush(outputStream);
	}
	
    return result;
}

enum DetectedMotionType handleAndWaitFreeMotion(PidMotion* pidMotion) {
    enum DetectedMotionType result = DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH;
    while (true) {
        result = handleInstructionAndMotion(pidMotion);
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

void handleAndWaitMSec(PidMotion* pidMotion, unsigned long delayMs) {
    unsigned long DELAY = 10;
    unsigned long counter;
    for (counter = 0; counter < delayMs; counter += DELAY) {
        delaymSec(DELAY);
        handleInstructionAndMotion(pidMotion);
    }
}
