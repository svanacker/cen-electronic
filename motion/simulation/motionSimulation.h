#ifndef MOTION_SIMULATION_H
#define MOTION_SIMULATION_H

#include <stdbool.h>

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

#endif
