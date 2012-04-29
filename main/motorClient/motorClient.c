#include "motorClient.h"

// Utils fonction
#include "../../common/commons.h"
#include "../../common/adc/adcutils.h"
#include "../../common/delay/delay30F.h"
#include "../../common/eeprom/eeprom.h"
#include "../../common/math/cenMath.h"
#include "../../common/pwm/pwmPic.h"
#include "../../common/serial/serial.h"
#include "../../common/serial/serialUtils.h"

// Drivers
#include "../../device/drivers/battery.h"
#include "../../device/drivers/motor.h"
#include "../../device/drivers/rly08.h"
#include "../../device/drivers/sd21.h"
#include "../../device/drivers/srf02.h"
#include "../../device/drivers/pcf8574.h"
#include "../../device/drivers/lcd.h"

// Motion
#include "../../motion/simple/motion.h"
#include "../../motion/pid/pid.h"
#include "../../motion/position/coders.h"
#include "../../motion/position/trajectory.h"

// Robot
#include "../../robot/robot.h"
#include "../../robot/robotConfig.h"
#include "../../robot/robotDetector.h"

// Specific 2010
#include "../../robot/2010/pliers2010.h"
#include "../../robot/2010/tomatoe2010.h"
#include "../../robot/2010/strategy2010.h"

// match
#include "../../robot/match/endMatchDetector.h"

static int debug;

int getDebug( void ) {
	return debug;
}

void sendPosition( void ) {
	// Send the two position
	signed long value = getCoderValue(CODER_LEFT);
	//sendHex8(value);
	sendHex4(value);
	putc('-');
	value = getCoderValue(CODER_RIGHT);
	sendHex4(value);
}

void notifyBlocked( void ) {
	// f for "failed"
	putc('f');
	sendPosition();
}

void notifyReached( void ) {
	// o for "ok"
	putc('o');
	sendPosition();
}

void notifyMatchStarted( void ) {
	putc('s');
}

void notifyReady( void ) {
	putString(ROBOT_STARTED_NOTIFICATION);
}

void notifyEnd ( void ) {
	putc('e');
}

void notifyObstacle () {
	unsigned int currentTimeInSecond = getCurrentTimeInSecond();
	if (currentTimeInSecond > getLastNotifyObstacleTime() + OBSTACLE_DELAY_BEFORE_NEXT_NOTIFICATION) {
		setLastNotifyObstacleTime(currentTimeInSecond);
		putc('h');
		unsigned int direction = (getLastLaserServoPosition() - 1500) / 12;
		unsigned int distance = OBSTACLE_DISTANCE_CM;
		sendPosition();
		putc('-');
		sendHex4(distance);
		putc('-');
		sendHex4(direction);
		clearObstacle();
	}
}

void notifyCornBlack() {
	putc('m');
}

void notifyCornSequenceEnd() {
	putc('k');
}

/**
* Load the next instruction found in the buffer
*/
void loadNextInstruction ( void ) {
	unsigned char b;
	signed long long1, long2;
	unsigned char char1, char2;
	signed char leftMotorSpeed;
	signed char rightMotorSpeed;
	unsigned int int1;

    // if buffer has data
    if (getBufferLength() > 0) {
		// the first character determines the instruction type
		b = getBufferValue(0);

		// "b" : Battery
		if (b == 'b') {
			printAck();
	        // clear this instruction
    	    deleteBuffer(0, 1);
			// Send the two position
			int1 = getBatteryVoltage(0);
			putc('b');
			sendHex4(int1);
		}

		// GET Debug : letter "c" (for config)
		else if (b == 'c') {
			// send acknowledgement
			printAck();
	        // clear this instruction
    	    deleteBuffer(0, 1);

			refreshConfig();

			// char1 = isConfigPresent();
			char2 = getConfigValue();
			if (debug) {
				println();
				putString("config=");
				putString(getStringConfig());
				println();
			}
			
			putc('c');
			sendHex2(char2);
		}
		// GET Debug : letter "d" (for debug) => 100
		else if (b == 'd') {
			// send acknowledgement
			printAck();
	        // clear this instruction
    	    deleteBuffer(0, 1);
			if (debug == 0) {
				debug = TRUE;
			}
			else {
				debug = FALSE;
			}
			sendHex2(debug);
		}

		// GET Error : letter "e" (for error) => 101
		else if (b == 'e') {
			// send acknowledgement
			printAck();

			printErrorStruct(0);
			printErrorStruct(1);

			printMotionStruct(0);
			printMotionStruct(1);

	        // clear this instruction
    	    deleteBuffer(0, 1);
		}
		// letter "g" (for goto)
		else if (b == 'g') {
			// wait that the instruction is completely loaded
			if (getBufferLength() >= 13) {
				// send acquittement
				printAck();

				// Ex: 0100 0100 01 10
				// Left position
				long1 = hex4CharToLong(getBufferValue(1), getBufferValue(2), getBufferValue(3), getBufferValue(4));
				// Right position
				long2 = hex4CharToLong(getBufferValue(5), getBufferValue(6), getBufferValue(7), getBufferValue(8));
				// Acceleration
				char1 = hex2CharToInt(getBufferValue(9), getBufferValue(10));
				// Speed
				char2 = hex2CharToInt(getBufferValue(11), getBufferValue(12));

				gotoPosition(long1, long2, char1, char2);
	
				deleteBuffer(0, 13);
			}
		}
		// f "for forward" in millimeter
		else if (b == 'f') {
			// wait that the instruction is completely loaded
			if (getBufferLength() >= 5) {
				printAck();
				// Left & Right position
				long1 = hex4CharToLong(getBufferValue(1), getBufferValue(2), getBufferValue(3), getBufferValue(4));

				forwardSimpleMM(long1);

				deleteBuffer(0, 5);
			}
		}
		// h for "homologation"
		else if (b == 'h') {
			deleteBuffer(0, 1);

			printAck();

			strategy2010(STRATEGY_HOMOLOGATION);
		}
		// H: coders errors
		else if (b == 'H') {
			deleteBuffer(0, 1);
			int i;
			for (i=0; i<MAX_CODERS; i++) {
				int e=getCodersErrorCount(i);
				println();
				printValue("e", i);
				putc('=');
				sendDec(e);
				putString(" (");
				printValue("i=", getCodersInitialPosition(i));
				printValue(",z=", getCodersZCount(i));
				printValue(",v=", getCodersErrorValue(i));
				putc(')');
			}
			println();
		}
		// GET Instruction : letter "i" (for instruction) => 105
		else if (b == 'i') {
			// send acknowledgement
			printAck();
	        // clear this instruction
    	    deleteBuffer(0, 1);
			printInst(0);
			printInst(1);
		}
		else if (b == 'I') {
			// send acknowledgement
			printAck();
	        // clear this instruction
    	    deleteBuffer(0, 1);
			printDistances();
		}
		// Sequence de ramassage
		else if (b == 'J') {
			// wait that the instruction is completely loaded
			if (getBufferLength() >= 3) {
				printAck();
				// Plier Index
				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));

				deleteBuffer(0, 3);
				
				unsigned cornBlack = takeCornIfNotBlack(char1);
				if (cornBlack == CORN_BLACK_NOT_TAKEN) {
					notifyCornBlack();
				}
				notifyCornSequenceEnd();
			}
		}
		// l "for left" in degree
		else if (b == 'l') {
			// wait that the instruction is completely loaded
			if (getBufferLength() >= 5) {
				printAck();
				// Left & Right position
				long1 = hex4CharToLong(getBufferValue(1), getBufferValue(2), getBufferValue(3), getBufferValue(4));

				leftSimpleDegree(long1);

				deleteBuffer(0, 5);
			}
		}
		// L : writes on LCD
		else if (b == 'L') {
        	if (getBufferLength() >= 3) {
                unsigned int lcdTextLength = hex2CharToInt(getBufferValue(1), getBufferValue(2));
                // Wait for the complete String
                if (getBufferLength() >= 3 + lcdTextLength * 2) {
					printAck();
                    // print character
					int i;
                    for (i= 0; i < lcdTextLength; i++) {
                    	int c = hex2CharToInt(getBufferValue(3 + i * 2), getBufferValue(4 + i * 2));
                     	writeChar(c);
                   }

                   // Delete the instruction
                   deleteBuffer(0, 3 + lcdTextLength * 2);
                }
			}
		}
		// laser servo position
		else if (b == 'N') {
			// send acknowledgement
			printAck();
	        // clear this instruction
    	    deleteBuffer(0, 1);
			printValue("laser=", getLastLaserServoPosition());
		}
		// Change speed of laser: letter "M" (for laser) => 108
		else if (b == 'M') {
			// wait that the instruction is completely loaded
			if (getBufferLength() >= 3) {
				// send acknowledgement
				printAck();

				// Acceleration
				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));
	
				setRobotDetectorSpeed(char1);
		        // clear this instruction
    	    	deleteBuffer(0, 3);
			}
		}
		// letter "m" (for motor)
		else if (b == 'm') {
			if (getBufferLength() >= 5) {
				// send acknowledgement
				printAck();

				// as we can not control call command directly, we adjust 
				// the variable which will be 	
				leftMotorSpeed = hex2CharToInt(getBufferValue(1), getBufferValue(2));
				rightMotorSpeed = hex2CharToInt(getBufferValue(3), getBufferValue(4));

				setMotorSpeeds(leftMotorSpeed, rightMotorSpeed);

		        // clear this instruction
	    	    deleteBuffer(0, 5);
			}

			// TODO : Small back motors			
		}
		// letter "n" (for digital-analogic)
		else if (b == 'n') {
			if (getBufferLength() >= 3) {
				// send acknowledgement
				printAck();
				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));

				// char1 corresponds to the channel
				int1 = getANX(char1);			

				sendUnsignedHex4(int1);

		        // clear this instruction
	    	    deleteBuffer(0, 3);
			}
		}
		else if (b == 'o') {
			if (getBufferLength() >= 9) {
				printAck();
				// Angle
				long1 = hex4CharToLong(getBufferValue(1), getBufferValue(2), getBufferValue(3), getBufferValue(4));
				// Acceleration
				char1 = hex2CharToInt(getBufferValue(5), getBufferValue(6));
				// Speed
				char2 = hex2CharToInt(getBufferValue(7), getBufferValue(8));
				leftDegree(long1, char1, char2);
				deleteBuffer(0, 9);
			}	
		}
		// "O" : pidTime
		else if (b == 'O') {
			// Send the two position
			long value=getPidTime();
			sendHex8(value);
    	    deleteBuffer(0, 1);
		}
		// letter "P" (for preparation for Plier)
		else if (b == 'P') {
			if (getBufferLength() >= 3) {
				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));
				printAck();
				preparePlier(char1);
	    	    deleteBuffer(0, 3);
			}
		}
		// letter "p" (for PID)
		else if (b == 'p') {
			if (getBufferLength() >= 11) {
				// send acquittement
				printAck();
				// PID Index
				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));
			
				setPID(char1, hex2CharToInt(getBufferValue(3), getBufferValue(4)), 
							  hex2CharToInt(getBufferValue(5), getBufferValue(6)),
							  hex2CharToInt(getBufferValue(7), getBufferValue(8)),
							  hex2CharToInt(getBufferValue(9), getBufferValue(10)));

				savePID();
		        
				// clear this instruction
	    	    deleteBuffer(0, 11);
			}
		}
		// letter "q" (for PID)
		else if (b == 'q') {
			// send acknowledgement
			printAck();
			putc('q');
			println();
		
        	// Send every value of every PID
			int pidIndex;
			for (pidIndex = 0; pidIndex < PID_COUNT; pidIndex++) {
				// we test all pid value (test mode included)
				Pid * localPid = getPID(pidIndex, 0);
				sendHex2(localPid->p);
				sendHex2(localPid->i);
				sendHex2(localPid->d);
				sendHex2(localPid->maxIntegral);
				println();
			}
	        // clear this instruction
    	    deleteBuffer(0, 1);
		}
		else if (b == 'Q') {
			if (getBufferLength() >= 3) {
				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));
				printAck();
				upSensor(char1);
	    	    deleteBuffer(0, 3);
			}
		}
		// r "for right" in degree
		else if (b == 'r') { 
			// wait that the instruction is completely loaded
			if (getBufferLength() >= 5) {
				printAck();
				// Left & Right position
				long1 = hex4CharToLong(getBufferValue(1), getBufferValue(2), getBufferValue(3), getBufferValue(4));

				deleteBuffer(0, 5);

				rightSimpleDegree(long1);
			}
		}
		// letter "R" (for Relay)
		else if (b == 'R') {
			if (getBufferLength() >= 5) {	
				// send acknowledgement
				printAck();

				// Relay Index
				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));
				// On / Off
				char2 = hex2CharToInt(getBufferValue(3), getBufferValue(4));
	
				if (debug) {
					println();
					putString("index=");
					sendDec(char1);
					putString(",value=");
					sendDec(char2);
				}				
				setRelayState(char1, char2);
	
		        // clear this instruction
	    	    deleteBuffer(0, 5);
			}
		}
		// letter "S" (for servo)
		else if (b == 'S') {
			if (getBufferLength() >= 9) {	
				// send acknowledgement
				printAck();

				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));
				char2 = hex2CharToInt(getBufferValue(3), getBufferValue(4));
				long1 = hex4CharToLong(getBufferValue(5), getBufferValue(6), getBufferValue(7), getBufferValue(8));
	
				if (debug) {
					println();
					putString("servo=");
					sendDec(char1);
					putString(",speed=");
					sendDec(char2);
					putString(",position=");
					sendDec(long1);
				}				
	
				//commandSD21(char servo, char speed, int position) 
				commandSD21(char1, char2, (int) long1);
	
		        // clear this instruction
	    	    deleteBuffer(0, 9);
			}
		}
		// letter "s" (for small) => 
		else if (b == 's') {
			// send acknowledgement
			printAck();

			setMotorSpeeds(-15, -15);

	        // clear this instruction
    	    deleteBuffer(0, 1);
		}
		// T : Sonar
		else if (b == 'T') {
			// send acknowledgement
			printAck();
			
			int1 = getSRF02Distance();
			sendUnsignedHex4(int1);

	        // clear this instruction
    	    deleteBuffer(0, 1);
		}

		// letter "t" (for time) => 116
		else if (b == 't') {
			// send acknowledgement
			printAck();

			// Send the time
			sendUnsignedHex4(getTime(CODER_TIMER_INDEX));

	        // clear this instruction
    	    deleteBuffer(0, 1);
		}
		// letter "U" : (Take Corn)
		else if (b == 'U') {
			if (getBufferLength() >= 3) {	
				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));
	
				// send acknowledgement
				printAck();

				if (debug) {
					println();
					putString("takeCorn:index=");
					sendDec(char1);
				}
				
				takeAndLoadCorn(char1);
	
		        // clear this instruction
	    	    deleteBuffer(0, 3);
			}
		}
		// Activate tomatoe
		else if (b == 'V') {
			// send acknowledgement
			printAck();

			setTomatoeEnabled(1);

	        // clear this instruction
    	    deleteBuffer(0, 1);
		}
		// Disactivate tomatoe
		else if (b == 'v') {
			// send acknowledgement
			printAck();

			setTomatoeEnabled(0);

	        // clear this instruction
    	    deleteBuffer(0, 1);
		}
		// w ("wheel") => 119
		else if (b == 'w') {
			// send acknowledgement
			printAck();

			// Send PID
			// putc(TO_JAVELIN_MASTER_POSITION);
			putc('w');

			sendPosition();

	        // clear this instruction
    	    deleteBuffer(0, 1);
		}
		// W ("PWM")
		else if (b == 'W') {
			if (getBufferLength() >= 7) {
				// send acknowledgement
				printAck();

				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));
				long1 = hex4CharToLong(getBufferValue(3), getBufferValue(4), getBufferValue(5), getBufferValue(6));
	
				if (debug) {
					println();
					putString("pwm=");
					sendDec(char1);
					putString(",position=");
					sendDec(long1);
				}				
				if (char1 == 1) {
					pwmServo1((int) long1);
				}
				else if (char1 == 2) {
					pwmServo2((int) long1);
				}
	
		        // clear this instruction
	    	    deleteBuffer(0, 7);
			}
		}
		// y : To see the type of trajectory
		else if (b == 'y') {
			int i;
			for (i=0; i<1; i++) {
				println();
				printValue("i=", i);
				MotionInstruction * localInst = getInst(i);
				switch (localInst->profileType) {
					case PROFILE_TYPE_TRIANGLE:
						putString(": triangle");
						break;
					case PROFILE_TYPE_TRAPEZE:
						putString(": trapeze");
						break;
				}
			}
			println();
			deleteBuffer(0, 1);
		}
		else if (b == 'Y') {
			if (getBufferLength() >= 3) {
				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));
				printAck();
				downSensor(char1);
	    	    deleteBuffer(0, 3);
			}
		}
	   // x : read pcf8574
		else if (b == 'x') {
			if (getBufferLength() >= 3) {
				printAck();
				// Sub address of PCF8574
				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));
				
				char2 = readPCF8574(PCF8574_BASE_ADDRESS, char1, 0b11111111);
				sendHex2(char2);
	
		        // clear this instruction
	    	    deleteBuffer(0, 3);
			}
		}
	    // Activated or disactivate PID
		else if (b == 'X') {
			if (getBufferLength() >= 5) {
				printAck();
				// Index of PID
				char1 = hex2CharToInt(getBufferValue(1), getBufferValue(2));
				// Value (Active or inactive)
				char2 = hex2CharToInt(getBufferValue(1), getBufferValue(2));
				
				setEnabledPid(char1, char2);
	
		        // clear this instruction
	    	    deleteBuffer(0, 5);
			}
		}
        // v : SRF02
		else if (b == 'V') {
			// send acknowledgement
			printAck();
			
			char1 = getSRF02SoftwareRevision(1);
			sendHex2(char1);

	        // clear this instruction
    	    deleteBuffer(0, 1);
		}
		// z as "clear" (instruction and position)
		else if (b == 'z') {
			// send acknowledgement
			printAck();
			putc('z');
			sendPosition();

			stopPosition();
	        // clear the buffer and all possibles instructions
    	    clearBuffer();
		}
		else {
			clearBuffer();
		}
	}
}





