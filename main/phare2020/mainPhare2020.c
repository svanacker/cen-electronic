#include "mainPhare2020.h"

#include "../../common/commons.h"

#include <stdbool.h>

// SPECIFIC TO PIC
#include "../../common/setup/32/picSetup32.h"
#include <plib.h>
#include "../../robot/config/32/robotConfigPic32.h"
#include "../../robot/match/32/startMatchDetector32.h"

#include "../../common/delay/cenDelay.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"
#include "../../common/log/logger.h"


#include "../../common/system/system.h"
#include "../../device/deviceList.h"

#include "../../device/io/ioDevice.h"
#include "../../device/io/ioDeviceInterface.h"

// COMMON PART
#include "../mainBoard/mainBoardCommon.h"
#include "../mainBoard/mainBoardCommonLcd.h"
#include "../mainBoard/mainBoardCommonMatch.h"
#include "../mainBoard/mainBoardCommonMotor.h"
#include "../mainBoard/mainBoardCommonTof.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusConnectionList.h"

// 2019 Specific
#include "../../drivers/tof/tofList.h"
#include "../../drivers/tof/tof.h"

#include "../../main/phare2020/mainPhare2020Tof.h"

#include "../../robot/2020/lightHouse/lightHouse2020.h"
#include "../../robot/2020/lightHouse/lightHouseDevice2020.h"
#include "../../robot/2020/lightHouse/lightHouseDeviceInterface2020.h"

#include "../../robot/match/endMatch.h"
#include "../../robot/match/endMatchDebug.h"
#include "../../robot/match/endMatchDetectorDevice.h"
#include "../../robot/match/endMatchDetectorDeviceInterface.h"
#include "io/ioDeviceInterface.h"
#include "2020/lightHouse/lightHouse2020Workflow.h"


// Robot Configuration
static RobotConfig robotConfig;
static LightHouse2020 lightHouse;
static EndMatch endMatch;

/**
 * @private
 */
void initMainBoardDevicesDescriptor() {
    mainBoardCommonInitDeviceListArray();

    mainBoardCommonAddDevices(&robotConfig);
    mainBoardCommonLcdAddDevices();
    mainBoardCommonMotorAddDevices(MAIN_BOARD_SERIAL_PORT_MOTOR);

    mainLightHouse2020TofAddDevices();

    // 2020 specific
    addLocalDevice(getLightHouse2020DeviceInterface(), getLightHouse2020DeviceDescriptor(&lightHouse));

    addLocalDevice(getEndMatchDetectorDeviceInterface(), getEndMatchDetectorDeviceDescriptor(&endMatch));

    // Call the init on each devices
    initDevices();
}

void initMainBoardDriverDataDispatcherList(void) {
    mainBoardCommonInitDriverDataDispatcherList();
    mainBoardCommonMotorAddDispatcher();
}

/**
 * EARLY INIT. In this stage, we have NO WAY to have LOGS if a problem occurs
 * @return 
 */
void mainBoardMainPhase1(void) {
    setBoardName("LIGHT HOUSE 2020");

    // CONFIG
    initRobotConfigPic32(&robotConfig, ROBOT_TYPE_LIGHTHOUSE_2020);

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

    // Notify is mandatory even if we don't use it
    mainBoardCommonMotorNotifyOpenSerialLink();
    mainBoardCommonMotorOpenSerialLink();

    mainBoardCommonInitBusList();
    mainBoardCommonInitTimerList();
    mainBoardCommonInitCommonDrivers();

    TofSensorList* tofSensorList = mainLightHouse2020TofInitDrivers(mainBoardCommonGetAlternativeI2cBus());

    // 2020 specific
    initLightHouse2020(&lightHouse,
            &endMatch,
            &robotConfig,
            mainBoardCommonGetServoList(),
            tofSensorList);

    initEndMatch(&endMatch, &robotConfig, MATCH_DURATION, NULL);
}

void mainBoardMainPhase3(void) {
    initMainBoardDevicesDescriptor();
    initMainBoardDriverDataDispatcherList();
    
    lightHouse2020ResetWorkflow(&lightHouse);
}

void lightHouse2020PinChangedCallback(bool pinValue1, bool pinValue2) {
    // PinValue1 to High means that back sensor touch -> At the bottom
    if (pinValue1) {
        if (lightHouse.state == LIGHT_HOUSE_STATE_INIT_GOING_DOWN) {
            updateLightHouseState(&lightHouse, LIGHT_HOUSE_STATE_SEARCH_IF_PLACED);
        }
    }
    // PinValue2 to High means that forward sensor touch -> At the end
    if (pinValue2) {
        if (lightHouse.state == LIGHT_HOUSE_STATE_LAUNCHED) {
            updateLightHouseState(&lightHouse, LIGHT_HOUSE_STATE_SHOW_REMAINING_TIME);
        }
    }
}

int main(void) {
    mainBoardMainPhase1();
    mainBoardMainPhase2();
    mainBoardMainPhase3();

    registerPinChangedCallback(&lightHouse2020PinChangedCallback);
    
    while (true) {
        mainBoardCommonHandleStreamInstruction();
        mainBoardCommonMotorHandleStreamInstruction();

        handleLightHouseActions(&lightHouse);
        
        ServoList* servoList = mainBoardCommonGetServoList();
        servoListMainUpdateCall(servoList);
    }
}
