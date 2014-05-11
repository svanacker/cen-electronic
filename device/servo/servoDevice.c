#include "servoDevice.h"
#include "servoDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/pwm/pwmPic.h"
#include "../../common/pwm/servoPwm.h"

#include "../../device/device.h"

#define MAX_SERVO_SPEED 		20000

void deviceServoInit() {
    initPwmForServo(PWM_SERVO_MIDDLE_POSITION);
}

void deviceServoShutDown() {
}

bool deviceServoIsOk() {
    return true;
}

void deviceServoHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (header == INDEX_COMMAND_SERVO) {
        int servoIndex = readHex2(inputStream);
        int servoSpeed = readHex2(inputStream);

		// 0xFF is for test to determine the index of each 
		// servo (test)
		if (servoIndex == 0xFF) {
			testAllPwmServos();
		}
		else {
	        //if (servoSpeed == 0xFF) {
	        servoSpeed = MAX_SERVO_SPEED;
	        //}
	
	        int servoValue = readHex4(inputStream);
	        if (servoIndex > 0 && servoIndex <= PWM_COUNT) {
	            pwmServo(servoIndex, servoSpeed, servoValue);
	        } else {
	            pwmServoAll(servoSpeed, servoValue);
	        }
		}
		ackCommand(outputStream, SERVO_DEVICE_HEADER, INDEX_COMMAND_SERVO);
    }
	else if (header == COMPACT_COMMAND_SERVO) {
		int servoValue = readHex4(inputStream);
		pwmServoAll(MAX_SERVO_SPEED, servoValue);
		ackCommand(outputStream, SERVO_DEVICE_HEADER, COMPACT_COMMAND_SERVO);
	}
}


static DeviceDescriptor descriptor = {
    .deviceInit = &deviceServoInit,
    .deviceShutDown = &deviceServoShutDown,
    .deviceIsOk = &deviceServoIsOk,
    .deviceHandleRawData = &deviceServoHandleRawData,
};

DeviceDescriptor* getServoDeviceDescriptor() {
    return &descriptor;
}
