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
#include "../../robot/2019/electronLauncher2019.h"
#include "../../robot/2019/electronLauncherDevice2019.h"
#include "../../robot/2019/electronLauncherDeviceInterface2019.h"

// Robot Configuration
static RobotConfig robotConfig;
static ElectronLauncher2019 launcher;

/**
 * @private
 */
void initMainBoardDevicesDescriptor() {
    mainBoardCommonInitDeviceListArray();

    mainBoardCommonAddDevices(&robotConfig);
    mainBoardCommonLcdAddDevices();
    mainBoardCommonTofAddDevices();
    
    // 2019 specific
    addLocalDevice(getElectronLauncher2019DeviceInterface(), getElectronLauncher2019DeviceDescriptor(&launcher));


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
    
    // 2019 specific
    initElectronLauncher2019(&launcher, 
                             &robotConfig,
                             mainBoardCommonGetServoList(),
                             mainBoardCommonTofGetTofSensorList());
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
        
        handleElectronLauncherActions(&launcher);
    }
}
