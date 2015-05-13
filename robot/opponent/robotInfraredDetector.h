#ifndef ROBOT_INFRARED_DETECTOR_H
#define ROBOT_INFRARED_DETECTOR_H

#include <stdbool.h>

/** 
 * Define the underlying function type attached to a group to evaluate if 
 * the infrared detect something.
 */
typedef bool InfraredDetectorFunction();

/** 
 * Type of Group of Detector
 */
enum InfraredDetectorGroupType {
    /** The group of Detector to go forward. */
    DETECTOR_GROUP_TYPE_FORWARD = 0,
    /** The group of Detector to go backward. */
    DETECTOR_GROUP_TYPE_BACKWARD = 1
};

/**
 * Detection is based on 2 GPD12 on left / right, and a gp2y0a02yk on the center
 */
typedef struct InfraredDetectorGroup {
    // DEFINITION VALUES
    /** Group Type. */
    enum InfraredDetectorGroupType type;
    /** The function to evaluate it. */
    InfraredDetectorFunction* function;
    /** If we must notify when we detects something */
    bool notifyIfDetected;
    // COMPUTATION VALUES
    /** The number of count which was detected. */
    int wasDetectedCount;
    /** A counter to avoid to notify. */
    bool doNotCheckBeforeCounter;
    /** A counter of interruption. */
    unsigned int interruptCounter;
} InfraredDetectorGroup;

/** 
 * Initializes a group of detector.
 * @param the type of group of detector (backward / forward)
 * @param function the function to evaluate if there is a detection associated with the group
 */
void initInfraredDetectorGroup(InfraredDetectorGroup* group, enum InfraredDetectorGroupType type, InfraredDetectorFunction* function);

/**
 * Encapsulates the all informations about detector
 */
typedef struct RobotInfraredDetector{
    /** Group of detector for backward. */
    InfraredDetectorGroup backwardDetectorGroup;
    /** Group of detector for forward move. */
    InfraredDetectorGroup forwardDetectorGroup;
} RobotInfraredDetector;

/**
 * Init and a timer to search via infrared detector.
 */
void initRobotInfraredDetector(RobotInfraredDetector* robotInfraredDetector);

/**
 * Returns if there is an obstacle forward.
 */
bool getRobotInfraredObstacleForward(void);

/**
 * Returns if there is an obstacle backward.
 */
bool getRobotInfraredObstacleBackward(void);

void setInfraredRobotNotification(enum InfraredDetectorGroupType type, bool enable);

/** 
 * Returns the global instance of RobotInfrared.
 */
RobotInfraredDetector* getRobotInfraredDetector(void);


#endif
