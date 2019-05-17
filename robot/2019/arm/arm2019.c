#include "arm2019.h"

#include "../fork/fork2019.h"

// ARM On for Small Robot

void arm2019On(ServoList* servoList, unsigned int leftRight) {
    fork2019MoveServo(servoList, leftRight,
        FORK_2019_LEFT_ARM_SERVO_INDEX, FORK_2019_RIGHT_ARM_SERVO_INDEX,
        FORK_2019_LEFT_ARM_SPEED_FACTOR, FORK_2019_RIGHT_ARM_SPEED_FACTOR,
        FORK_2019_LEFT_ARM_SERVO_ON, FORK_2019_RIGHT_ARM_SERVO_ON,
        false);
}

// ARM Off for Small Robot

void arm2019Off(ServoList* servoList, unsigned int leftRight) {
    fork2019MoveServo(servoList, leftRight,
        FORK_2019_LEFT_ARM_SERVO_INDEX, FORK_2019_RIGHT_ARM_SERVO_INDEX,
        FORK_2019_LEFT_ARM_SPEED_FACTOR, FORK_2019_RIGHT_ARM_SPEED_FACTOR,
        FORK_2019_LEFT_ARM_SERVO_OFF, FORK_2019_RIGHT_ARM_SERVO_OFF,
        false);
}