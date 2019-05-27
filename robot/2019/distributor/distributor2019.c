#include "distributor2019.h"

#include <stdbool.h>

#include "../../../common/color/color.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../robot/strategy/teamColor.h"

#include "../../../robot/2019/elevator/elevator2019.h"
#include "../../../robot/2019/fork/forkScan2019.h"
#include "../../../robot/2019/fork/fork2019.h"


bool distributor2019PrepareTake(ServoList* servoList) {
    // We do not wait because this action is a preparing action, so we could do during the robot moves
    bool wait = false;

    // Fork Push Off for both
    moveForkPushOff(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX, wait);
    
    // Fork Push Off for both
    moveForkBack(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX, wait);

    // Elevator
    moveElevatorDistributorScan(servoList, wait);
    
    return true;
}

/**
 * All actions to take a 2 Pucks.
 * @param servoList
 */
bool distributor2019Take(ServoList* servoList, TofSensorList* tofSensorList) {
    // We wait because all actions must be finished before going to the next step !
    bool wait = true;

    // TODO : Scan to do => Return false if the scan is KO
    if (!forkScan(servoList, tofSensorList, FORK_2019_LEFT_AND_RIGHT_INDEX)) {
        return false;
    }
    
    // Move to Bottom which is the level to take the distributor elements
    moveElevatorBottom(servoList, wait);

    // Fork Single Puck
    moveForkSimplePuck(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX, wait);

    // Elevator Up to free the and prepare to put either in the Weighing Machine, or in the Accelerator Front
    moveElevatorUp(servoList, wait);

    return true;
}
