#include "electronLauncher2019.h"
#include "electronLauncher2019Debug.h"

#include <stdlib.h>

#include "../../../common/error/error.h"

#include "../../../common/pwm/servo/servoList.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/log/logger.h"

#include "../../../common/timer/timerConstants.h"
#include "../../../common/timer/delayTimer.h"
#include "../../../common/timer/timerList.h"

#include "../../../robot/config/robotConfig.h"

#include "../../../robot/match/endMatch.h"

#include "../../../drivers/tof/tofDetectionUtils.h"

void updateElectronLauncherState(ElectronLauncher2019* launcher, enum ElectronLauncher2019State newState) {
    if (launcher == NULL) {
        writeError(ELECTRON_LAUNCHER_2019_NULL);
        return;
    }
    if (launcher->state == newState) {
        return;
    }
    else {
        OutputStream* outputStream = getDebugOutputStreamLogger();
        printElectronLauncherState(outputStream, launcher->state);
        launcher->state = newState;
        appendString(outputStream, "-->");
        printElectronLauncherState(outputStream, launcher->state);
        appendCRLF(outputStream);
    }
}


// SIMULATION

void electronLauncher2019SimulateRobotPlaced(ElectronLauncher2019* launcher) {
    updateElectronLauncherState(launcher, LAUNCHER_STATE_ROBOT_PLACED);
}

void electronLauncher2019SimulateRobotPlacedAndMoved(ElectronLauncher2019* launcher) {
    updateElectronLauncherState(launcher, LAUNCHER_STATE_ROBOT_MOVED);
}

// CHECKS

void checkElectronLauncher2019RobotPlaced(ElectronLauncher2019* launcher) {
    if (launcher == NULL) {
        writeError(ELECTRON_LAUNCHER_2019_NULL);
        return;
    }
    if (launcher->state != LAUNCHER_STATE_SEARCH_ROBOT_PLACED) {
        return;
    }
    TofSensor* tofSensor = launcher->tofSensor;
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return;
    }
    launcher->robotPlacedAnalysisCount++;
    tofSensor->thresholdMinDistanceMM = ELECTRON_LAUNCHER_2019_ROBOT_PLACED_DISTANCE_MIN;
    tofSensor->thresholdMaxDistanceMM = ELECTRON_LAUNCHER_2019_ROBOT_PLACED_DISTANCE_MAX;
    
    unsigned int distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
    if (isTofDistanceInRange(tofSensor)) {
        // We only notify one time
        appendStringAndDec(getAlwaysOutputStreamLogger(), "ROBOT PLACED:", distanceMM);
        appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");
        updateElectronLauncherState(launcher, LAUNCHER_STATE_ROBOT_PLACED);
    }
}

void checkElectronLauncher2019RobotMoved(ElectronLauncher2019* launcher) {
    if (launcher == NULL) {
        writeError(ELECTRON_LAUNCHER_2019_NULL);
        return;
    }
    if (launcher->state != LAUNCHER_STATE_SEARCH_ROBOT_MOVED) {
        return;
    }
    TofSensor* tofSensor = launcher->tofSensor;
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return;
    }
    launcher->robotMovedAnalysisCount++;
    unsigned int distanceMM = 0;
    distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
    tofSensor->thresholdMinDistanceMM = ELECTRON_LAUNCHER_2019_ROBOT_MOVED_DISTANCE_MIN;
    tofSensor->thresholdMaxDistanceMM = ELECTRON_LAUNCHER_2019_ROBOT_MOVED_DISTANCE_MAX;
    
    if (isTofDistanceInRange(tofSensor)) {
        launcher->robotMovedDetectionCount++;
        // Store how many Count the detect
        if (launcher->robotMovedDetectionCount >= ELECTRON_LAUNCHER_2019_THRESHOLD_COUNT) {
            appendStringAndDec(getAlwaysOutputStreamLogger(), "ROBOT MOVED:", distanceMM);
            appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");
            updateElectronLauncherState(launcher, LAUNCHER_STATE_ROBOT_MOVED);
        }
    }
    else {
        if (launcher->robotMovedDetectionCount > 0) {
            launcher->robotMovedDetectionCount--;
        }
    }
}

void checkElectronLauncher2019ToLaunch(ElectronLauncher2019* launcher) {
    if (launcher == NULL) {
        writeError(ELECTRON_LAUNCHER_2019_NULL);
        return;
    }
    if (launcher->state != LAUNCHER_STATE_TO_LAUNCH) {
        return;
    }
    // We show first, because in case of reboot (energy problem or other)
    // we will gain the points
    electronLauncher2019Show(launcher);
    // Do the actions !
    electronLauncher2019Launch(launcher);
}

void checkElectronLauncher2019ShowRemainingTime(ElectronLauncher2019* launcher) {
    if (launcher == NULL) {
        writeError(ELECTRON_LAUNCHER_2019_NULL);
        return;
    }
    if (launcher->state != LAUNCHER_STATE_SHOW_REMAINING_TIME) {
        return;
    }
    EndMatch* endMatch = launcher->endMatch;
    if (endMatch == NULL) {
        writeError(ROBOT_END_MATCH_NULL);
    }
    showRemainingTime(endMatch, getAlwaysOutputStreamLogger());
}

// ACTIONS

void electronLauncher2019Launch(ElectronLauncher2019* launcher) {
    if (launcher == NULL) {
        writeError(ELECTRON_LAUNCHER_2019_NULL);
        return;
    }
    ServoList* servoList = launcher->servoList;
    Servo* electronServo = getServo(servoList, ELECTRON_LAUNCHER_2019_ELECTRON_SERVO_INDEX);
    unsigned int tryCount = 0;
    for (tryCount = 0; tryCount < ELECTRON_LAUNCHER_2019_RELEASE_TRY_COUNT; tryCount++) {
        pwmServo(electronServo, PWM_SERVO_SPEED_MAX, ELECTRON_LAUNCHER_2019_ELECTRON_RELEASE_SERVO_VALUE, true);
        pwmServo(electronServo, PWM_SERVO_SPEED_MAX, ELECTRON_LAUNCHER_2019_ELECTRON_LOCKED_SERVO_VALUE, true);
    }
    updateElectronLauncherState(launcher, LAUNCHER_STATE_LAUNCHED);
    markStartMatch(launcher->endMatch);
}

void electronLauncher2019Show(ElectronLauncher2019* launcher) {
    if (launcher == NULL) {
        writeError(ELECTRON_LAUNCHER_2019_NULL);
        return;
    }
    appendStringCRLF(getAlwaysOutputStreamLogger(), "SHOW : ");
    ServoList* servoList = launcher->servoList;
    Servo* experienceShowServo = getServo(servoList, ELECTRON_LAUNCHER_2019_EXPERIENCE_SHOW_SERVO_INDEX);
    pwmServo(experienceShowServo, PWM_SERVO_SPEED_MAX, ELECTRON_LAUNCHER_2019_EXPERIENCE_SHOW_VALUE, false);
}

void electronLauncher2019Reset(ElectronLauncher2019* launcher) {
    if (launcher == NULL) {
        writeError(ELECTRON_LAUNCHER_2019_NULL);
        return;
    }
    if (launcher == NULL) {
        writeError(ELECTRON_LAUNCHER_2019_NULL);
        return;
    }
    launcher->robotPlacedAnalysisCount = 0;
    launcher->robotMovedAnalysisCount = 0;
    launcher->robotMovedDetectionCount = 0;
    ServoList* servoList = launcher->servoList;
    if (servoList == NULL) {
        writeError(SERVO_LIST_NOT_INITIALIZED);
        return;
    }

    // Experience
    Servo* electronServo = getServo(servoList, ELECTRON_LAUNCHER_2019_ELECTRON_SERVO_INDEX);
    pwmServo(electronServo, PWM_SERVO_SPEED_MAX, ELECTRON_LAUNCHER_2019_ELECTRON_LOCKED_SERVO_VALUE, true);
    electronServo->maxSpeedUnderLoad = MAX_SPEED_UNDER_LOAD__1_SECOND_60_DEG;
    
    // Experience
    Servo* experienceShowServo = getServo(servoList, ELECTRON_LAUNCHER_2019_EXPERIENCE_SHOW_SERVO_INDEX);
    pwmServo(experienceShowServo, PWM_SERVO_SPEED_MAX, ELECTRON_LAUNCHER_2019_EXPERIENCE_INIT_VALUE, true);
    experienceShowServo->maxSpeedUnderLoad = MAX_SPEED_UNDER_LOAD__1_SECOND_60_DEG;
    updateElectronLauncherState(launcher, LAUNCHER_STATE_INITIALIZED);
}

// TIMER INTERRUPT


/**
 * The interrupt timer.
 */
void electronLauncher2019CallbackFunc(Timer* timer) {
    ElectronLauncher2019* launcher = (ElectronLauncher2019*)timer->object;
    if (launcher == NULL) {
        writeError(ELECTRON_LAUNCHER_2019_NULL);
        return;
    }
    launcher->doNextAction = true;
}

// INIT

void initElectronLauncher2019(ElectronLauncher2019* launcher,
    EndMatch* endMatch,
    RobotConfig* robotConfig,
    ServoList* servoList,
    TofSensorList* tofSensorList) {
    launcher->endMatch = endMatch;
    launcher->robotConfig = robotConfig;
    launcher->servoList = servoList;
    launcher->tofSensorList = tofSensorList;
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
        timer = addTimer(ELECTRON_LAUNCHER_2019_TIMER_CODE,
            TIME_DIVIDER_1_HERTZ,
            &electronLauncher2019CallbackFunc,
            "ELEC LAUNC 2019",
            (int*)launcher);
        timer->enabled = true;
    }
    electronLauncher2019Reset(launcher);
}



// MAIN METHOD

void handleElectronLauncherActions(ElectronLauncher2019* launcher) {

    if (!launcher->doNextAction) {
        return;
    }

    if (launcher->state == LAUNCHER_STATE_INITIALIZED) {
        updateElectronLauncherState(launcher, LAUNCHER_STATE_SEARCH_ROBOT_PLACED);
        return;
    }
    if (launcher->state == LAUNCHER_STATE_ROBOT_PLACED) {
        updateElectronLauncherState(launcher, LAUNCHER_STATE_SEARCH_ROBOT_MOVED);
        return;
    }
    if (launcher->state == LAUNCHER_STATE_ROBOT_MOVED) {
        updateElectronLauncherState(launcher, LAUNCHER_STATE_TO_LAUNCH);
        return;
    }
    if (launcher->state == LAUNCHER_STATE_LAUNCHED) {
        updateElectronLauncherState(launcher, LAUNCHER_STATE_SHOW_REMAINING_TIME);
        return;
    }
    // Show the distance
    TofSensor* tofSensor = launcher->tofSensor;
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return;
    }
    unsigned distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
    appendStringAndDec(getAlwaysOutputStreamLogger(), "DIST=", distanceMM);
    appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");

    checkElectronLauncher2019RobotPlaced(launcher);
    checkElectronLauncher2019RobotMoved(launcher);
    checkElectronLauncher2019ToLaunch(launcher);
    checkElectronLauncher2019ShowRemainingTime(launcher);
    
    // Avoid to do it in continous mode
    launcher->doNextAction = false;

}