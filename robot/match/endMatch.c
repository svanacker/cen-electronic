#include "endMatch.h"

#include <stdlib.h>
#include <stdint.h>

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"
#include "../../common/timer/timerConstants.h"

#include "../../drivers/lcd/lcd.h"

#include "../../common/log/logger.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/error/error.h"


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
    if (endMatch == NULL) {
        writeError(ROBOT_END_MATCH_NULL);
        return;
    }
    endMatch->endMatchDetectorDeviceTimer->enabled = true;
    endMatch->currentTimeInSecond = 0;
}

void resetStartMatch(EndMatch* endMatch) {
    if (endMatch == NULL) {
        writeError(ROBOT_END_MATCH_NULL);
        return;
    }
    endMatch->endMatchDetectorDeviceTimer->enabled = false;
    endMatch->currentTimeInSecond = 0;
}

unsigned int matchEndGetRemainingTime(EndMatch* endMatch) {
    if (endMatch->doNotEnd) {
        return INT32_MAX;
    }
    if (isMatchFinished(endMatch)) {
        return 0;
    }
    else {
        return endMatch->matchDurationInSecond - endMatch->currentTimeInSecond;
    }
}

void showRemainingTime(EndMatch* endMatch, OutputStream* outputStream) {
    if (isMatchFinished(endMatch)) {
        return;
    }
    clearScreen();
    appendString(outputStream, "Remain. Time:");
    appendDec(outputStream, matchEndGetRemainingTime(endMatch));
    appendStringLN(outputStream, " s");
}

void showEndAndScore(EndMatch* endMatch, OutputStream* outputStream) {
    clearScreen();
    appendString(outputStream, "End : Score = ");
    appendDec(outputStream, endMatch->scoreToShow);
    appendStringLN(outputStream, " pts");
}

bool showEndAndScoreIfNeeded(EndMatch* endMatch, OutputStream* outputStream) {
    // Only show if the match is finished
    if (!isMatchFinished(endMatch)) {
        return false;
    }
    // Do not show x times the end of the match
    if (endMatch->endOfMatchNotified) {
        return false;
    }

    showEndAndScore(endMatch, outputStream);
    endMatch->endOfMatchNotified = true;

    return true;
}

int getCurrentTimeInSecond(EndMatch* endMatch) {
    return endMatch->currentTimeInSecond;
}

bool isMatchFinished(EndMatch* endMatch) {
    if (endMatch->doNotEnd) {
        return false;
    }
    if (!endMatch->endMatchDetectorDeviceTimer->enabled) {
        appendStringLN(getErrorOutputStreamLogger(), "You must enable end Match Timer before");
    }
    bool result = endMatch->currentTimeInSecond >= endMatch->matchDurationInSecond;

    return result;
}