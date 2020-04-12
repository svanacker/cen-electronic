#include "clientMotor.h"

#include "../../common/2d/2d.h"
#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

#include "../../common/motor/dualHBridgePin.h"
#include "../../device/motor/pwmMotorDeviceInterface.h"

bool clientMotorWrite(signed int motorValue1, signed int motorValue2) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, MOTOR_DEVICE_HEADER);
    append(outputStream, COMMAND_MOVE_MOTOR);
    appendSignedHex2(outputStream, motorValue1);
    appendSignedHex2(outputStream, motorValue2);
    
    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool clientMotorStop(void) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, MOTOR_DEVICE_HEADER);
    append(outputStream, COMMAND_STOP_MOTOR);
    
    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// Pin Management
bool clientMotorSetPinUsage(enum DualHBridgePinUsageType pinUsageType1, 
                            enum DualHBridgePinUsageType pinUsageType2,
                            enum DualHBridgePinStopEventType pinStopEventType1,
                            enum DualHBridgePinStopEventType pinStopEventType2
        ) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, MOTOR_DEVICE_HEADER);
    append(outputStream, COMMAND_SET_PIN_USAGE_MOTOR);
    appendHex2(outputStream, pinUsageType1);
    appendSeparator(outputStream);
    appendHex2(outputStream, pinUsageType2);
    appendSeparator(outputStream);
    appendHex2(outputStream, pinStopEventType1);
    appendSeparator(outputStream);
    appendHex2(outputStream, pinStopEventType2);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

