#ifndef ELEVATOR_2019_H
#define ELEVATOR_2019_H

#include <stdbool.h>

#include "../../../common/pwm/servo/servoList.h"

#include "../../../drivers/tof/tofList.h"

// ELEVATOR

void moveElevatorAtValue(ServoList* servoList, unsigned int value, bool wait);

void moveElevatorBottom(ServoList* servoList, bool wait);

void moveElevatorDistributorScan(ServoList* servoList, bool wait);

void moveElevatorUp(ServoList* servoList, bool wait);

void moveElevatorAcceleratorSecondDrop(ServoList* servoList, bool wait);

void moveElevatorInitPosition(ServoList* servoList, bool wait);

// GOLDENIUM

void moveElevatorToScanGoldenium(ServoList* servoList, bool wait);

void moveElevatorToTakeGoldenium(ServoList* servoList, bool wait);

// LEFT / RIGHT

void moveElevatorLeft(ServoList* servoList, bool wait);

void moveElevatorMiddle(ServoList* servoList, bool wait);

void moveElevatorRight(ServoList* servoList, bool wait);

#endif
