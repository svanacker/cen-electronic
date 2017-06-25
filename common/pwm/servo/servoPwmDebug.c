#include "servoPwmDebug.h"
#include "servoPwm.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#define SERVO_PWM_DEBUG_INDEX_COLUMN_LENGTH           7
#define SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH           7
#define SERVO_PWM_DEBUG_CURRENT_POS_COLUMN_LENGTH     10
#define SERVO_PWM_DEBUG_TARGET_POS_COLUMN_LENGTH      10

/**
* Private.
*/
void printServoListHeader(OutputStream* outputStream) {
	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "index", SERVO_PWM_DEBUG_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "speed", SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "currentPos", SERVO_PWM_DEBUG_CURRENT_POS_COLUMN_LENGTH);
	appendStringHeader(outputStream, "targetPos", SERVO_PWM_DEBUG_TARGET_POS_COLUMN_LENGTH);
	appendTableSeparator(outputStream);
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
}

void printServo(OutputStream* outputStream, Servo* servo, int index) {
	appendDecTableData(outputStream, index, SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH);
	appendDecTableData(outputStream, servo->speed, SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH);
	appendDecTableData(outputStream, servo->currentPosition, SERVO_PWM_DEBUG_CURRENT_POS_COLUMN_LENGTH);
	appendDecTableData(outputStream, servo->targetPosition, SERVO_PWM_DEBUG_TARGET_POS_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
}


void printServoList(OutputStream* outputStream) {
	println(outputStream);
	printServoListHeader(outputStream);
    ServoList* servoList = _getServoList();
    int i;
    for (i = 0; i < PWM_COUNT; i++) {
        Servo* servo = &(servoList->servos[i]);

        printServo(outputStream, servo, i);
    }
	appendTableHeaderSeparatorLine(outputStream);
}

// TEST FUNCTIONS

void testAllPwmServos() {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
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
