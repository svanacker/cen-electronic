#ifndef STRATEGY_2018_H
#define STRATEGY_2018_H

#include "../../robot/strategy/gameTarget.h"
#include "../../robot/match/teamColor.h"

#include "../../motion/simple/simpleMotion.h"


/**
* Init all elements for 2018.
*/
void initStrategy2018(int strategyIndex);

/**
* Print
*/
void printStrategyAllDatas(OutputStream* outputStream);

/**
* Define the color and update strategy.
*/
void setColor(enum TeamColor color);

#endif
