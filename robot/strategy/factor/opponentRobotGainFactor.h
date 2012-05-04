#ifndef OPPONENT_ROBOT_GAIN_FACTOR_H
#define OPPONENT_ROBOT_GAIN_FACTOR_H

/**
 * Determines the gain and the risk of doing this strategy by analyzing the
 * opponent robot strategy and the risk that there is a collision even if the
 * way is not filled and that we can go. For example, if robot does always
 * something to the bottom left, we consider that it is riskly to do actions to
 * the bottom left too.
 * 
 */

/**
 * Returns the gain which must take into account the opponent strategy.
 * 
 * @param opponent
 * @return
 */
typedef float getOpponentRobotGainFactorFunction(float robotX, float robotY);

#endif
