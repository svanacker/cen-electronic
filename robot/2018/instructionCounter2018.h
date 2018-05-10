#ifndef INSTRUCTION_COUNTER_2018_H
#define INSTRUCTION_COUNTER_2018_H

#include "../../robot/strategy/gameStrategyContext.h"

#include "../../device/motion/simple/motionDeviceInterface.h"

// START MATCH

#define INSTRUCTION_COUNTER_MATCH_WAIT_FOR_START          0

#define INSTRUCTION_COUNTER_MATCH_STARTED                 10

// SWITCH

#define INSTRUCTION_COUNTER_START_TO_SWITCH_MOVE_REQUESTED 20
#define INSTRUCTION_COUNTER_SWITCH_REACHED                 21

#define INSTRUCTION_COUNTER_SWITCH_ON                      22

// DISTRIBUTOR 1

#define INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_TO_REQUEST   50
#define INSTRUCTION_COUNTER_SWITCH_TO_DIST_1_REQUESTED    51

#define INSTRUCTION_COUNTER_DIST_1_REACHED                52

// BORDER 

#define INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_TO_REQUEST 60
#define INSTRUCTION_COUNTER_DIST_1_TO_BORDER_1_REQUESTED  61

#define INSTRUCTION_COUNTER_BORDER_1_REACHED              62

// BEE

#define INSTRUCTION_COUNTER_BORDER_1_TO_BEE_TO_REQUEST    70
#define INSTRUCTION_COUNTER_BORDER_1_TO_BEE_REQUESTED     71
#define INSTRUCTION_COUNTER_BEE_REACHED                   72

#define INSTRUCTION_COUNTER_END_MATCH                     80

// DISTRIBUTOR 2


// THRESHOLD
#define TRAJECTORY_REACHED_TRESHOLD                       150.0f

// TODO

char* appendInstructionCounterAsString(unsigned int instructionCounter);

void setNewInstructionCounter(GameStrategyContext* gameStrategyContext, unsigned int newInstructionCounter);

void initInstructionCounter(GameStrategyContext* gameStrategyContext);

void startInstructionCounter(GameStrategyContext* gameStrategyContext);

// HANDLE

void handleObstacle(GameStrategyContext* gameStrategyContext);

void handleNotificationInstructionCounter(GameStrategyContext* gameStrategyContext, unsigned commandHeader);

void handleNextInstructionCounter(GameStrategyContext* gameStrategyContext);

#endif
