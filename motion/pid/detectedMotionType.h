#ifndef DETECTED_MOTION_TYPE_H
#define DETECTED_MOTION_TYPE_H

#include "../../common/io/outputStream.h"

/**
 * Define the type of Position which is detected by the PID
 */
enum DetectedMotionType {
    /** No position to reach. */
    DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH = 0,
    
    /** No position to reach, but a position to maintain. */
    DETECTED_MOTION_TYPE_POSITION_TO_MAINTAIN = 1,
    
    /** The trajectory is in progress. */
    DETECTED_MOTION_TYPE_POSITION_IN_PROGRESS = 2,
    
    /** The robot reach the position. */
    DETECTED_MOTION_TYPE_POSITION_REACHED = 3,
    
    /** The robot seems to have his wheels blocked. */
    DETECTED_MOTION_TYPE_POSITION_BLOCKED_WHEELS = 4,
    
    /** The robot will hurt something (detection by RobotDetector). */
    DETECTED_MOTION_TYPE_POSITION_OBSTACLE = 5
};

unsigned int appendDetectedMotionTypeAsString(OutputStream* outputStream, enum DetectedMotionType detectedMotionType);

unsigned int addDetectedMotionTypeTableData(OutputStream* outputStream, enum DetectedMotionType detectedMotionType, unsigned int columnSize);

#endif
