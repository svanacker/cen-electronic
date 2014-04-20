#include <p30fxxxx.h>

#include "pwmPic.h"
#include "servoPwm.h"

#include "../../common/commons.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

/** The index of the timer (used to update value of servo). */
#define SERVO_TIMER_INDEX 10

/** For 50 Hz operation. */
#define PWM_TIMER_FOR_SERVO 9215

/** For 50 Hz operation. */
#define PWM_DUTY_CYCLE_FOR_SERVO 20000

/**
 * The servos.
 */
static ServoList servoList;

// IMPLEMENTATION

/**
 * @private.
 * duty convPwm ( int ms )
 * Objet : convertit une duree en ms en integer pour traitement
 * @param ms valeur en ms a convertir
 * @return resultat en Integer
 */
int convPwmServo(int ms) {
    long duty;
    duty = PWM_TIMER_FOR_SERVO * (long) ms;
    duty = duty / PWM_DUTY_CYCLE_FOR_SERVO;

    return (int) duty;
}

/**
 * @private.
 * Convert a duty cycle (from the OCXRS value)
 */
int confServoToPwm(int value) {
    long result;

    result = value * PWM_DUTY_CYCLE_FOR_SERVO;
    result = value / PWM_TIMER_FOR_SERVO;

    return (int) result;
}

void _pwmServo1(int dutyms) {
    OC1RS = convPwmServo(dutyms); //duty cycle OC1
}

void _pwmServo2(int dutyms) {
    OC2RS = convPwmServo(dutyms); //duty cycle OC2
}

void _pwmServo3(int dutyms) {
    OC3RS = convPwmServo(dutyms); //duty cycle OC3
}

void _pwmServo4(int dutyms) {
    OC4RS = convPwmServo(dutyms); //duty cycle OC4
}

Servo* getServo(int index) {
    return &(servoList.servos[index]);
}

void _internalPwmServo(int pwmIndex, int dutyms) {
    // Update the current Position of the servo
    switch (pwmIndex) {
        case 1:
        {
            _pwmServo1(dutyms);
            break;
        }
        case 2:
        {
            _pwmServo2(dutyms);
            break;
        }
        case 3:
        {
            _pwmServo3(dutyms);
            break;
        }
        case 4:
        {
            _pwmServo4(dutyms);
            break;
        }
    }
}

/**
 * The interrupt timer.
 */
void interruptServoTimerCallbackFunc(Timer* timer) {
    int i;
    for (i = 0; i < PWM_COUNT; i++) {
        Servo* servo = getServo(i);
        if (servo->currentPosition == servo->targetPosition) {
            continue;
        }
        if (servo->currentPosition < servo->targetPosition) {
            servo->currentPosition += servo->speed;
            if (servo->currentPosition > servo->targetPosition) {
                servo->currentPosition = servo->targetPosition;
            }
        } else if (servo->currentPosition > servo->targetPosition) {
            servo->currentPosition -= servo->speed;
            // Limit
            if (servo->currentPosition < servo->targetPosition) {
                servo->currentPosition = servo->targetPosition;
            }
        }
        _internalPwmServo(i + 1, servo->currentPosition);
    }
}

// PUBLIC INTERFACCE

void initPwmForServo(int posInit) {
    // PR2 = [  period / ( Tosc * 4 * prediv) ] -1
    // period = 20ms
    // Tosc = 1 / frequency
    pwmInit();
    PR2 = PWM_TIMER_FOR_SERVO; // period TIMER2
    OC1RS = convPwmServo(posInit); // duty cycle OC1
    OC2RS = convPwmServo(posInit); // duty cycle OC2
    OC3RS = convPwmServo(posInit); // duty cycle OC3
    OC4RS = convPwmServo(posInit); // duty cycle OC4
    T2CONbits.TCKPS = 0b10; // predivisor TIMER2 (64)
    T2CONbits.TON = 1; // activate Timer2

    // Init servo structure
    int i;
    for (i = 0; i < PWM_COUNT; i++) {
        Servo* servo = getServo(i);
        servo->speed = PWM_SERVO_SPEED_MAX;
        servo->currentPosition = posInit;
        servo->targetPosition = posInit;
    }

    // Init the timer for servo
    // and add the timer to the list, so that the interrupt function will
    // update at a certain frequency the position of the servo
    addTimer(SERVO_TIMER_INDEX,
            				TIME_DIVISER_50_HERTZ,
            				&interruptServoTimerCallbackFunc);
}

/**
 * @private
 */
void logServo(Servo* servo, OutputStream* outputStream) {
    appendString(outputStream, ",speed=");
    appendDec(outputStream, servo->speed);
    appendString(outputStream, ",currentPos=");
    appendDec(outputStream, servo->currentPosition);
    appendString(outputStream, ",targePos=");
    appendDec(outputStream, servo->targetPosition);
    appendCRLF(outputStream);
}

void pwmServo(int servoIndex, unsigned int speed, int dutyms) {
    if (servoIndex == 0) {
        writeError(ILLEGAL_ARGUMENT_EXCEPTION);
        appendString(getOutputStreamLogger(ERROR), "=>pwmServo");
        return;
    }
    Servo* servo = getServo(servoIndex - 1);
    servo->speed = speed;
    servo->targetPosition = dutyms;
    // logServo(servo, getOutputStreamLogger(ERROR));
}

void pwmServoAll(unsigned int speed, int dutyms) {
    int i;
    for (i = 1; i <= PWM_COUNT; i++) {
        pwmServo(i, speed, dutyms);
    }
}

void testAllPwmServos() {
	OutputStream* debugOutputStream = getOutputStreamLogger(DEBUG);
	int servoIndex;
	initPwmForServo(PWM_SERVO_MIDDLE_POSITION);

	for (servoIndex = 1; servoIndex <= PWM_COUNT; servoIndex++) {
		appendString(debugOutputStream, "Servo : ");
		appendDec(debugOutputStream, servoIndex);
		appendCRLF(debugOutputStream);
	    delaymSec(500);
	    pwmServo(servoIndex, PWM_SERVO_SPEED_MAX, PWM_SERVO_LEFT_POSITION);
	    delaymSec(500);
	    pwmServo(servoIndex, PWM_SERVO_SPEED_MAX, PWM_SERVO_RIGHT_POSITION);
		delaymSec(2000);
	}
}

