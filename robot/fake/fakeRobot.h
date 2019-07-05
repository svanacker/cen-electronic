#ifndef FAKE_ROBOT_H
#define FAKE_ROBOT_H

#include "../../common/2d/2d.h"

/**
 * Define the Structure which stores information about a fake or a "map opponent" Robot which moves and collide
 * with our robot sometimes.
 */
typedef struct FakeRobot {
    // x in millimeter
    float x;
    // y in millimeter
    float y;
    // angle in radian
    float angleRadian;
    // radius
    float radius;
    // The speed in mm / sec
    float speed;
    /** the target point in x */
    float targetX;
    /** the target point in Y */
    float targetY;
} FakeRobot;

/**
* Init the fake robot structure.
*/
void initFakeRobot(float x, float y, float angleRadian, float radius);

/**
* Simulate the continous move of the robot.
* TODO
*/
void moveFakeRobotForward(FakeRobot* fakeRobot);

/**
* 
*/
void gotoNextTarget(FakeRobot* fakeRobot);

/**
* Returns the singleton of fake Robot
*/
FakeRobot* getFakeRobotInstance(void);

#endif