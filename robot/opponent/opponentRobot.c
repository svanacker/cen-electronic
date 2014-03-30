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
#define OPPONENT_ROBOT_TIMER_INDEX			5

void opponentRobotCallbackFunc(Timer* timer) {
	mustAskLastOpponentRobotPosition = TRUE;
}

Point* getLastOpponentRobotPosition() {
	return &lastOpponentRobotPosition;
}

void initOpponentRobot() {
    // Timer for detector
    addTimer(OPPONENT_ROBOT_TIMER_INDEX,
            TIME_DIVISER_2_HERTZ,
            &opponentRobotCallbackFunc);
}

void updateOpponentRobotIfNecessary() {
	// wait after new flag changed by timer
	if (!mustAskLastOpponentRobotPosition) {
		return;
	}
	// reset Flag
	mustAskLastOpponentRobotPosition = FALSE;

	// Update the opponent Robot Position by asking beaconReceiver
	updateOpponentRobotPosition(&lastOpponentRobotPosition);
}

