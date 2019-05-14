#include "electronLauncher2019Debug.h"

#include <stdlib.h>
#include <stdbool.h>

#include "electronLauncher2019.h"

#include "../../common/error/error.h"

#include "../../common/pwm/servo/servoList.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/log/logger.h"

#define ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH     40
#define ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH   25
#define ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH    10
#define ELECTRON_LAUNCHER_2019_LAST_COLUMN            0

unsigned int printElectronLauncherState(OutputStream* outputStream, enum ElectronLauncher2019State state) {
    if (state == LAUNCHER_STATE_UNKNOWN) {
        return appendString(outputStream, "UNKNOWN");
    }
    else if (state == LAUNCHER_STATE_INITIALIZED) {
        return appendString(outputStream, "INITIALIZED");
    }
    else if (state == LAUNCHER_STATE_SEARCH_ROBOT_PLACED) {
        return appendString(outputStream, "SEARCH ROBOT PLACED");
    }
    else if (state == LAUNCHER_STATE_ROBOT_PLACED) {
        return appendString(outputStream, "ROBOT PLACED");
    }
    else if (state == LAUNCHER_STATE_SEARCH_ROBOT_MOVED) {
        return appendString(outputStream, "SEARCH ROBOT MOVED");
    }
    else if (state == LAUNCHER_STATE_ROBOT_MOVED) {
        return appendString(outputStream, "ROBOT MOVED");
    }
    else if (state == LAUNCHER_STATE_TO_LAUNCH) {
        return appendString(outputStream, "TO LAUNCH");
    }
    else if (state == LAUNCHER_STATE_LAUNCHED) {
        return appendString(outputStream, "LAUNCHED");
    }
    else if (state == LAUNCHER_STATE_SHOW_REMAINING_TIME) {
        return appendString(outputStream, "SHOW REMAINING TIME");
    }
    else {
        return appendString(outputStream, "???");
    }
}

unsigned int addLauncherStateTypeTableData(OutputStream* outputStream, enum ElectronLauncher2019State state, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = printElectronLauncherState(outputStream, state);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}


void printElectronLauncher2019TableHeader(OutputStream* outputStream) {
    println(outputStream);

    // Table Header
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Key", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Value", ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Unit", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);
}

void electronLauncher2019Debug(ElectronLauncher2019* launcher, OutputStream* outputStream) {
    printElectronLauncher2019TableHeader(outputStream);

    appendStringTableData(outputStream, "State", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    addLauncherStateTypeTableData(outputStream, launcher->state, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);

    // Tof Index
    appendStringTableData(outputStream, "Tof Index", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, launcher->tofIndex, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);

    appendStringTableData(outputStream, "Current Dist.", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    TofSensor* tofSensor = launcher->tofSensor;
    if (tofSensor != NULL) {
        unsigned int distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
        appendDecTableData(outputStream, distanceMM, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    }
    else {
        appendStringTableData(outputStream, "TOF NULL", ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    }
    appendStringTableData(outputStream, "mm", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);

    appendStringTableData(outputStream, "Threshold - Min", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, ELECTRON_LAUNCHER_2019_ROBOT_PLACED_DISTANCE_MIN, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "mm", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);

    appendStringTableData(outputStream, "Threshold - Max", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, ELECTRON_LAUNCHER_2019_ROBOT_PLACED_DISTANCE_MAX, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "mm", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);

    appendStringTableData(outputStream, "Robot Placed - Analysis Count", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, launcher->robotPlacedAnalysisCount, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);


    appendTableHeaderSeparatorLine(outputStream);

    // Robot Moved

    appendStringTableData(outputStream, "Robot Moved - Analysis Count", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, launcher->robotMovedAnalysisCount, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);

    // robotMovedDetectionCount
    /*
    appendStringTableData(outputStream, "RobotMovedDetectionCount - Check Count", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, ELECTRON_LAUNCHER_2019_CHECK_COUNT, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);
    */
    appendStringTableData(outputStream, "RobotMovedDetectionCount - Threshold", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, ELECTRON_LAUNCHER_2019_THRESHOLD_COUNT, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);
    
    appendStringTableData(outputStream, "RobotMovedDetectionCount - Measured", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, launcher->robotMovedDetectionCount, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
}