#include "servoPwmDebug.h"
#include "servoPwm.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

void printServo(OutputStream* outputStream, Servo* servo) {
    appendString(outputStream, ",speed=");
    appendDec(outputStream, servo->speed);
    appendString(outputStream, ",currentPos=");
    appendDec(outputStream, servo->currentPosition);
    appendString(outputStream, ",targePos=");
    appendDec(outputStream, servo->targetPosition);
    appendCRLF(outputStream);
}


void printServoList(OutputStream* outputStream) {
    ServoList* servoList = _getServoList();
	int i;
    for (i = 0; i < PWM_COUNT; i++) {
        Servo* servo = &(servoList->servos[i]);

        printServo(outputStream, servo);
    }
}

// TEST FUNCTIONS

void testAllPwmServos() {
    OutputStream* debugOutputStream = getOutputStreamLogger(DEBUG);
    int servoIndex;
    initPwmForServo(PWM_SERVO_MIDDLE_POSITION);

    for (servoIndex = 1; servoIndex <= PWM_COUNT; servoIndex++) {
        appendString(debugOutputStream, "Servo : ");
        appendDec(debugOutputStream, servoIndex);
        delaymSec(500);
        pwmServo(servoIndex, PWM_SERVO_SPEED_MAX, PWM_SERVO_LEFT_POSITION);
        delaymSec(500);
        pwmServo(servoIndex, PWM_SERVO_SPEED_MAX, PWM_SERVO_RIGHT_POSITION);
        delaymSec(2000);
        appendCRLF(debugOutputStream);
    }
}
