#include "../../common/commons.h"

// SPECIFIC TO PIC
#include "../../common/setup/32/picSetup32.h"
#include <plib.h>
#include "mainBoardSmall32.h"
#include "../../robot/config/32/robotConfigPic32.h"
#include "../../robot/match/32/startMatchDetector32.h"

#include "../../common/delay/cenDelay.h"
#include "../../common/io/printWriter.h"
#include "../../common/log/logger.h"


#include "../../common/system/system.h"
#include "../../device/deviceList.h"

// COMMON PART
#include "../mainBoard/mainBoardCommon.h"
#include "../mainBoard/mainBoardCommonLcd.h"
#include "../mainBoard/mainBoardCommonMatch.h"
#include "../mainBoard/mainBoardCommonMeca1.h"
#include "../mainBoard/mainBoardCommonMotor.h"
#include "../mainBoard/mainBoardCommonStrategy.h"
#include "../mainBoard/mainBoardCommonTof.h"

#include "../../drivers/pwm/servo/servoPwmPca9685.h"
#include "../../drivers/pwm/servo/pca9685.h"
#include "../../drivers/accelerometer/adxl345.h"
#include "../../drivers/accelerometer/adxl345Debug.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusConnectionList.h"
#include "printTableWriter.h"

// SMALL ROBOT PART
#include "../../drivers/pwm/servo/servoPwmPca9685.h"
#include "../../robot/2019/arm/armDeviceInterface2019.h"
#include "../../robot/2019/arm/armDevice2019.h"
#include "../../robot/2019/distributor/distributorDeviceInterface2019.h"
#include "../../robot/2019/distributor/distributorDevice2019.h"
#include "../../robot/2019/elevator/elevatorDevice2019.h"
#include "../../robot/2019/elevator/elevatorDeviceInterface2019.h"
#include "../../robot/2019/elevator/elevatorDevice2019.h"
#include "../../robot/2019/fork/forkDeviceInterface2019.h"
#include "../../robot/2019/fork/forkDevice2019.h"
#include "../../robot/2019/goldenium/goldeniumDeviceInterface2019.h"
#include "../../robot/2019/goldenium/goldeniumDevice2019.h"


#include "../../robot/2019/strategy/strategyConfig2019.h"

// Robot Configuration
static RobotConfig robotConfig;

/**
 * @private
 */
void initMainBoardDevicesDescriptor() {
    mainBoardCommonInitDeviceListArray();

    mainBoardCommonAddDevices(&robotConfig);
    mainBoardCommonLcdAddDevices();
    mainBoardCommonMotorAddDevices(MAIN_BOARD_SERIAL_PORT_MOTOR);
    mainBoardCommonStrategyAddDevices(MAIN_BOARD_SERIAL_PORT_MOTOR);
    mainBoardCommonTofAddDevices();
    mainBoardCommonMeca1AddDevices();

    // Call the init on each devices
    initDevices();
}

void initMainBoardDriverDataDispatcherList(void) {
    mainBoardCommonInitDriverDataDispatcherList();
 
    mainBoardCommonMotorAddDispatcher();    
    // mainBoardCommonMeca1AddDispatcher();
}

bool mainBoardWaitForInstruction(StartMatch* startMatchParam) {
    // loop for all notification
    // notification handler must avoid to handle directly information in notification callback
    // and never to the call back device
    mainBoardCommonHandleStreamInstruction();
    // mainBoardCommonHandleAccelerometer();
    mainBoardCommonMotorHandleStreamInstruction();
    mainBoardCommonStrategyHandleStreamInstruction();

    return true;
}

bool loopUnWaitForInstruction(StartMatch* startMatchParam) {
    // We do the same function before or after the start of match
    return mainBoardWaitForInstruction(startMatchParam);
}

/**
 * EARLY INIT. In this stage, we have NO WAY to have LOGS if a problem occurs
 * @return 
 */
void mainBoardMainPhase1(void) {
    setBoardName("MAIN SMALL ROBOT 32");
 
    // CONFIG
    initRobotConfigPic32(&robotConfig, ROBOT_TYPE_SMALL);
    
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
    
    // OTHER SERIAL LINKS
    mainBoardCommonMotorNotifyOpenSerialLink();
    mainBoardCommonMotorOpenSerialLink();
   
    mainBoardCommonInitBusList();
    mainBoardCommonInitTimerList();
    mainBoardCommonInitCommonDrivers();

    // ROBOT2019 : PCA9685
    ServoList* servoList = mainBoardCommonGetServoList();
    // I2cBus* i2cBus = mainBoardCommonGetMainI2cBus();
    I2cBus* i2cBus = getI2cBusByIndex(MAIN_BOARD_SERVO_I2C_BUS_INDEX);
    I2cBusConnection* servoI2cBusConnection = addI2cBusConnection(i2cBus, PCA9685_ADDRESS_0, true);
    addServoAllPca9685(servoList, servoI2cBusConnection);

    // Initialise the Strategy first so that we could show the color & stragegy
    // index at a very early stage
    mainBoardCommonStrategyMainInitDrivers(&robotConfig);

    mainBoardCommonTofInitDrivers(&robotConfig);
    mainBoardCommonMatchMainInitDrivers(&robotConfig, isMatchStarted32, mainBoardWaitForInstruction, loopUnWaitForInstruction);
}

void mainBoardMainPhase3(void) {
    initMainBoardDevicesDescriptor();
    initMainBoardDriverDataDispatcherList();

    mainBoardCommonMotorMainEndInit();
    mainBoardCommonStrategyMainEndInit();
}

int main(void) {
    mainBoardMainPhase1();
    mainBoardMainPhase2();
    mainBoardMainPhase3();
    
    TofSensorList* tofSensorList = mainBoardCommonTofGetTofSensorList();
    ServoList* servoList = mainBoardCommonGetServoList();
	addLocalDevice(getArm2019DeviceInterface(), getArm2019DeviceDescriptor(servoList));
	addLocalDevice(getElevator2019DeviceInterface(), getElevator2019DeviceDescriptor(servoList));
    addLocalDevice(getFork2019DeviceInterface(), getFork2019DeviceDescriptor(servoList, tofSensorList));
    addLocalDevice(getDistributor2019DeviceInterface(), getDistributor2019DeviceDescriptor(servoList, tofSensorList));
    addLocalDevice(getGoldenium2019DeviceInterface(), getGoldenium2019DeviceDescriptor(servoList, tofSensorList));
   
    mainBoardCommonStrategyMainLoop();

    while (true) {
        // Avoid reboot even at end
    }
}
