#ifndef MOTION_SIMULATION_H
#define MOTION_SIMULATION_H

#include <stdbool.h>

#include "../../robot/strategy/gameStrategyContext.h"

typedef struct MotionSimulationParameter {
    /** Simulate that motors rotates */
    bool simulateMotors;
    /** Simulate that coders move like we want. */
    bool simulateCoders;
    /** Simulate that robot moves ! */
    bool simulateRobotPosition;
} MotionSimulationParameter;

/**
 * Returns the structure containing all information about motion Simulation.
 */
MotionSimulationParameter* getMotionSimulationParameter();

void simulateBSplineAbsolute(GameStrategyContext* gameStrategyContext, 
                             float destX,
                             float destY,
                             float angleRadian,
                             float dist0,
                             float dist1,
                             float accelerationFactor, float speedFactor);

void initMotionSimulation(GameStrategyContext* gameStrategyContext);

void simulateMotionCancel(GameStrategyContext* gameStrategyContext);

#endif
