#include <p30fxxxx.h>
#include <UART.h>
#include <libpic30.h>
#include <math.h>

#include "../device/drivers/beacon/laserBeacon.h"

#include "../common/commons.h"
#include "../common/math/cenMath.h"
#include "../common/delay/delay30F.h"
#include "../common/pwm/pwmPic.h"
#include "../common/serial/serial.h"
#include "../common/serial/serialUtils.h"

#include "../device/drivers/zigbee.h"

#include "../robot/robotDetector.h"
#include "../common/2d/2d.h"

// Bounds of detection
#define SERVO_LASER_1_MAX_LEFT_POSITION_DEFAULT_VALUE 500
#define SERVO_LASER_1_MAX_RIGHT_POSITION_DEFAULT_VALUE 1500

#define SERVO_LASER_2_MAX_LEFT_POSITION_DEFAULT_VALUE 700
#define SERVO_LASER_2_MAX_RIGHT_POSITION_DEFAULT_VALUE 1700

#define DISTANCE_BETWEEN_BEACON 2200.0f
// #define DISTANCE_BETWEEN_BEACON 1250.0f

// Factors to determine line (between beacon and receiver) equation, with cartesian coordinates corresponding to the first laser beacon. */
#define BEACON_SERVO_1_ANGLE_DEGREE 90
#define BEACON_SERVO_1_INIT_COMPUTE_VALUE 1490
#define BEACON_SERVO_1_FACTOR 10.2

#define BEACON_SERVO_2_ANGLE_DEGREE 90
#define BEACON_SERVO_2_INIT_COMPUTE_VALUE 1670
#define BEACON_SERVO_2_FACTOR 10.2
 
/** Defines the interval to search, when we are in tracking mode. */
#define SHORT_TRACKING_INTERVAL 50

#define SERIAL_PORT_ZIGBEE SERIAL_PORT_2
#define SERIAL_PORT_DEBUG SERIAL_PORT_1

int getLaserPin1() {
	return PORTAbits.RA11;
}

int getLaserPin2() {
	//return PORTBbits.RB8;
	// Corresponds to L4
	return PORTCbits.RC13;
}

int receiverZigbeeTest(void) {
	/*
	char *macAdresse = "1";
	char *panId = "1620";
	char *channel = "100000";
	char *function = "0";
	char *adresse = "0";
	char *data;
	char receiveChar;
	char valide;
	int toto;
	*/
	
	TRISB = 0;
	TRISB = 0;

	// Configure serialBuffer
	Buffer zigbeeBuffer;
	initBuffer(&zigbeeBuffer, SERIAL_PORT_ZIGBEE);
	setAndOpenSerialBuffer(&zigbeeBuffer);

	Buffer debugBuffer;
	initBuffer(&debugBuffer, SERIAL_PORT_DEBUG);
	setAndOpenSerialBuffer(&debugBuffer);

	setSerialBuffer(&debugBuffer);
	putString("Beacon Receiver start rs232\n");

	initPwmForServo(1500);	

	// Initialization of laserDetector
	// Laser 1
	initLaserDetectorStruct(
			LASER_INDEX_1,
			LASER_SERVO_INDEX_1,
			&getLaserPin1,
			SERVO_LASER_1_MAX_LEFT_POSITION_DEFAULT_VALUE, 
			SERVO_LASER_1_MAX_RIGHT_POSITION_DEFAULT_VALUE,
			SHORT_TRACKING_INTERVAL,
			BEACON_SERVO_1_FACTOR,
			BEACON_SERVO_1_INIT_COMPUTE_VALUE,
			BEACON_SERVO_1_ANGLE_DEGREE
	);
	// Laser 2
	initLaserDetectorStruct(
			LASER_INDEX_2,
			LASER_SERVO_INDEX_2,
			&getLaserPin2,
			SERVO_LASER_2_MAX_LEFT_POSITION_DEFAULT_VALUE,
			SERVO_LASER_2_MAX_RIGHT_POSITION_DEFAULT_VALUE,
			SHORT_TRACKING_INTERVAL,
			BEACON_SERVO_2_FACTOR,
			BEACON_SERVO_2_INIT_COMPUTE_VALUE,
			BEACON_SERVO_2_ANGLE_DEGREE
	);

	while (1) {
		int laserIndex;
		for (laserIndex = 0; laserIndex < LASER_COUNT; laserIndex++) {
			detectsLaser(laserIndex);
		}
		delay100us(5);

		char c = handleChar(&debugBuffer, FALSE);
		if (c != 0) {
			putString("---------\n");
			Laser* laser1 = getLaser(LASER_INDEX_1);
			Laser* laser2 = getLaser(LASER_INDEX_2);
	
			printLaserStruct(&debugBuffer, laser1);
			println();
			printLaserStruct(&debugBuffer, laser2);
			clearBuffer(&debugBuffer);

			Point p = getPosition(DISTANCE_BETWEEN_BEACON);
			if (p.x != 0 && p.y != 0) {
				sendDec(p.x);
				putString(", ");
				sendDec(p.y);
				println();
			}	
		}
	}

	/*
	valide = 0;
	while (1) {
		if (U2STAbits.URXDA == 1){
				valide = getc();
				putc1 (valide);
		}
		if (U1STAbits.URXDA == 1){
				valide = getc1();
				putc (valide);
		}
	}
	*/
}

//	initZigbee(macAdresse,panId,channel,function,adresse);
//	while (1){
//		delaymSec(1000);
//		* data = getc1();
//		sendDataZigbee('5','5',data);

