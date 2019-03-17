#include <stdbool.h>

#include "accelerometerDevice.h"
#include "accelerometerDeviceInterface.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"

#include "../../common/sensor/accelerometer/accelerometer.h"

#include "../device.h"

// Forward declaration
Accelerometer* getAccelerometerDeviceAccelerometer(void);

// DEVICE INTERFACE

void initAccelerometerDevice( void ) {

}

void stopAccelerometerDevice( void ) {

}

bool isAccelerometerDeviceOk ( void ) {
    return true;
}

void deviceAccelerometerHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // SAMPLE COUNT
    if (commandHeader == COMMAND_ACCELEROMETER_GET_SAMPLE_COUNT) {
        ackCommand(outputStream, ACCELEROMETER_DEVICE_HEADER, COMMAND_ACCELEROMETER_GET_SAMPLE_COUNT);

        Accelerometer* accelerometer = getAccelerometerDeviceAccelerometer();
        unsigned int sampleCount = accelerometer->getSampleCount(accelerometer);
        appendHex4(outputStream, sampleCount);
    }
    // DATA
    else if (commandHeader == COMMAND_ACCELEROMETER_GET_SAMPLE_RAW_DATA) {
        ackCommand(outputStream, ACCELEROMETER_DEVICE_HEADER, COMMAND_ACCELEROMETER_GET_SAMPLE_RAW_DATA);

        Accelerometer* accelerometer = getAccelerometerDeviceAccelerometer();
        accelerometer->readLastSample(accelerometer);
        AccelerometerData* accelerometerData = accelerometer->accelerometerData;
        appendHex4(outputStream, accelerometerData->xRawValue);
        appendSeparator(outputStream);
        appendHex4(outputStream, accelerometerData->yRawValue);
        appendSeparator(outputStream);
        appendHex4(outputStream, accelerometerData->zRawValue);
    }
    else if (commandHeader == COMMAND_ACCELEROMETER_GET_SAMPLE_DATA_MILLIG_G) {
        ackCommand(outputStream, ACCELEROMETER_DEVICE_HEADER, COMMAND_ACCELEROMETER_GET_SAMPLE_DATA_MILLIG_G);

        Accelerometer* accelerometer = getAccelerometerDeviceAccelerometer();
        accelerometer->readLastSample(accelerometer);
        AccelerometerData* accelerometerData = accelerometer->accelerometerData;
        appendHex4(outputStream, accelerometerData->milligXValue);
        appendSeparator(outputStream);
        appendHex4(outputStream, accelerometerData->milligYValue);
        appendSeparator(outputStream);
        appendHex4(outputStream, accelerometerData->milligZValue);
    }
    // TRESHOLD
    else if (commandHeader == COMMAND_ACCELEROMETER_GET_THRESHOLD) {
        ackCommand(outputStream, ACCELEROMETER_DEVICE_HEADER, COMMAND_ACCELEROMETER_GET_THRESHOLD);

        Accelerometer* accelerometer = getAccelerometerDeviceAccelerometer();
        unsigned int threshold = accelerometer->getThresholdMillig(accelerometer);
        appendHex4(outputStream, threshold);
    }
    else if (commandHeader == COMMAND_ACCELEROMETER_SET_THRESHOLD) {
        ackCommand(outputStream, ACCELEROMETER_DEVICE_HEADER, COMMAND_ACCELEROMETER_SET_THRESHOLD);

        Accelerometer* accelerometer = getAccelerometerDeviceAccelerometer();
        unsigned int threshold = readHex4(inputStream);
        accelerometer->setThresholdMillig(accelerometer, threshold);
    }
    // DEBUG
    else if (commandHeader == COMMAND_ACCELEROMETER_DEBUG_CONFIG) {
        ackCommand(outputStream, ACCELEROMETER_DEVICE_HEADER, COMMAND_ACCELEROMETER_DEBUG_CONFIG);
        
        Accelerometer* accelerometer = getAccelerometerDeviceAccelerometer();
        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        accelerometer->debugConfig(debugOutputStream, accelerometer);
    }
    else if (commandHeader == COMMAND_ACCELEROMETER_DEBUG_VALUES) {
        ackCommand(outputStream, ACCELEROMETER_DEVICE_HEADER, COMMAND_ACCELEROMETER_DEBUG_VALUES);
        
        Accelerometer* accelerometer = getAccelerometerDeviceAccelerometer();
        accelerometer->readLastSample(accelerometer);
        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        accelerometer->debugValues(debugOutputStream, accelerometer);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initAccelerometerDevice,
    .deviceShutDown = &stopAccelerometerDevice,
    .deviceIsOk = &isAccelerometerDeviceOk,
    .deviceHandleRawData = &deviceAccelerometerHandleRawData,
};

DeviceDescriptor* getAccelerometerDeviceDescriptor(Accelerometer* accelerometer) {
    descriptor.object = (int*) accelerometer;
    return &descriptor;
}

Accelerometer* getAccelerometerDeviceAccelerometer(void) {
    return (Accelerometer*)(descriptor.object);
}
