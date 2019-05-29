#include "fakeRobot.h"

static FakeRobot fakeRobot;

void initFakeRobot(float x, float y, float angleRadian, float radius) {
    fakeRobot.x = x;
    fakeRobot.y = y;
    fakeRobot.angleRadian = angleRadian;
    fakeRobot.radius = radius;
}

/**
* Returns the singleton of fake Robot
*/
FakeRobot* getFakeRobotInstance(void) {
    return &fakeRobot;
}