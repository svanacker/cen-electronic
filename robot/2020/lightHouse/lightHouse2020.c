#include "lightHouse2020.h"
#include "lightHouse2020Actions.h"
#include "lightHouse2020CheckRobotPlaced.h"
#include "lightHouse2020CheckRobotTouched.h"
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

#include "../../../drivers/tof/tofDetectionUtils.h"


 
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

    // TOF
    TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, lightHouse->tofIndex);
    lightHouse->tofSensor = tofSensor;
    
    // TIMER
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
