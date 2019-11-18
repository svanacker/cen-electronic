#ifndef ROBOT_TYPE_H
#define ROBOT_TYPE_H

/**
 * Define a type of color which was detected.
 */
enum RobotType {
    // Used to detect that we do not have configured the robot
    ROBOT_TYPE_UNKNOWN = 0,
    // The big robot authorized for Eurobot
    ROBOT_TYPE_BIG = 1,
    // The Small robot authorized for Eurobot
    ROBOT_TYPE_SMALL = 2,
    // LIGHTHOUSE 2019,
    ROBOT_TYPE_LIGHTHOUSE_2020,
};

#endif

