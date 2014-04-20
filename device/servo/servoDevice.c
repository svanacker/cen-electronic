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
    if (header == COMMAND_SERVO) {
        int servoIndex = readHex2(inputStream);
        int servoSpeed = readHex2(inputStream);

		// 0xFF is for test to determine the index of each 
		// servo (test)
		if (servoIndex == 0xFF) {
			testAllPwmServos();
		}
		else {
	        //if (servoSpeed == 0xFF) {
	        servoSpeed = 20000;
	        //}
	
	        int servoValue = readHex4(inputStream);
	        if (servoIndex > 0 && servoIndex <= PWM_COUNT) {
	            pwmServo(servoIndex, servoSpeed, servoValue);
	        } else {
	            pwmServoAll(servoSpeed, servoValue);
	        }
		}
        appendAck(outputStream);
        append(outputStream, COMMAND_SERVO);
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
