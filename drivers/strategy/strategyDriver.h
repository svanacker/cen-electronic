#ifndef STRATEGY_DRIVER_H
#define STRATEGY_DRIVER_H

#include <stdbool.h>

#include "../../common/2d/2d.h"

#include "../driver.h"

/**
 * Init the strategy driver and the timer to force next step if needed
 */
void initStrategyDriver();

/**
 * Force next step if last next step is too old.
 */
void forceRobotNextStepIfNecessary();

/**
 * Do all call to do the next step.
 */
void robotNextStep();

/**
* Send to the strategy board the configuration.
*/
bool sendStrategyConfiguration(int configuration);

/**
* Allow the strategy board to send new notification
*/
bool sendStrategyNextStep();

/**
 * Send the opponent robot position.
 */
bool sendStrategyOpponentRobotPosition(Point* opponentRobotPosition);

bool sentStrategyRobotPosition(unsigned char status, float x, float y, float angleDegree);

#endif
