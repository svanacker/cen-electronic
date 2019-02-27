#include "servoListPc.h"

#include <stdlib.h>
#include <stdio.h>

#include "servoPwmPc.h"

#include "../servoList.h"

void initServoListPc(ServoList* servoList, Servo(*servoArray)[], unsigned int servoListSize) {
    initServoList(servoList, servoArray, servoListSize);
    unsigned int i;
    for (i = 0; i < servoListSize; i++) {
        char servoName[10];
        snprintf(servoName, 10, "%d", i);
        addServo(servoList, SERVO_TYPE_PC, i, servoName, servoInitPc, servoInternalPwmPc);
    }
}