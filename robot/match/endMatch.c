#include "endMatch.h"

#include <stdlib.h>

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"
#include "../../common/timer/timerConstants.h"

#include "../../common/log/logger.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"


// SPECIFIC PART

void endMatchDetectorCallbackFunc(Timer* timer) {
    EndMatch* endMatch = (EndMatch*)timer->object;
    if (endMatch->endMatchDetectorDeviceTimer->enabled) {
        endMatch->currentTimeInSecond++;
    }
}

void initEndMatch(EndMatch* endMatch, RobotConfig* robotConfig, unsigned int matchDurationInSecond) {
    endMatch->robotConfig = robotConfig;
    endMatch->currentTimeInSecond = 0;
    endMatch->matchDurationInSecond = matchDurationInSecond;
    endMatch->doNotEnd = isConfigSet(robotConfig, CONFIG_DO_NOT_END);
    endMatch->endMatchDetectorDeviceTimer = addTimer(END_MATCH_DETECTOR_TIMER_CODE,
        TIME_DIVIDER_1_HERTZ,
        endMatchDetectorCallbackFunc,
        "END MATCH TIMER",
        (int*) endMatch);
}

void markStartMatch(EndMatch* endMatch) {
    endMatch->endMatchDetectorDeviceTimer->enabled = true;
    endMatch->currentTimeInSecond = 0;
}

void resetStartMatch(EndMatch* endMatch) {
    endMatch->endMatchDetectorDeviceTimer->enabled = false;
    endMatch->currentTimeInSecond = 0;
}

void showEnd(EndMatch* endMatch, OutputStream* outputStream) {
    appendString(outputStream, "End of match");
}

int getCurrentTimeInSecond(EndMatch* endMatch) {
    return endMatch->currentTimeInSecond;
}

bool isEnd(EndMatch* endMatch) {
    if (endMatch->doNotEnd) {
        return false;
    }
    if (!endMatch->endMatchDetectorDeviceTimer->enabled) {
        appendString(getErrorOutputStreamLogger(), "You must call startMatch before");
    }
    bool result = endMatch->currentTimeInSecond >= endMatch->matchDurationInSecond;

    return result;
}