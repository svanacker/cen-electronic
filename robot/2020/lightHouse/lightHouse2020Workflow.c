#include "lightHouse2020Workflow.h"
#include "lightHouse2020.h"

#include "lightHouse2020Actions.h"
#include "lightHouse2020CheckRobotPlaced.h"
#include "lightHouse2020CheckRobotTouched.h"
#include "lightHouse2020CheckRobotLaunched.h"
#include "lightHouse2020CheckShowRemainingTime.h"
#include "lightHouse2020Workflow.h"
#include "lightHouse2020Debug.h"

#include <stdlib.h>

#include "../../../common/error/error.h"

#include "../../../common/pwm/servo/servoList.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/io/pin.h"

#include "../../../common/log/logger.h"

#include "../../../common/timer/timerConstants.h"
#include "../../../common/timer/delayTimer.h"
#include "../../../common/timer/timerList.h"

#include "../../../robot/config/robotConfig.h"

#include "../../../robot/match/endMatch.h"

#include "../../../client/motor/clientMotor.h"

#include "../../../drivers/tof/tofDetectionUtils.h"
#include "lightHouse2020CheckRobotBottom.h"

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
    lightHouse->doNextAction = true;
} 

// MAIN METHOD (WORKFLOW)

void handleLightHouseActions(LightHouse2020* lightHouse) {
    /*
    if (!lightHouse->doNextAction) {
        return;
    }
    */
    // INIT
    if (lightHouse->state == LIGHT_HOUSE_STATE_INITIALIZED) {
        // We must init 
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_INIT_POSITION_BOTTOM);
        return;
    }
    // PLACED
    if (lightHouse->state == LIGHT_HOUSE_STATE_PLACED) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_SEARCH_TOUCH);
        return;
    }
    // TOUCHED
    if (lightHouse->state == LIGHT_HOUSE_STATE_TOUCHED) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_TO_LAUNCH);
        return;
    }
    // REMAINING TIME
    if (lightHouse->state == LIGHT_HOUSE_STATE_LAUNCHED) {
        updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_SHOW_REMAINING_TIME);
        return;
    }

    checkLightHouse2020RobotBottom(lightHouse);
    checkLightHouse2020RobotPlaced(lightHouse);
    checkLightHouse2020RobotTouched(lightHouse);
    checkLightHouse2020ToLaunch(lightHouse);
    checkLightHouse2020ShowRemainingTime(lightHouse);

    // Avoid to do it in continous mode
    lightHouse->doNextAction = false;
}

void lightHouse2020ResetWorkflow(LightHouse2020* lightHouse) {
    appendString(getAlwaysOutputStreamLogger(), "INIT WORKFLOW :");
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
    bool ok = clientMotorSetPinUsage(PIN_USAGE_TYPE_MOTOR_2_BACKWARD_END, 
                           PIN_USAGE_TYPE_MOTOR_2_FORWARD_END,
                           PIN_STOP_EVENT_HIGH_STOP,
                           PIN_STOP_EVENT_HIGH_STOP);

    if (ok) {
        appendStringLN(getAlwaysOutputStreamLogger(), "OK");
    }
    else {
        appendStringLN(getAlwaysOutputStreamLogger(), "KO");
    }
    // State
    updateLightHouseState(lightHouse, LIGHT_HOUSE_STATE_INITIALIZED);    
}
