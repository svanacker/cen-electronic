#include "lightHouse2020Debug.h"

#include <stdlib.h>
#include <stdbool.h>

#include "lightHouse2020.h"
#include "lightHouse2020Actions.h"
#include "lightHouse2020CheckRobotPlaced.h"

#include "../../../common/error/error.h"

#include "../../../common/pwm/servo/servoList.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/log/logger.h"

#define LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH     40
#define LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH   25
#define LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH    10
#define LIGHT_HOUSE_2020_LAST_COLUMN            0

unsigned int printLightHouseState(OutputStream* outputStream, enum LightHouse2020State state) {
    if (state == LIGHT_HOUSE_STATE_UNKNOWN) {
        return appendString(outputStream, "UNKNOWN");
    } else if (state == LIGHT_HOUSE_STATE_INITIALIZED) {
        return appendString(outputStream, "INITIALIZED");
    } else if (state == LIGHT_HOUSE_STATE_INIT_GOING_DOWN) {
        return appendString(outputStream, "INIT GOING DOWN");
    } else if (state == LIGHT_HOUSE_STATE_INIT_POSITION_BOTTOM) {
        return appendString(outputStream, "BOTTOM OK");
    } else if (state == LIGHT_HOUSE_STATE_SEARCH_IF_PLACED) {
        return appendString(outputStream, "SEARCH IF PLACED");
    } else if (state == LIGHT_HOUSE_STATE_PLACED) {
        return appendString(outputStream, "PLACED");
    } else if (state == LIGHT_HOUSE_STATE_SEARCH_TOUCH) {
        return appendString(outputStream, "SEARCH TOUCH");
    } else if (state == LIGHT_HOUSE_STATE_TOUCHED) {
        return appendString(outputStream, "TOUCHED");
    } else if (state == LIGHT_HOUSE_STATE_TO_LAUNCH) {
        return appendString(outputStream, "TO LAUNCH");
    } else if (state == LIGHT_HOUSE_STATE_LAUNCHED) {
        return appendString(outputStream, "LAUNCHED");
    } else if (state == LIGHT_HOUSE_STATE_SHOW_REMAINING_TIME) {
        return appendString(outputStream, "SHOW REMAINING TIME");
    } else {
        return appendString(outputStream, "???");
    }
}

unsigned int addLightHouseStateTypeTableData(OutputStream* outputStream, enum LightHouse2020State state, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = printLightHouseState(outputStream, state);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

void printLightHouse2020TableHeader(OutputStream* outputStream) {
    println(outputStream);

    // Table Header
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Key", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Value", LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Unit", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);
}

void lightHouse2020Debug(LightHouse2020* lightHouse, OutputStream* outputStream) {
    printLightHouse2020TableHeader(outputStream);

    // State
    appendStringTableData(outputStream, "State", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    addLightHouseStateTypeTableData(outputStream, lightHouse->state, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);

    // Do Next Action
    appendStringTableData(outputStream, "Do Next Action", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendBoolAsStringTableData(outputStream, lightHouse->doNextAction, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);
    
    // Rotation
    appendStringTableData(outputStream, "Rotate Servo", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendBoolAsStringTableData(outputStream, lightHouse->rotateServo, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);
    
    // Timer Count
    appendStringTableData(outputStream, "Timer Count", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, lightHouse->timerCount, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);
    
    // Pwm Servo
    ServoList* servoList = lightHouse->servoList;
    Servo* servo = getServo(servoList, LIGHT_HOUSE_2020_SERVO_INDEX);

    unsigned int currentPosition = servo->currentPosition;
    appendStringTableData(outputStream, "PWM Current Position", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, currentPosition, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "ms", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);

    unsigned int targetPosition = servo->targetPosition;
    appendStringTableData(outputStream, "PWM Target Position", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, targetPosition, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "ms", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);
    
    appendTableHeaderSeparatorLine(outputStream);

    /*
    // Tof Index
    appendStringTableData(outputStream, "Tof Index", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, lightHouse->tofIndex, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);

    appendStringTableData(outputStream, "Current Dist.", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    TofSensor* tofSensor = lightHouse->tofSensor;
    if (tofSensor != NULL) {
        unsigned int distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
        appendDecTableData(outputStream, distanceMM, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    } else {
        appendStringTableData(outputStream, "TOF NULL", LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    }
    appendStringTableData(outputStream, "mm", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);

    appendStringTableData(outputStream, "Threshold - Min", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, LIGHT_HOUSE_2020_ROBOT_TOUCH_DISTANCE_MIN, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "mm", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);

    appendStringTableData(outputStream, "Threshold - Max", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, LIGHT_HOUSE_2020_ROBOT_TOUCH_DISTANCE_MAX, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "mm", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
*/
    
    appendStringTableData(outputStream, "Robot Placed - Analysis Count", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, lightHouse->robotPlacedAnalysisCount, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);

    // Robot Moved

    appendStringTableData(outputStream, "Robot Near - Analysis Count", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, lightHouse->robotNearAnalysisCount, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);


    appendStringTableData(outputStream, "RobotNearDetectionCount - Threshold", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, LIGHT_HOUSE_2020_ROBOT_PLACED_THRESHOLD_COUNT, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);

    appendStringTableData(outputStream, "RobotNearDetectionCount - Measured", LIGHT_HOUSE_2020_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, lightHouse->robotNearDetectionCount, LIGHT_HOUSE_2020_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", LIGHT_HOUSE_2020_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LIGHT_HOUSE_2020_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
}