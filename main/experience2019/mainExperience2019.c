#include "../../common/commons.h"

#include <stdbool.h>

// SPECIFIC TO PIC
#include "../../common/setup/32/picSetup32.h"
#include <plib.h>
#include "mainExperience2019.h"
#include "../../robot/config/32/robotConfigPic32.h"
#include "../../robot/match/32/startMatchDetector32.h"

#include "../../common/delay/cenDelay.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"
#include "../../common/log/logger.h"


#include "../../common/system/system.h"
#include "../../device/deviceList.h"

// COMMON PART
#include "../mainBoard/mainBoardCommon.h"
#include "../mainBoard/mainBoardCommonLcd.h"
#include "../mainBoard/mainBoardCommonMatch.h"
#include "../mainBoard/mainBoardCommonTof.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusConnectionList.h"

// 2019 Specific
#include "../../drivers/tof/tofList.h"
#include "../../drivers/tof/tof.h"

// Robot Configuration
static RobotConfig robotConfig;

/**
 * @private
 */
void initMainBoardDevicesDescriptor() {
    mainBoardCommonInitDeviceListArray();

    mainBoardCommonAddDevices(&robotConfig);
    mainBoardCommonLcdAddDevices();
    mainBoardCommonTofAddDevices();

    // Call the init on each devices
    initDevices();
}

void initMainBoardDriverDataDispatcherList(void) {
    mainBoardCommonInitDriverDataDispatcherList();
}

/**
 * EARLY INIT. In this stage, we have NO WAY to have LOGS if a problem occurs
 * @return 
 */
void mainBoardMainPhase1(void) {
    setBoardName("EXPERIENCE 2019");
 
    // CONFIG
    initRobotConfigPic32(&robotConfig, ROBOT_TYPE_EXPERIENCE_2019);
    
    // BASE LOGS
    mainBoardCommonInitLogs();
    
    // LCD
    mainBoardCommonLcdInit(&robotConfig);

    // SERIAL
    mainBoardCommonInitSerialList();
    mainBoardCommonDebugOpenSerialLink(); 
}

/**
 * DRIVERS MAIN INIT.
 */
void mainBoardMainPhase2(void) {
    mainBoardCommonMainInit(&robotConfig);
    
   
    mainBoardCommonInitBusList();
    mainBoardCommonInitTimerList();
    mainBoardCommonInitCommonDrivers();

    mainBoardCommonTofInitDrivers(mainBoardCommonGetMainI2cBus(), MAIN_EXPERIENCE_2019_TOF_SENSOR_LIST_COUNT);
}

void mainBoardMainPhase3(void) {
    initMainBoardDevicesDescriptor();
    initMainBoardDriverDataDispatcherList();
}

int main(void) {
    mainBoardMainPhase1();
    mainBoardMainPhase2();
    mainBoardMainPhase3();
    
    unsigned int tofIndex = 0;
    if (isConfigSet(&robotConfig, CONFIG_COLOR_YELLOW_MASK)) {
        appendStringCRLF(getAlwaysOutputStreamLogger(), "YELLOW->RIGHT");
        tofIndex = 0;
    }
    else {
        appendStringCRLF(getAlwaysOutputStreamLogger(), "VIOLET->LEFT");
        tofIndex = 1;
    }
        
    TofSensorList* tofSensorList = mainBoardCommonTofGetTofSensorList();
    TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
    
    bool robotPlaced = false;
    bool robotMoved = false;

    ServoList* servoList = mainBoardCommonGetServoList();
    Servo* electronServo = getServo(servoList, 0);
    Servo* experienceShowServo = getServo(servoList, 1);

    while (true) {
        mainBoardCommonHandleStreamInstruction();

        unsigned int distanceMM = tofSensor->tofGetDistanceMM(tofSensor);
        if (distanceMM > 450.0f && distanceMM < 600.0f) {
            // We only notify one time
            if (!robotPlaced) {
                robotPlaced = true;
                appendStringAndDecf(getAlwaysOutputStreamLogger(), "ROBOT OK : ", distanceMM);
                appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");
            }
        }
        if (robotPlaced) {
            // The action will be done only one time
            if (distanceMM > 800.0f && !robotMoved) {
                appendStringAndDecf(getAlwaysOutputStreamLogger(), "GO : ", distanceMM);
                appendStringCRLF(getAlwaysOutputStreamLogger(), " mm");
                robotMoved = true;
                unsigned int tryCount = 0;
                pwmServo(experienceShowServo, PWM_SERVO_SPEED_MAX, 800);
                delaymSec(500);
                for (tryCount = 0; tryCount < 5; tryCount++) {
                    pwmServo(electronServo, PWM_SERVO_SPEED_MAX, 650);
                    delaymSec(1000);
                    pwmServo(electronServo, PWM_SERVO_SPEED_MAX, 1500);
                    delaymSec(500);
                }
            }
        }
    }
}
