#include "lightHouse2020.h"
#include "lightHouse2020Debug.h"

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

void updateLightHouseState(LightHouse2020* lightHouse, enum LightHouse2020State newState) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse->state == newState) {
        return;
    }
    else {
        OutputStream* outputStream = getDebugOutputStreamLogger();
        printLightHouseState(outputStream, lightHouse->state);
        lightHouse->state = newState;
        appendString(outputStream, "-->");
        printLightHouseState(outputStream, lightHouse->state);
        appendCRLF(outputStream);
    }
}


// SIMULATION

void lightHouse2020SimulateRobotPlaced(LightHouse2020* lightHouse) {
    updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_ROBOT_PLACED);
}

void lightHouse2020SimulateRobotPlacedAndNear(LightHouse2020* lightHouse) {
    updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_ROBOT_NEAR);
}

// CHECKS

void checkLightHouse2020RobotPlaced(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse->state != LIGHT_HOUSE_STATE_SEARCH_ROBOT_PLACED) {
        return;
    }
    TofSensor* tofSensor = lightHouse->tofSensor;
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return;
    }
    lightHouse->robotPlacedAnalysisCount++;
    tofSensor->thresholdMinDistanceMM = LIGHT_HOUSE_2020_ROBOT_PLACED_DISTANCE_MIN;
    tofSensor->thresholdMaxDistanceMM = LIGHT_HOUSE_2020_ROBOT_PLACED_DISTANCE_MAX;
    
    unsigned int distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
    if (isTofDistanceInRange(tofSensor)) {
        // We only notify one time
        appendStringAndDec(getAlwaysOutputStreamLogger(), "ROBOT PLACED:", distanceMM);
        appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_ROBOT_PLACED);
    }
}

void checkLightHouse2020RobotNear(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse->state != LIGHT_HOUSE_STATE_SEARCH_ROBOT_NEAR) {
        return;
    }
    TofSensor* tofSensor = lightHouse->tofSensor;
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return;
    }
    lightHouse->robotNearAnalysisCount++;
    unsigned int distanceMM = 0;
    distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
    tofSensor->thresholdMinDistanceMM = LIGHT_HOUSE_2020_ROBOT_MOVED_DISTANCE_MIN;
    tofSensor->thresholdMaxDistanceMM = LIGHT_HOUSE_2020_ROBOT_MOVED_DISTANCE_MAX;
    
    if (isTofDistanceInRange(tofSensor)) {
        lightHouse->robotNearDetectionCount++;
        // Store how many Count the detect
        if (lightHouse->robotNearDetectionCount >= LIGHT_HOUSE_2020_THRESHOLD_COUNT) {
            appendStringAndDec(getAlwaysOutputStreamLogger(), "ROBOT NEAR:", distanceMM);
            appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");
            updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_ROBOT_NEAR);
        }
    }
    else {
        lightHouse->robotNearDetectionCount -= LIGHT_HOUSE_2020_MISSED_DECREMENT_VALUE;
        if (lightHouse->robotNearDetectionCount < 0) {
            lightHouse->robotNearDetectionCount = 0;
        }
    }
}

void checkLightHouse2020ToLaunch(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse->state != LIGHT_HOUSE_STATE_TO_LAUNCH) {
        return;
    }
    // Do the action
    lightHouse2020Up(lightHouse);
}

void checkLightHouse2020ShowRemainingTime(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse->state != LIGHT_HOUSE_STATE_SHOW_REMAINING_TIME) {
        return;
    }
    EndMatch* endMatch = lightHouse->endMatch;
    if (endMatch == NULL) {
        writeError(ROBOT_END_MATCH_NULL);
    }
    if (lightHouse->timerCount %10 == 0) {
        showRemainingTime(endMatch, getAlwaysOutputStreamLogger());
        
    }
}

// ACTIONS

void lightHouse2020Up(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    /*
    ServoList* servoList = lightHouse->servoList;
    Servo* electronServo = getServo(servoList, LIGHT_HOUSE_2020_ELECTRON_SERVO_INDEX);
    unsigned int tryCount = 0;
    for (tryCount = 0; tryCount < LIGHT_HOUSE_2020_RELEASE_TRY_COUNT; tryCount++) {
        pwmServo(electronServo, PWM_SERVO_SPEED_MAX, LIGHT_HOUSE_2020_ELECTRON_RELEASE_SERVO_VALUE, true);
        pwmServo(electronServo, PWM_SERVO_SPEED_MAX, LIGHT_HOUSE_2020_ELECTRON_LOCKED_SERVO_VALUE, true);
    }
    updateLightHouseState(launcher, LIGHT_HOUSE_STATE_LAUNCHED);
    markStartMatch(lightHouse->endMatch);
    */
}

void lightHouse2020Bottom(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    // TODO
}

void lightHouse2020Reset(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    lightHouse->robotPlacedAnalysisCount = 0;
    lightHouse->robotNearAnalysisCount = 0;
    lightHouse->robotNearDetectionCount = 0;
    ServoList* servoList = lightHouse->servoList;
    if (servoList == NULL) {
        writeError(SERVO_LIST_NOT_INITIALIZED);
        return;
    }

    // Light House
    /*
    Servo* electronServo = getServo(servoList, LIGHT_HOUSE_2020_SERVO_INDEX);
    pwmServo(electronServo, PWM_SERVO_SPEED_MAX, LIGHT_HOUSE_2020_SERVO_LEFT_VALUE, true);
    electronServo->maxSpeedUnderLoad = MAX_SPEED_UNDER_LOAD__1_SECOND_60_DEG;
    */
    
    // State
    updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_INITIALIZED);
}

// TIMER INTERRUPT


/**
 * The interrupt timer.
 */
void lightHouse2020CallbackFunc(Timer* timer) {
    LightHouse2020* lightHouse = (LightHouse2020*)timer->object;
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    lightHouse->doNextAction = true;
    lightHouse->timerCount++;
}

// INIT

void initLightHouse2020(LightHouse2020* lightHouse,
    EndMatch* endMatch,
    RobotConfig* robotConfig,
    ServoList* servoList,
    TofSensorList* tofSensorList) {
    lightHouse->endMatch = endMatch;
    lightHouse->robotConfig = robotConfig;
    lightHouse->servoList = servoList;
    lightHouse->tofSensorList = tofSensorList;
    if (isConfigSet(robotConfig, CONFIG_COLOR_YELLOW_MASK)) {
        appendStringCRLF(getAlwaysOutputStreamLogger(), "YELLOW->RIGHT");
        lightHouse->tofIndex = 0;
    }
    else {
        appendStringCRLF(getAlwaysOutputStreamLogger(), "VIOLET->LEFT");
        lightHouse->tofIndex = 1;
    }
    TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, lightHouse->tofIndex);
    lightHouse->tofSensor = tofSensor;
    Timer* timer = getTimerByCode(LIGHT_HOUSE_2020_TIMER_CODE);
    if (timer == NULL) {
        timer = addTimer(LIGHT_HOUSE_2020_TIMER_CODE,
            TIME_DIVIDER_10_HERTZ,
            &lightHouse2020CallbackFunc,
            "LIGHT HOUSE 2020",
            (int*)lightHouse);
        timer->enabled = true;
    }
    lightHouse2020Reset(lightHouse);
}



// MAIN METHOD

void handleLightHouseActions(LightHouse2020* lightHouse) {
    if (!lightHouse->doNextAction) {
        return;
    }

    if (lightHouse->state == LIGHT_HOUSE_STATE_INITIALIZED) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_SEARCH_ROBOT_PLACED);
        return;
    }
    if (lightHouse->state == LIGHT_HOUSE_STATE_ROBOT_PLACED) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_SEARCH_ROBOT_NEAR);
        return;
    }
    if (lightHouse->state == LIGHT_HOUSE_STATE_ROBOT_NEAR) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_TO_LAUNCH);
        return;
    }
    if (lightHouse->state == LIGHT_HOUSE_STATE_LAUNCHED) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_SHOW_REMAINING_TIME);
        return;
    }
    // Show the distance
    TofSensor* tofSensor = lightHouse->tofSensor;
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return;
    }
    if (lightHouse->timerCount % 10 == 0) {
        unsigned distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
        appendStringAndDec(getAlwaysOutputStreamLogger(), "DIST=", distanceMM);
        appendStringAndDec(getAlwaysOutputStreamLogger(), " mm (", lightHouse->robotNearDetectionCount);
        appendStringLN(getAlwaysOutputStreamLogger(), ")");
    }
    checkLightHouse2020RobotPlaced(lightHouse);
    checkLightHouse2020RobotNear(lightHouse);
    checkLightHouse2020ToLaunch(lightHouse);
    checkLightHouse2020ShowRemainingTime(lightHouse);

    // Avoid to do it in continous mode
    lightHouse->doNextAction = false;
}