#include "servoPwmDebug.h"
#include "servoPwm.h"
#include "servoList.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#define SERVO_PWM_DEBUG_INDEX_DEC_COLUMN_LENGTH                  5
#define SERVO_PWM_DEBUG_INDEX_HEX_COLUMN_LENGTH                  5
#define SERVO_PWM_DEBUG_NAME_COLUMN_LENGTH                       8
#define SERVO_PWM_DEBUG_INTERNAL_INDEX_COLUMN_LENGTH             9
#define SERVO_PWM_DEBUG_TYPE_COLUMN_LENGTH                       9
#define SERVO_PWM_DEBUG_ENABLED_COLUMN_LENGTH                    8
#define SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH                      12
#define SERVO_PWM_DEBUG_CURRENT_POSITION_DEC_COLUMN_LENGTH       8
#define SERVO_PWM_DEBUG_CURRENT_POSITION_HEX_COLUMN_LENGTH       8
#define SERVO_PWM_DEBUG_TARGET_POSITION_DEC_COLUMN_LENGTH        8
#define SERVO_PWM_DEBUG_TARGET_POSITION_HEX_COLUMN_LENGTH        8
#define SERVO_PWM_DEBUG_LAST_COLUMN_LENGTH                       0

/**
* Private.
*/
void printServoListHeader(OutputStream* outputStream) {
	// Table Header
    // -> First Line
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Idx", SERVO_PWM_DEBUG_INDEX_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Idx", SERVO_PWM_DEBUG_INDEX_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Name", SERVO_PWM_DEBUG_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Internal", SERVO_PWM_DEBUG_INTERNAL_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "type", SERVO_PWM_DEBUG_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "enabled", SERVO_PWM_DEBUG_ENABLED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "speed", SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "current", SERVO_PWM_DEBUG_CURRENT_POSITION_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "current", SERVO_PWM_DEBUG_CURRENT_POSITION_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "target", SERVO_PWM_DEBUG_TARGET_POSITION_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "target", SERVO_PWM_DEBUG_TARGET_POSITION_HEX_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, SERVO_PWM_DEBUG_LAST_COLUMN_LENGTH);

    // -> Second Line 
	appendStringHeader(outputStream, "(Dec)", SERVO_PWM_DEBUG_INDEX_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Hex)", SERVO_PWM_DEBUG_INDEX_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Idx", SERVO_PWM_DEBUG_INTERNAL_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_ENABLED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Delta ms /", SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Pos.", SERVO_PWM_DEBUG_CURRENT_POSITION_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Pos.", SERVO_PWM_DEBUG_CURRENT_POSITION_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Pos.", SERVO_PWM_DEBUG_TARGET_POSITION_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Pos.", SERVO_PWM_DEBUG_TARGET_POSITION_HEX_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, SERVO_PWM_DEBUG_LAST_COLUMN_LENGTH);

    // -> Third Line 
	appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_INDEX_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_INDEX_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_INTERNAL_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "", SERVO_PWM_DEBUG_ENABLED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "deltaT)", SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Dec)", SERVO_PWM_DEBUG_CURRENT_POSITION_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Hex)", SERVO_PWM_DEBUG_CURRENT_POSITION_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Dec)", SERVO_PWM_DEBUG_TARGET_POSITION_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Hex)", SERVO_PWM_DEBUG_TARGET_POSITION_HEX_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, SERVO_PWM_DEBUG_LAST_COLUMN_LENGTH);

	appendTableHeaderSeparatorLine(outputStream);
}

void printServo(OutputStream* outputStream, Servo* servo, unsigned int servoIndex) {
    appendDecTableData(outputStream, servoIndex, SERVO_PWM_DEBUG_INDEX_DEC_COLUMN_LENGTH);
    appendHex2TableData(outputStream, servoIndex, SERVO_PWM_DEBUG_INDEX_HEX_COLUMN_LENGTH);
    appendStringTableData(outputStream, servo->name, SERVO_PWM_DEBUG_NAME_COLUMN_LENGTH);
    appendDecTableData(outputStream, servo->internalServoIndex, SERVO_PWM_DEBUG_INTERNAL_INDEX_COLUMN_LENGTH);
    addServoTypeTableData(outputStream, servo->servoType, SERVO_PWM_DEBUG_TYPE_COLUMN_LENGTH);
	appendBoolAsStringTableData(outputStream, servo->enabled, SERVO_PWM_DEBUG_ENABLED_COLUMN_LENGTH);
	appendDecTableData(outputStream, servo->speed, SERVO_PWM_DEBUG_SPEED_COLUMN_LENGTH);
	appendDecTableData(outputStream, servo->currentPosition, SERVO_PWM_DEBUG_CURRENT_POSITION_DEC_COLUMN_LENGTH);
	appendHex4TableData(outputStream, servo->currentPosition, SERVO_PWM_DEBUG_CURRENT_POSITION_HEX_COLUMN_LENGTH);
	appendDecTableData(outputStream, servo->targetPosition, SERVO_PWM_DEBUG_TARGET_POSITION_DEC_COLUMN_LENGTH);
	appendHex4TableData(outputStream, servo->targetPosition, SERVO_PWM_DEBUG_TARGET_POSITION_HEX_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, SERVO_PWM_DEBUG_LAST_COLUMN_LENGTH);
}


void printServoList(OutputStream* outputStream, ServoList* servoList) {
	println(outputStream);
	printServoListHeader(outputStream);
    unsigned int i;
    unsigned lineCounter;
    enum ServoType servoType = SERVO_TYPE_UNKNOWN;
    for (i = 0; i < servoList->size; i++) {
        Servo* servo = getServo(servoList, i);
        if (servo->servoType != servoType) {
            if (servoType != SERVO_TYPE_UNKNOWN) {
            	appendTableHeaderSeparatorLine(outputStream);
            }
            servoType = servo->servoType;
            lineCounter = 0;
        }
        if (lineCounter >= 4 && i != servoList->size- 1) {
        	appendTableHeaderSeparatorLine(outputStream);
            lineCounter = 0;
        }
        lineCounter++;
        printServo(outputStream, servo, i);
    }
	appendTableHeaderSeparatorLine(outputStream);
}

// SERVO TYPE

unsigned int appendServoTypeAsString(OutputStream* outputStream, enum ServoType servoType) {
    if (servoType == SERVO_TYPE_UNKNOWN) {
        return appendString(outputStream, "UNKNOWN");
    }
    else if (servoType == SERVO_TYPE_INTERNAL_PWM) {
        return appendString(outputStream, "INTERNAL");
    }
    else if (servoType == SERVO_TYPE_PCA_8695) {
        return appendString(outputStream, "PCA_8695");
    }
    else if (servoType == SERVO_TYPE_SD_21) {
		return appendString(outputStream, "SD21");
    }
    else if (servoType == SERVO_TYPE_PC) {
		return appendString(outputStream, "PC");
    }
    else {
        append(outputStream, '?');
		return 1;
    }
	return 0;
}

unsigned int addServoTypeTableData(OutputStream* outputStream, enum ServoType servoType, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	unsigned int length = appendServoTypeAsString(outputStream, servoType);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}

// TEST FUNCTIONS

void testAllPwmServos(ServoList* servoList) {
    OutputStream* infoOutputStream = getInfoOutputStreamLogger();
    unsigned int servoIndex;

    for (servoIndex = 0; servoIndex < servoList->size; servoIndex++) {
        Servo* servo = getServo(servoList, servoIndex);
        pwmServo(servo, PWM_SERVO_SPEED_MAX, PWM_SERVO_MIDDLE_POSITION);
        appendString(infoOutputStream, "Servo : ");
        appendDec(infoOutputStream, servoIndex);
        delaymSec(500);
        pwmServo(servo, PWM_SERVO_SPEED_MAX, PWM_SERVO_LEFT_POSITION);
        delaymSec(500);
        pwmServo(servo, PWM_SERVO_SPEED_MAX, PWM_SERVO_RIGHT_POSITION);
        delaymSec(2000);
        appendCRLF(infoOutputStream);
    }
}
