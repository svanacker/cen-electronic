#include "goldenium2019.h"

#include "../fork/fork2019.h"
#include "../fork/forkScan2019.h"
#include "../elevator/elevator2019.h"

bool fork2019PrepareTakeGoldenium(ServoList* servoList, unsigned int leftRight) {
    // We do not wait because this action is a preparing action, so we could do during the robot moves
    bool wait = false;

    if (leftRight == FORK_2019_LEFT_INDEX) {
        moveElevatorLeft(servoList, wait);
    }
    else if (leftRight == FORK_2019_RIGHT_INDEX) {
        moveElevatorRight(servoList, wait);
    }

    // Fork Push Off for both !
    moveForkPushOff(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX, wait);

    // Fork Off for both !
    moveForkBack(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX, wait);

    // Elevator
    moveElevatorToScanGoldenium(servoList, wait);

    return true;
}

bool fork2019TakeGoldenium(ServoList* servoList, TofSensorList* tofSensorList, unsigned int leftRight) {
    // We wait because all actions must be finished before going to the next step !
    bool wait = true;

    forkScan(servoList, tofSensorList, leftRight);

    moveElevatorToTakeGoldenium(servoList, wait);

    // Fork Single Puck
    moveForkDoublePuck(servoList, leftRight, wait);

    // Elevator Up to free the Puck
    moveElevatorUp(servoList, wait);

    return true;
}

bool fork2019DropGoldenium(ServoList* servoList, unsigned int leftRight) {
    // Push : Must Wait
    moveForkPushOn(servoList, leftRight, true);

    // Fork back to let the puck without support => Must Wait
    moveForkBack(servoList, leftRight, true);

    // Push Off could be done without waiting
    moveForkPushOff(servoList, leftRight, false);

    return true;
}
