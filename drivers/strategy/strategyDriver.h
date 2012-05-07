#ifndef STRATEGY_DRIVER_H
#define STRATEGY_DRIVER_H

#include "../../common/commons.h"

#include "../driver.h"

/**
* Send to the strategy board the configuration.
*/
BOOL sendStrategyConfiguration(int configuration);

/**
* Allow the strategy board to send new notification
*/
BOOL sendStrategyNextStep();

/**
 * Send the opponent robot position.
 */
BOOL sendStrategyOpponentRobotPosition(int x, int y);

#endif
