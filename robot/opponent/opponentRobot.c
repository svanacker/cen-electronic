#include "opponentRobot.h"

#include "../../common/commons.h"
#include "../../common/2d/2d.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../drivers/beacon/beaconReceiverDriver.h"
#include "../../drivers/strategy/strategyDriver.h"

/** The last OpponentRobotPosition. */
static Point lastOpponentRobotPosition;
static BOOL mustAskLastOpponentRobotPosition;

/** To distinguish every Timer. */
#define OPPONENT_ROBOT_TIMER_INDEX			5

void opponentRobotCallbackFunc(void) {
	mustAskLastOpponentRobotPosition = TRUE;
}

void initOpponentRobot() {
    // Timer for detector
    addTimer(OPPONENT_ROBOT_TIMER_INDEX,
            TIME_DIVISER_2_HERTZ,
            opponentRobotCallbackFunc);
}

void updateOpponentRobotIfNecessary() {
	// wait after new flag changed by timer
	if (!mustAskLastOpponentRobotPosition) {
		return;
	}
	// reset Flag
	mustAskLastOpponentRobotPosition = FALSE;

	// Update the opponent Robot Position
	updateOpponentRobotPosition(&lastOpponentRobotPosition);

	// Send the opponentRobot position if it has the information.			
	// if (lastOpponentRobotPosition.x != 0 && lastOpponentRobotPosition.y != 0) {
	//	sendStrategyOpponentRobotPosition(&lastOpponentRobotPosition);
	// }
}
