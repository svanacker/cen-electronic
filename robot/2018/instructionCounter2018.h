#ifndef INSTRUCTION_COUNTER_2018_H
#define INSTRUCTION_COUNTER_2018_H

#include "../../robot/strategy/gameStrategyContext.h"

#define INSTRUCTION_COUNTER_MATCH_WAIT_FOR_START          0

#define INSTRUCTION_COUNTER_MATCH_STARTED                 1

#define INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_ASKED    2

#define INSTRUCTION_COUNTER_SWITCH_REACHED                3

#define INSTRUCTION_COUNTER_SWITCH_ON                     4

#define INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_ASKED        5

#define INSTRUCTION_COUNTER_DIST_1_REACHED                6

#define INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_ASKED      7

#define INSTRUCTION_COUNTER_BORDER_1_REACHED             8

#define INSTRUCTION_COUNTER_BORDER_1_TO_BEE_ASKED         9

#define INSTRUCTION_COUNTER_BEE_REACHED                  10

void initInstructionCounter(GameStrategyContext* gameStrategyContext);

void startInstructionCounter(GameStrategyContext* gameStrategyContext);

void handleNotificationInstructionCounter(GameStrategyContext* gameStrategyContext);

void handleNextInstructionCounter(GameStrategyContext* gameStrategyContext);

#endif
