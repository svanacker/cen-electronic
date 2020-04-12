#include "lightHouse2020.h"
#include "lightHouse2020Debug.h"

#include <stdlib.h>

#include "../../../common/error/error.h"

#include "../../../common/pwm/servo/servoList.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/log/logger.h"

#include "../../../common/motor/dualHBridgeMotor.h"

#include "../../../common/timer/timerConstants.h"
#include "../../../common/timer/delayTimer.h"
#include "../../../common/timer/timerList.h"

#include "../../../client/motor/clientMotor.h"

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
    } else {
        OutputStream* outputStream = getDebugOutputStreamLogger();
        printLightHouseState(outputStream, lightHouse->state);
        lightHouse->state = newState;
        appendString(outputStream, "-->");
        printLightHouseState(outputStream, lightHouse->state);
        appendCRLF(outputStream);
    }
}

// CHECKS
 
void checkLightHouse2020RobotPlaced(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse->state != LIGHT_HOUSE_STATE_SEARCH_IF_PLACED) {
        return;
    }
    TofSensor* tofSensor = lightHouse->tofSensor;
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return;
    }
    lightHouse->robotPlacedAnalysisCount++;
    tofSensor->thresholdMinDistanceMM = LIGHT_HOUSE_2020_ROBOT_NO_TOUCH_DISTANCE_MIN;
    tofSensor->thresholdMaxDistanceMM = LIGHT_HOUSE_2020_ROBOT_NO_TOUCH_DISTANCE_MAX;

    unsigned int distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
    if (isTofDistanceInRange(tofSensor)) {
        // We only notify one time
        appendStringAndDec(getAlwaysOutputStreamLogger(), "PLACED:", distanceMM);
        appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_PLACED);
    }
}

void checkLightHouse2020RobotTouch(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    if (lightHouse->state != LIGHT_HOUSE_STATE_SEARCH) {
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
    tofSensor->thresholdMinDistanceMM = LIGHT_HOUSE_2020_ROBOT_TOUCH_DISTANCE_MIN;
    tofSensor->thresholdMaxDistanceMM = LIGHT_HOUSE_2020_ROBOT_TOUCH_DISTANCE_MAX;

    if (isTofDistanceInRange(tofSensor)) {
        lightHouse->robotNearDetectionCount++;
        // Store how many Count the detect
        if (lightHouse->robotNearDetectionCount >= LIGHT_HOUSE_2020_THRESHOLD_COUNT) {
            appendStringAndDec(getAlwaysOutputStreamLogger(), "ROBOT TOUCH:", distanceMM);
            appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");
            updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_LAUNCHED);
        }
    } else {
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
    if (lightHouse->timerCount % 10 == 0) {
        showRemainingTime(endMatch, getAlwaysOutputStreamLogger());
    }
}

// ACTIONS

void lightHouse2020Up(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    clientMotorWrite(0, LIGHT_HOUSE_2020_MOTOR_FORWARD_SPEED);
}

void lightHouse2020Bottom(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    clientMotorWrite(0, LIGHT_HOUSE_2020_MOTOR_BACKWARD_SPEED);
}

void lightHouse2020On(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    clientMotorWrite(LIGHT_HOUSE_2020_LIGHT_ON_VALUE, 0);
}

void lightHouse2020Off(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    clientMotorStop();
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
    // Set the Pin Management on Motor Board
    clientMotorSetPinUsage(PIN_USAGE_TYPE_MOTOR_2_BACKWARD_END, 
                           PIN_USAGE_TYPE_MOTOR_2_FORWARD_END,
                           PIN_STOP_EVENT_HIGH_STOP,
                           PIN_STOP_EVENT_HIGH_STOP);

    // State
    updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_INITIALIZED);
}

// TIMER INTERRUPT

/**
 * The interrupt timer.
 */
void lightHouse2020CallbackFunc(Timer* timer) {
    LightHouse2020* lightHouse = (LightHouse2020*) timer->object;
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    lightHouse->doNextAction = true;
    lightHouse->timerCount++;

    ServoList* servoList = lightHouse->servoList;
    Servo* servo = getServo(servoList, LIGHT_HOUSE_2020_SERVO_INDEX);

    // To initialize rotation
    unsigned int servoTargetPosition = pwmServoReadTargetPosition(servo);
    if (servoTargetPosition != LIGHT_HOUSE_2020_SERVO_LEFT_VALUE && servoTargetPosition != LIGHT_HOUSE_2020_SERVO_RIGHT_VALUE) {
        pwmServo(servo, LIGHT_HOUSE_2020_SERVO_SPEED, LIGHT_HOUSE_2020_SERVO_LEFT_VALUE, false);
    }

    unsigned int servoCurrentPosition = pwmServoReadCurrentPosition(servo);

    // Change sense when reaching current
    if (servoCurrentPosition >= LIGHT_HOUSE_2020_SERVO_RIGHT_VALUE) {
        pwmServo(servo, LIGHT_HOUSE_2020_SERVO_SPEED, LIGHT_HOUSE_2020_SERVO_LEFT_VALUE, false);
    } else if (servoCurrentPosition <= LIGHT_HOUSE_2020_SERVO_LEFT_VALUE) {
        pwmServo(servo, LIGHT_HOUSE_2020_SERVO_SPEED, LIGHT_HOUSE_2020_SERVO_RIGHT_VALUE, false);
    }
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
    /*
    if (isConfigSet(robotConfig, CONFIG_COLOR_YELLOW_MASK)) {
        appendStringCRLF(getAlwaysOutputStreamLogger(), "YELLOW->RIGHT");
        lightHouse->tofIndex = 0;
    } else {
        appendStringCRLF(getAlwaysOutputStreamLogger(), "VIOLET->LEFT");
        lightHouse->tofIndex = 1;
    }
    */
    TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, lightHouse->tofIndex);
    lightHouse->tofSensor = tofSensor;
    Timer* timer = getTimerByCode(LIGHT_HOUSE_2020_TIMER_CODE);
    if (timer == NULL) {
        timer = addTimer(LIGHT_HOUSE_2020_TIMER_CODE,
                TIME_DIVIDER_10_HERTZ,
                &lightHouse2020CallbackFunc,
                "LIGHT HOUSE 2020",
                (int*) lightHouse);
        timer->enabled = true;
    }
}



// MAIN METHOD

void handleLightHouseActions(LightHouse2020* lightHouse) {
    if (!lightHouse->doNextAction) {
        return;
    }

    if (lightHouse->state == LIGHT_HOUSE_STATE_INITIALIZED) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_SEARCH_IF_PLACED);
        return;
    }
    if (lightHouse->state == LIGHT_HOUSE_STATE_SEARCH_IF_PLACED) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_PLACED);
        return;
    }
    if (lightHouse->state == LIGHT_HOUSE_STATE_PLACED) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_SEARCH);
        return;
    }
    if (lightHouse->state == LIGHT_HOUSE_STATE_SEARCH) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_SEARCH_OK);
        return;
    }
    if (lightHouse->state == LIGHT_HOUSE_STATE_SEARCH_OK) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_TO_LAUNCH);
        return;
    }
    
    if (lightHouse->state == LIGHT_HOUSE_STATE_TO_LAUNCH) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_LAUNCHED);
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
    checkLightHouse2020RobotTouch(lightHouse);
    checkLightHouse2020ToLaunch(lightHouse);
    checkLightHouse2020ShowRemainingTime(lightHouse);

    // Avoid to do it in continous mode
    lightHouse->doNextAction = false;
}