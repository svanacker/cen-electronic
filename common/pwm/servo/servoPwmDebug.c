#include "servoPwmDebug.h"
#include "servoPwm.h"
#include "servoList.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#define SERVO_PWM_DEBUG_INDEX_COLUMN_LENGTH                      7
#define SERVO_PWM_DEBUG_ENABLED_COLUMN_LENGTH                    8
#define SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH                      7
#define SERVO_PWM_DEBUG_CURRENT_POSITION_DEC_COLUMN_LENGTH       12
#define SERVO_PWM_DEBUG_CURRENT_POSITION_HEX_COLUMN_LENGTH       12
#define SERVO_PWM_DEBUG_TARGET_POSITION_DEC_COLUMN_LENGTH        12
#define SERVO_PWM_DEBUG_TARGET_POSITION_HEX_COLUMN_LENGTH        12
#define SERVO_PWM_DEBUG_LAST_COLUMN_LENGTH                       0

/**
* Private.
*/
void printServoListHeader(OutputStream* outputStream) {
	// Table Header
    // -> First Line
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "index", SERVO_PWM_DEBUG_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "enabled", SERVO_PWM_DEBUG_ENABLED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "speed", SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "current", SERVO_PWM_DEBUG_CURRENT_POSITION_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "current", SERVO_PWM_DEBUG_CURRENT_POSITION_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "target", SERVO_PWM_DEBUG_TARGET_POSITION_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "target", SERVO_PWM_DEBUG_TARGET_POSITION_HEX_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, SERVO_PWM_DEBUG_LAST_COLUMN_LENGTH);

    // -> Second Line 
	appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_ENABLED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Position", SERVO_PWM_DEBUG_CURRENT_POSITION_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Position", SERVO_PWM_DEBUG_CURRENT_POSITION_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Position", SERVO_PWM_DEBUG_TARGET_POSITION_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Position", SERVO_PWM_DEBUG_TARGET_POSITION_HEX_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, SERVO_PWM_DEBUG_LAST_COLUMN_LENGTH);

    // -> Third Line 
	appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_ENABLED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Dec)", SERVO_PWM_DEBUG_CURRENT_POSITION_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Hex))", SERVO_PWM_DEBUG_CURRENT_POSITION_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Dec)", SERVO_PWM_DEBUG_TARGET_POSITION_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Hex)", SERVO_PWM_DEBUG_TARGET_POSITION_HEX_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, SERVO_PWM_DEBUG_LAST_COLUMN_LENGTH);

	appendTableHeaderSeparatorLine(outputStream);
}

void printServo(OutputStream* outputStream, Servo* servo, int index) {
	appendDecTableData(outputStream, index, SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH);
	appendBoolTableData(outputStream, servo->enabled, SERVO_PWM_DEBUG_ENABLED_COLUMN_LENGTH);
	appendDecTableData(outputStream, servo->speed, SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH);
	appendDecTableData(outputStream, servo->currentPosition, SERVO_PWM_DEBUG_CURRENT_POSITION_DEC_COLUMN_LENGTH);
	appendHex4TableData(outputStream, servo->currentPosition, SERVO_PWM_DEBUG_CURRENT_POSITION_HEX_COLUMN_LENGTH);
	appendDecTableData(outputStream, servo->targetPosition, SERVO_PWM_DEBUG_TARGET_POSITION_DEC_COLUMN_LENGTH);
	appendHex4TableData(outputStream, servo->targetPosition, SERVO_PWM_DEBUG_TARGET_POSITION_HEX_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, SERVO_PWM_DEBUG_LAST_COLUMN_LENGTH);
}


void printServoList(ServoList* servoList, OutputStream* outputStream) {
	println(outputStream);
	printServoListHeader(outputStream);
    int i;
    for (i = 0; i < PWM_COUNT; i++) {
        Servo* servo = getServo(servoList, i + 1);

        printServo(outputStream, servo, i);
    }
	appendTableHeaderSeparatorLine(outputStream);
}

// TEST FUNCTIONS

void testAllPwmServos(ServoList* servoList) {
    OutputStream* infoOutputStream = getInfoOutputStreamLogger();
    int servoIndex;

    for (servoIndex = 1; servoIndex <= PWM_COUNT; servoIndex++) {
        pwmServo(servoIndex, PWM_SERVO_SPEED_MAX, PWM_SERVO_MIDDLE_POSITION);
        appendString(infoOutputStream, "Servo : ");
        appendDec(infoOutputStream, servoIndex);
        delaymSec(500);
        pwmServo(servoIndex, PWM_SERVO_SPEED_MAX, PWM_SERVO_LEFT_POSITION);
        delaymSec(500);
        pwmServo(servoIndex, PWM_SERVO_SPEED_MAX, PWM_SERVO_RIGHT_POSITION);
        delaymSec(2000);
        appendCRLF(infoOutputStream);
    }
}
