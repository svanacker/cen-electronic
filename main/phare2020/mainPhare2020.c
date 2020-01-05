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

#include "../../main/phare2020/mainPhare2020Tof.h"

#include "../../robot/2020/lightHouse/lightHouse2020.h"
#include "../../robot/2020/lightHouse/lightHouseDevice2020.h"
#include "../../robot/2020/lightHouse/lightHouseDeviceInterface2020.h"

#include "../../robot/match/endMatch.h"
#include "../../robot/match/endMatchDebug.h"
#include "../../robot/match/endMatchDetectorDevice.h"
#include "../../robot/match/endMatchDetectorDeviceInterface.h"


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
    mainLightHouse2020TofAddDevices();
    
    // 2020 specific
    addLocalDevice(getLightHouse2020DeviceInterface(), getLightHouse2020DeviceDescriptor(&lightHouse));
    
    addLocalDevice(getEndMatchDetectorDeviceInterface(), getEndMatchDetectorDeviceDescriptor(&endMatch));

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

    initEndMatch(&endMatch, &robotConfig, MATCH_DURATION);
}

void mainBoardMainPhase3(void) {
    initMainBoardDevicesDescriptor();
    initMainBoardDriverDataDispatcherList();
}

int main(void) {
    mainBoardMainPhase1();
    mainBoardMainPhase2();
    mainBoardMainPhase3();
    
    while (true) {
        mainBoardCommonHandleStreamInstruction();
        
        /// handleLightHouseActions(&lightHouse);
    }
}
