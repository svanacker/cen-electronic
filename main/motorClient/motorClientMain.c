#include <p30fxxxx.h>
#include <libpic30.h>
#include <math.h>
#include <delay.h>
#include <i2c.h>


_FOSC(CSW_FSCM_OFF & XT_PLL16);  //7Mhz3728 * 16  = 117,9648 MHz /4 = 29,4912 MIPS maxi pour ce pic
_FWDT(WDT_OFF);					
//Watchdog OFF
//_FBORPOR(PBOR_OFF & BORV_27 & PWRT_16 & MCLR_EN);
_FGS(CODE_PROT_OFF);			//Codeprotect OFF

// Robot
#include "motorClientMain.h"
#include "motorClient.h"

// Utils
#include "../../common/commons.h"
#include "../../common/io/cenIO.h"
#include "../../common/math/cenMath.h"
#include "../../common/delay/delay30F.h"
#include "../../common/pwm/pwmPic.h"
#include "../../common/serial/serial.h"
#include "../../common/serial/serialUtils.h"
#include "../../common/i2c/i2cSetup.h"

// Drivers
#include "../../device/device.h"
#include "../../device/drivers/battery.h"
#include "../../device/drivers/lcd.h"
#include "../../device/drivers/motor.h"
#include "../../device/drivers/pcf8574.h"
#include "../../device/drivers/rly08.h"
#include "../../device/drivers/sd21.h"
#include "../../device/drivers/srf02.h"


// Match / Strategy
#include "../../robot/match/startMatchDetector.h"
#include "../../robot/match/endMatchDetector.h"
#include "../../robot/robotDetector.h"
#include "../../robot/robot.h"
#include "../../robot/robotConfig.h"
#include "../../robot/match/strategy.h"

// Motors
#include "../../motion/pid/pid.h"
#include "../../motion/position/coders.h"
#include "../../motion/position/trajectory.h"
#include "../../motion/simple/motion.h"

// Specific to 2010
#include "../../robot/2010/pliers2010.h"
#include "../../robot/2010/tomatoe2010.h"
#include "../../robot/2010/strategy2010.h"

#define DEVICE_COUNT 13

static DeviceDescriptor devices[DEVICE_COUNT];

void initDevices(unsigned char debug) {

	devices[0] = getMotorDeviceDescriptor();
	devices[1] = getSD21DeviceDescriptor();
	devices[2] = getRLY08DeviceDescriptor();
	devices[3] = getSRF02DeviceDescriptor();
	devices[4] = getCodersDeviceDescriptor();
	devices[5] = getBatteryDeviceDescriptor();

	devices[6] = getStartMatchDetectorDeviceDescriptor();
	devices[7] = getEndMatchDetectorDeviceDescriptor();
	devices[8] = getRobotDetectorDeviceDescriptor();
	devices[9] = getPIDDeviceDescriptor();
	devices[10] = getTrajectoryDeviceDescriptor();
	devices[11] = getPliers2010DeviceDescriptor();
	devices[12] = getTomatoe2010DeviceDescriptor();

	int i;
	for (i=0; i < DEVICE_COUNT; i++) {
		DeviceDescriptor deviceDescriptor = devices[i];
		initDevice(&deviceDescriptor, debug);
	}
}

void stopDevices() {
	int i;
	for (i=0; i < DEVICE_COUNT; i++) {
		DeviceDescriptor deviceDescriptor = devices[i];
		stopDevice(&deviceDescriptor);
	}
}

void init(void) {
	int startDebug = TRUE;
	// int startDebug = TRUE;

	// Elapse time to be ensure that PIC is ok
	delaymSec(100);

	initDelay30F();
	initIO();

	// Serial
	openSerial(DEFAULT_SERIAL_SPEED);
	delaymSec(100);
	if (startDebug) {
		putString("Serial Interface started\n");
	}	

	// I2C
	initializeI2C();
	if (startDebug) {
		putString("I2C Interface started\n");
	}
	delaymSec(100);

	// Configuration of the robot
	DeviceDescriptor robotConfigDeviceDescriptor = getRobotConfigDeviceDescriptor();
	initDevice(&robotConfigDeviceDescriptor, startDebug);
	unsigned char debug = isConfigDebug();
	
	initDevices(debug);

	// Start interruption
	startDelay30F();

	// SRF02 Test
	/*
	unsigned int distance = 0;
	while (TRUE) {
		distance = getSRF02Distance();
		delaymSec(100);
		if (distance < 100) {
			sendDec(distance);
			println();
		}
	}
	*/
}

void smallTest( void ) {
	// Motor test
	forwardSimpleMMAndWait(100);
	backwardSimpleMMAndWait(100);

	// tomatoe
	setTomatoeEnabled(1);

	// Plier test
	preparePlier(0);
	delaymSec(1000);
	preparePlier(1);
	delaymSec(1000);
	pliersInTheRobot();

	// Laser begin
	setRobotDetectorEnabled(1);

	// Sensors
	downSensor(0);
	delaymSec(1000);
	downSensor(1);
	delaymSec(1000);
	upSensor(0);
	delaymSec(1000);
	upSensor(1);

	delaymSec(1000);

	setTomatoeEnabled(0);

	// laser End
	setRobotDetectorEnabled(0);
}

int main(void) {
	init();
	clearScreen();

	// maintain the position of the robot to avoid problems
	maintainPosition();

	unsigned char configValue = getConfigValue();
	unsigned char strategyIndex = configValue & CONFIG_STRATEGY_MASK;
	unsigned char rollingTest = configValue & CONFIG_ROLLING_TEST_MASK;
	unsigned char useLaser = configValue & CONFIG_USE_LASER_MASK;
	unsigned char debug = configValue & CONFIG_DEBUG_MASK;
	unsigned char blue = configValue & CONFIG_COLOR_BLUE_MASK;

	// Send to the PC that robot is ready
	notifyReady();

	loadMatchSide();

	if (strategyIndex) {
		writeString("Strategy = ");
		writeIntCR(strategyIndex);
	}
	if (rollingTest) {
		writeStringCR("!! ROLLING TEST !!");
	}

	if (debug) {
		smallTest();
	}

	setBacklight(0);

	// TODO : TEMP
	/*
	if (useLaser) {
		setRobotDetectorEnabled(1);
	}
	*/
	if (blue) {
		setMaxLeftAndRight(1000, 1650);
	}
	else {
		setMaxLeftAndRight(1650, 1000);
	}

	// Wait before start and handle robot
	loopUntilStart();

	setTomatoeEnabled(1);

	// After start, we can take more place
	pliersAfterStart() ;

	// Detects the start of the match to be able to end the robot.
	startMatch();

	if (useLaser) {
		setRobotDetectorEnabled(1);
	}

	if (strategyIndex) {
		strategy2010(strategyIndex);
	}
	else {
		while (TRUE) {
			handleInstructionAndMotion();
	
			if (isRobotMustStop()) {
				break;
			}
	
			if (isEnd()) {
				showEnd();
				break;
			}
		}
	}
	
	stopRobot();

	return 0;
}

	





