#include "armDevice2012.h"

#include "armDeviceInterface2012.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/delay/delay30F.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/pwm/servoPwm.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../main/meca1/mechanicalBoard1.h"


void upArm(int armIndex) {
	int pwmSpeed = 20;
	if (armIndex == ARM_LEFT) {
		pwmServo(ARM_LEFT_PWM_INDEX, pwmSpeed, ARM_LEFT_UP);
	}
	else if (armIndex == ARM_RIGHT) {
		pwmServo(ARM_RIGHT_PWM_INDEX, pwmSpeed, ARM_RIGHT_UP);
	}
	else if (armIndex == 0) {
		pwmServo(ARM_LEFT_PWM_INDEX, pwmSpeed, ARM_LEFT_UP);
		pwmServo(ARM_RIGHT_PWM_INDEX, pwmSpeed, ARM_RIGHT_UP);
	}
}

void downArm(int armIndex) {
	int pwmSpeed = 20;
	if (armIndex == ARM_LEFT) {
		pwmServo(ARM_LEFT_PWM_INDEX, pwmSpeed, ARM_LEFT_DOWN);
	}
	else if (armIndex == ARM_RIGHT) {
		pwmServo(ARM_RIGHT_PWM_INDEX, pwmSpeed, ARM_RIGHT_DOWN);
	}
	else if (armIndex == 0) {
		pwmServo(ARM_LEFT_PWM_INDEX, pwmSpeed, ARM_LEFT_DOWN);
		pwmServo(ARM_RIGHT_PWM_INDEX, pwmSpeed, ARM_RIGHT_DOWN);
	}
}

void deviceArm2012Init() {
	upArm(ARM_LEFT);
	upArm(ARM_RIGHT);
}

void deviceArm2012ShutDown() {
    downArm(ARM_LEFT);
    downArm(ARM_RIGHT);
}

bool deviceArm2012IsOk() {
    return TRUE;
}

void deviceArm2012HandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (header == COMMAND_ARM_2012_UP) {
        int armIndex = readHex2(inputStream);
		upArm(armIndex);

        appendAck(outputStream);
        append(outputStream, COMMAND_ARM_2012_UP);

	
    } else if (header == COMMAND_ARM_2012_DOWN) {
        int armIndex = readHex2(inputStream);
		downArm(armIndex);

        appendAck(outputStream);
        append(outputStream, COMMAND_ARM_2012_DOWN);
    }
}


static DeviceDescriptor descriptor = {
    .deviceInit = &deviceArm2012Init,
    .deviceShutDown = &deviceArm2012ShutDown,
    .deviceIsOk = &deviceArm2012IsOk,
    .deviceHandleRawData = &deviceArm2012HandleRawData,
};

DeviceDescriptor* getArm2012DeviceDescriptor() {
    return &descriptor;
}
