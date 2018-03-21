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

/**
 * @private
 * If we have a next position to reach, stop the current motion, initialize the next motion and switch to it
 * @param pidMotion
 */
void switchToNextMotionDefinitionIfAny(PidMotion* pidMotion, PidMotionDefinition* currentMotionDefinition) {
    if (currentMotionDefinition == NULL) {
        return;
    }
    currentMotionDefinition->state = PID_MOTION_DEFINITION_STATE_ENDED;
    // There is the current motion definition, and the next one (so we test that there is >= 2)
    int elementCount = getPidMotionElementsCount(pidMotion);
    if (elementCount >= 1) {
        pidMotionReadMotionDefinition(pidMotion, false);
    }
}

void handleInstructionAndMotion(PidMotion* pidMotion) {
    updateCoders();
    updateTrajectory();

	// Get the current Motion Definition
    PidMotionDefinition* currentMotionDefinition = pidMotionGetCurrentMotionDefinition(pidMotion);
    if (currentMotionDefinition == NULL) {
        return;
    }
    if (currentMotionDefinition->state == PID_MOTION_DEFINITION_STATE_UNDEFINED) {
        return;
    }
    // Avoid to handle a motion definition which is ended
    if (currentMotionDefinition->state == PID_MOTION_DEFINITION_STATE_ENDED) {
        return;
    }
    // Init the motion Definition
    if (currentMotionDefinition->state == PID_MOTION_DEFINITION_STATE_SET) {
        // Update trajectory before clearing coders
        updateTrajectoryAndClearCoders();

        // resets all current values
        clearPidTime();
        clearPidComputationValues(&(pidMotion->computationValues));
        
        currentMotionDefinition->state = PID_MOTION_DEFINITION_STATE_ACTIVE; 
    }

    // OPTIONAL
    // checkCoders();

    // MANDATORY
    updateMotorsAndDetectedMotionType(pidMotion);
    enum DetectedMotionType motionType = pidMotion->computationValues.detectedMotionType;

    OutputStream* outputStream = NULL;
	if (currentMotionDefinition != NULL) {
		outputStream = currentMotionDefinition->notificationOutputStream;
	}
	else {
		writeError(MOTION_DEFINITION_NO_CURRENT_DEFINITION);
	}

    if (motionType == DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH) {
        // don't do anything
    }
    if (motionType == DETECTED_MOTION_TYPE_POSITION_TO_MAINTAIN) {
        // does not end
    } else if (motionType == DETECTED_MOTION_TYPE_POSITION_IN_PROGRESS) {
        // don't do anything, wait
    } else if (motionType == DETECTED_MOTION_TYPE_POSITION_REACHED) {
        notifyReached(outputStream);
        stopPosition(pidMotion, false, outputStream);
        switchToNextMotionDefinitionIfAny(pidMotion, currentMotionDefinition);
    }
    else if (motionType == DETECTED_MOTION_TYPE_POSITION_SHOCK_WHEELS) {
        notifyShocked(outputStream);
        stopPosition(pidMotion, false, outputStream);
        switchToNextMotionDefinitionIfAny(pidMotion, currentMotionDefinition);
    } else if (motionType == DETECTED_MOTION_TYPE_POSITION_BLOCKED_WHEELS) {
        notifyBlocked(outputStream);
        stopPosition(pidMotion, false, outputStream);
        switchToNextMotionDefinitionIfAny(pidMotion, currentMotionDefinition);
    } else if (motionType == DETECTED_MOTION_TYPE_POSITION_OBSTACLE) {
        notifyObstacle(outputStream);
        stopPosition(pidMotion, true, outputStream);
        switchToNextMotionDefinitionIfAny(pidMotion, currentMotionDefinition);
    }
	if (outputStream != NULL) {
		outputStream->flush(outputStream);
	}
}

void handleAndWaitFreeMotion(PidMotion* pidMotion) {
    while (true) {
        handleInstructionAndMotion(pidMotion);
        enum DetectedMotionType motionType = pidMotion->computationValues.detectedMotionType; 
        // POSITION_BLOCKED_WHEELS is not necessary because we block the position after
        if (motionType == DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH 
         || motionType == DETECTED_MOTION_TYPE_POSITION_TO_MAINTAIN
         || motionType == DETECTED_MOTION_TYPE_POSITION_OBSTACLE) {
            // if (value == NO_POSITION_TO_REACH || value == POSITION_OBSTACLE) {
            appendString(getDebugOutputStreamLogger(), "handleAndWaitFreeMotion->break=");
            appendDec(getDebugOutputStreamLogger(), motionType);
            break;
        }
    }
}

void handleAndWaitMSec(PidMotion* pidMotion, unsigned long delayMs) {
    unsigned long DELAY = 10;
    unsigned long counter;
    for (counter = 0; counter < delayMs; counter += DELAY) {
        delaymSec(DELAY);
        handleInstructionAndMotion(pidMotion);
    }
}
