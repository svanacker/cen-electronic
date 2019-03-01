#include "servoListPc.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "servoPwmPc.h"

#include "../servoList.h"

#define SERVO_NAME_PC_STRING_LENGTH   15

Servo* addServoPc(ServoList* servoList, unsigned internalIndex, char* servoName) {
    return addServo(servoList,
                    SERVO_TYPE_PC,
                    internalIndex,
                    servoName,
                    servoTypeInitPc,
                    servoInitPc,
                    servoUpdateConfigPc,
                    servoInternalPwmPc,
                    NULL);
}

void initServoListPc(ServoList* servoList, Servo(*servoArray)[], unsigned int servoListSize) {
    initServoList(servoList, servoArray, servoListSize);
    unsigned int i;
    for (i = 0; i < servoListSize; i++) {
        char* servoName = (char*)malloc(SERVO_NAME_PC_STRING_LENGTH * sizeof(char));;
        snprintf(servoName, SERVO_NAME_PC_STRING_LENGTH, "PC ");
        snprintf(servoName + strlen(servoName), SERVO_NAME_PC_STRING_LENGTH, "%d", i);
        addServoPc(servoList, i, servoName);
    }
}