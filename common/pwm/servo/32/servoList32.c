#include "servoList32.h"
#include "servoPwm32.h"

#include "../servoList.h"
#include "../servoPwm.h"

#include <stdlib.h>

Servo* addServo32(ServoList* servoList, unsigned int internalServoIndex, char* servoName) {
    return addServo(servoList,
              SERVO_TYPE_INTERNAL_PWM,
              internalServoIndex,
              servoName,
              _internalTypeInitPwmServo32,
              _internalInitPwmServo32,
              _internalUpdateConfigServo32,
              _servoInternalPwm32,
            NULL);
}

/**
 * Add to the servo List 
 */
void addServos_1_2_5(ServoList* servoList, char* nameServo1, char* nameServo2, char* nameServo5) {
    addServo32(servoList, 1, nameServo1);
    addServo32(servoList, 2, nameServo2);
    addServo32(servoList, 5, nameServo5);
}

void addServos_1_2_3_4_5(ServoList* servoList,
                         char* nameServo1,
                         char* nameServo2, char* nameServo3, char* nameServo4, char* nameServo5) {
    addServo32(servoList, 1, nameServo1);
    addServo32(servoList, 2, nameServo2);
    addServo32(servoList, 3, nameServo3);
    addServo32(servoList, 4, nameServo4);
    addServo32(servoList, 5, nameServo5);
    
}