#include "opponentRobot.h"

#include "../../common/commons.h"
#include "../../common/2d/2d.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../drivers/beacon/beaconReceiverDriver.h"
#include "../../drivers/strategy/strategyDriver.h"

/** The last OpponentRobotPosition. */
static Point lastOpponentRobotPosition;
static bool mustAskLastOpponentRobotPosition;

/** To distinguish every Timer. */
#define OPPONENT_ROBOT_TIMER_INDEX            5

void opponentRobotCallbackFunc(Timer* timer) {
    mustAskLastOpponentRobotPosition = true;
}

Point* getLastOpponentRobotPosition() {
    return &lastOpponentRobotPosition;
}

void initOpponentRobot() {
    // Timer for detector
    addTimer(OPPONENT_ROBOT_TIMER_INDEX,
            TIME_DIVIDER_2_HERTZ,
            &opponentRobotCallbackFunc,
            "OPPONENT");
}

void updateOpponentRobotIfNecessary() {
    // wait after new flag changed by timer
    if (!mustAskLastOpponentRobotPosition) {
        return;
    }
    // reset Flag
    mustAskLastOpponentRobotPosition = false;

    // Update the opponent Robot Position by asking beaconReceiver
    updateOpponentRobotPosition(&lastOpponentRobotPosition);
}

