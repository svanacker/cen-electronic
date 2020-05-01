#include "../../common/commons.h"

// SPECIFIC TO PIC
#include "../../common/setup/32/picSetup32.h"
#include <plib.h>
#include "mainBoardSmall32.h"
#include "../../robot/config/32/robotConfigPic32.h"
#include "../../robot/match/32/startMatchDetector32.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusConnectionList.h"

#include "../../common/log/logger.h"

#include "../../common/system/system.h"
#include "../../device/deviceList.h"

// COMMON PART
#include "../mainBoard/mainBoardCommon.h"
#include "../mainBoard/mainBoardCommonLcd.h"
#include "../mainBoard/mainBoardCommonIoExpanderList.h"
#include "../mainBoard/mainBoardCommonMatch.h"
#include "../mainBoard/mainBoardCommonMeca1.h"
#include "../mainBoard/mainBoardCommonMotor.h"
#include "../mainBoard/mainBoardCommonMotion.h"
#include "../mainBoard/mainBoardCommonServo.h"
#include "../mainBoard/mainBoardCommonStrategy.h"
#include "../mainBoard/mainBoardCommonTof.h"
#include "../mainBoard/mainBoardCommonTof32.h"

#include "../../drivers/ioExpander/ioExpander.h"

#include "../../drivers/pwm/servo/pca9685.h"
#include "../../drivers/accelerometer/adxl345.h"
#include "../../drivers/accelerometer/adxl345Debug.h"

#include "../../robot/strategy/teamColor.h"
#include "../../robot/2020/mainBoard2020.h"

// SMALL ROBOT PART

// LED
#include "../../device/led/ledDevice.h"
#include "../../device/led/ledDeviceInterface.h"

// -> LED
#include "../../drivers/led/pca9685/ledPca9685.h"
// -> SERVO
#include "../../drivers/pwm/servo/servoPwmPca9685.h"

// -> ARM
#include "../../robot/2020/arm/buttonBoardArm2020.h"
#include "../../robot/2020/arm/armDeviceInterface2020.h"
#include "../../robot/2020/arm/armDevice2020.h"


#include "../../robot/2020/strategy/strategyConfig2020.h"
#include "../ioExpander/ioExpanderPcf8574.h"

// Robot Configuration
static RobotConfig robotConfig;

// LED
static LedArray ledArray;
// static I2cBusConnection* ledArrayBusConnection;

/**
 * @private
 */
void initMainBoardDevicesDescriptor() {
    mainBoardCommonInitDeviceListArray();

    mainBoardCommonAddDevices(&robotConfig);
    mainBoardCommonLcdAddDevices();
    mainBoardCommonMotorAddDevices(MAIN_BOARD_SERIAL_PORT_MOTOR);
    mainBoardCommonMotionAddDevices(MAIN_BOARD_SERIAL_PORT_MOTOR);
    mainBoardCommonStrategyAddDevices(MAIN_BOARD_SERIAL_PORT_MOTOR);
    mainBoardCommonMatchAddDevices();
    mainBoardCommonTofAddDevices32();
    mainBoardCommonMeca1AddDevices();
	mainBoardCommonIOExpanderListAddDevices32();

    addLocalDevice(getLedDeviceInterface(), getLedDeviceDescriptor(&ledArray));

    // Call the init on each devices
    initDevices();
}

void initMainBoardDriverDataDispatcherList(void) {
    mainBoardCommonInitDriverDataDispatcherList();

    mainBoardCommonMotorAddDispatcher();
}

bool mainBoardWaitForInstruction(StartMatch* startMatchParam) {
    // loop for all notification
    // notification handler must avoid to handle directly information in notification callback
    // and never to the call back device
    mainBoardCommonHandleStreamInstruction();
    // mainBoardCommonHandleAccelerometer();
    mainBoardCommonMotorHandleStreamInstruction();
    mainBoardCommonStrategyHandleStreamInstruction();
	
	ServoList* servoList = mainBoardCommonGetServoList();
    servoListMainUpdateCall(servoList);
    
    IOExpanderList* ioExpanderList = mainBoardCommonGetIOExpanderList();
    IOExpander* ioExpander = getIOExpanderByIndex(ioExpanderList, MAIN_BOARD_IO_EXPANDER_IOBOARD_INDEX);
    ioExpander->ioExpanderReadValue(ioExpander);

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

    mainBoardCommonAddPca9685Servos();

    /*
    appendString(getDebugOutputStreamLogger(), "LED ...");
    ledArrayBusConnection = addI2cBusConnection(i2cBus, PCA9685_ADDRESS_7, true);
    initLedArrayPca9685(&ledArray, ledArrayBusConnection);
    appendStringLN(getDebugOutputStreamLogger(), "OK");
    // -> SHOW COLOR OF THE TEAM
    enum TeamColor teamColor = getTeamColorFromRobotConfig(&robotConfig);
    Color color = getColorForTeam(teamColor);
    setLedColor(&ledArray, MAIN_BOARD_LED_COLOR_TEAM_INDEX, color);
    */
    IOExpanderList* ioExpanderList = mainBoardCommonIOExpanderListInitDrivers32(&robotConfig);
    IOExpander* ioExpanderStrategy = getIOExpanderByIndex(ioExpanderList, MAIN_BOARD_IO_EXPANDER_STRATEGY_INDEX);
    unsigned char strategyId = ioExpanderStrategy->ioExpanderReadValue(ioExpanderStrategy) & 0x0F;
    mainBoardCommonStrategyMainInitDrivers(&robotConfig, strategyId);
    
    // Attach a callback to the button Board
    IOExpander* ioExpanderButtonBoard = getIOExpanderByIndex(ioExpanderList, MAIN_BOARD_IO_EXPANDER_IOBOARD_INDEX);
    ioExpanderSetOnValueChangeEvent(ioExpanderButtonBoard, &arm2020IoExpanderOnValueChangeEvent, (int*) mainBoardCommonGetServoList());

    // Initialise the Strategy first so that we could show the color & stragegy
    // index at a very early stage
    IOExpander* ioExpanderBeepExpander = getIOExpanderByIndex(ioExpanderList, MAIN_BOARD_IO_EXPANDER_BEEP_INDEX);
    mainBoardCommonTofInitDrivers32(&robotConfig, ioExpanderBeepExpander);
    mainBoardCommonMatchMainInitDrivers(&robotConfig,
                                        &startupCheckList2020,
                                        isMatchStarted32,
                                        mainBoardWaitForInstruction,
                                        loopUnWaitForInstruction,
                                        endMatchBeforeEnd2020);
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

    // TofSensorList* tofSensorList = mainBoardCommonTofGetTofSensorList();
    ServoList* servoList = mainBoardCommonGetServoList();
    addLocalDevice(getArm2020DeviceInterface(), getArm2020DeviceDescriptor(servoList));

    mainBoardCommonStrategyMainLoop();

    while (true) {
        // Avoid reboot even at end
    }
}
