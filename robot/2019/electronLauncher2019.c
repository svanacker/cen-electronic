#include "electronLauncher2019.h"

#include "../../common/error/error.h"

#include "../../common/pwm/servo/servoList.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/log/logger.h"


#include "../../common/timer/timerConstants.h"
#include "../../common/timer/delayTimer.h"
#include "../../common/timer/timerList.h"

#include "../../robot/config/robotConfig.h"

// CHECKS

void checkElectronLauncher2019RobotPlaced(ElectronLauncher2019* launcher) {
    if (!launcher->robotPlaced) {
        return;
    }
    TofSensor* tofSensor = launcher->tofSensor;
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return;
;    }
    unsigned int distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
    if (distanceMM > ELECTRON_LAUNCHER_2019_ROBOT_PLACED_DISTANCE_MIN 
     && distanceMM < ELECTRON_LAUNCHER_2019_ROBOT_PLACED_DISTANCE_MAX) {
        // We only notify one time
        launcher->robotPlaced = true;
        appendStringAndDec(getAlwaysOutputStreamLogger(), "ROBOT OK : ", distanceMM);
        appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");
    }
}

void checkElectronLauncher2019RobotMoved(ElectronLauncher2019* launcher) {
    if (!launcher->robotPlaced) {
        return;
    }
    if (launcher->robotMoved) {
        return;
    }
    TofSensor* tofSensor = launcher->tofSensor;
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return;
    }
    unsigned int i;
    unsigned detectionCount = 0;
    for (i = 0; i < ELECTRON_LAUNCHER_2019_CHECK_COUNT; i++) {
        unsigned int distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
        timerDelayMilliSeconds(10);
        if (distanceMM > ELECTRON_LAUNCHER_2019_ROBOT_MOVED_DISTANCE_MIN) {
            detectionCount++;
        }
    }
    // Store how many Count the detect
    launcher->robotMovedDetectionCount = detectionCount;
    if (detectionCount > ELECTRON_LAUNCHER_2019_THRESHOLD_COUNT) {
        // We only notify one time
        launcher->robotMoved = true;
        electronLauncher2019Launch(launcher);
    }
}


// ACTIONS

void electronLauncher2019Launch(ElectronLauncher2019* launcher) {
    ServoList* servoList = launcher->servoList;
    Servo* electronServo = getServo(servoList, ELECTRON_LAUNCHER_2019_ELECTRON_SERVO_INDEX);
    appendStringAndDecf(getAlwaysOutputStreamLogger(), "LAUNCH : ", 0);
    appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");
    launcher->robotMoved = true;
    unsigned int tryCount = 0;
    timerDelayMilliSeconds(500);
    for (tryCount = 0; tryCount < 5; tryCount++) {
        pwmServo(electronServo, PWM_SERVO_SPEED_MAX, ELECTRON_LAUNCHER_2019_ELECTRON_RELEASE_SERVO_VALUE, true);
        pwmServo(electronServo, PWM_SERVO_SPEED_MAX, ELECTRON_LAUNCHER_2019_ELECTRON_LOCKED_SERVO_VALUE, true);
    }
}

void electronLauncher2019Show(ElectronLauncher2019* launcher) {
    appendStringCRLF(getAlwaysOutputStreamLogger(), "SHOW : ");
    ServoList* servoList = launcher->servoList;
    Servo* experienceShowServo = getServo(servoList, ELECTRON_LAUNCHER_2019_EXPERIENCE_SHOW_SERVO_INDEX);
    pwmServo(experienceShowServo, PWM_SERVO_SPEED_MAX, ELECTRON_LAUNCHER_2019_EXPERIENCE_SHOW_VALUE, false);
}

void electronLauncher2019Init(ElectronLauncher2019* launcher) {
    appendStringCRLF(getAlwaysOutputStreamLogger(), " INIT");
    launcher->robotMoved = false;
    launcher->robotPlaced = false;
    ServoList* servoList = launcher->servoList;
    Servo* experienceShowServo = getServo(servoList, ELECTRON_LAUNCHER_2019_EXPERIENCE_SHOW_SERVO_INDEX);
    pwmServo(experienceShowServo, PWM_SERVO_SPEED_MAX, ELECTRON_LAUNCHER_2019_EXPERIENCE_INIT_VALUE, false);
}

// TIMER INTERRUPT


/**
 * The interrupt timer.
 */
void electronLauncher2019CallbackFunc(Timer* timer) {
    ElectronLauncher2019* launcher = (ElectronLauncher2019*)timer->object;

    checkElectronLauncher2019RobotPlaced(launcher);
    checkElectronLauncher2019RobotMoved(launcher);
}

// INIT

void initElectronLauncher2019(ElectronLauncher2019* launcher,
    RobotConfig* robotConfig,
    ServoList* servoList,
    TofSensorList* tofSensorList) {
    launcher->robotConfig = robotConfig;
    launcher->servoList = servoList;
    launcher->tofSensorList = tofSensorList;
    launcher->robotMoved = false;
    launcher->robotPlaced = false;
    if (isConfigSet(robotConfig, CONFIG_COLOR_YELLOW_MASK)) {
        appendStringCRLF(getAlwaysOutputStreamLogger(), "YELLOW->RIGHT");
        launcher->tofIndex = 0;
    }
    else {
        appendStringCRLF(getAlwaysOutputStreamLogger(), "VIOLET->LEFT");
        launcher->tofIndex = 1;
    }
    TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, launcher->tofIndex);
    launcher->tofSensor = tofSensor;
    Timer* timer = getTimerByCode(ELECTRON_LAUNCHER_2019_TIMER_CODE);
    if (timer == NULL) {
        addTimer(ELECTRON_LAUNCHER_2019_TIMER_CODE,
            TIME_DIVIDER_1_HERTZ,
            &electronLauncher2019CallbackFunc,
            "ELEC LAUNC 2019",
            (int*)servoList);
    }
}


// DEBUG


#define ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH     30
#define ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH   25
#define ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH    10
#define ELECTRON_LAUNCHER_2019_LAST_COLUMN            0

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

    // Tof Index
    appendStringTableData(outputStream, "Tof Index", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, launcher->tofIndex, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);

    // Robot Placed
    appendStringTableData(outputStream, "Robot Placed", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendBoolAsStringTableData(outputStream, launcher->robotPlaced, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);

    // Robot Moved
    appendStringTableData(outputStream, "Robot Moved", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendBoolAsStringTableData(outputStream, launcher->robotMoved, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);

    // robotMovedDetectionCount
    appendStringTableData(outputStream, "RobotMovedDetectionCount", ELECTRON_LAUNCHER_2019_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, launcher->robotMovedDetectionCount, ELECTRON_LAUNCHER_2019_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", ELECTRON_LAUNCHER_2019_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, ELECTRON_LAUNCHER_2019_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
}