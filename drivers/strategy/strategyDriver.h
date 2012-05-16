#ifndef STRATEGY_DRIVER_H
#define STRATEGY_DRIVER_H

#include "../../common/commons.h"
#include "../../common/2d/2d.h"

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
BOOL sendStrategyOpponentRobotPosition(Point* opponentRobotPosition);

BOOL sentStrategyRobotPosition(unsigned char status, unsigned int x, unsigned int y, int angleInDeciDegree);



#endif
