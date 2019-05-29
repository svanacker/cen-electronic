#ifndef FAKE_ROBOT_H
#define FAKE_ROBOT_H

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
} FakeRobot;

void initFakeRobot(float x, float y, float angleRadian, float radius);

/**
* Returns the singleton of fake Robot
*/
FakeRobot* getFakeRobotInstance(void);

#endif