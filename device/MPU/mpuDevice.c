#include <stdbool.h>
#include <stdlib.h>

#include "mpuDevice.h"
#include "mpuDeviceInterface.h"

#include "../../common/MPU/MPU.h"
#include "../../common/error/error.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

static Mpu* mpu;

void _deviceMpuCheckInitialized() {
    if (mpu == NULL) {
        writeError(MPU_NULL);
    }
    if (!isMpuInitialized(mpu)) {
        writeError(MPU_NOT_INITIALIZED);
    }
}

void deviceMpuInit(void) {
    _deviceMpuCheckInitialized();
    mpu->initMPU(mpu);
}

void deviceMpuShutDown(void) {
}

bool isMpuDeviceOk(void) {
    return true;
}

void deviceMpuHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    _deviceMpuCheckInitialized();
    if (header == GET_ACCELERATION_MPU) {     
        MpuData* mpuData = mpu->getAccelMPU(mpu);
        appendHex4(outputStream, mpuData->accel_X);
        append(outputStream,':');
        appendHex4(outputStream, mpuData->accel_Y);
        append(outputStream,':');
        appendHex4(outputStream, mpuData->accel_Z);
        ackCommand(outputStream, MPU_DEVICE_HEADER, GET_ACCELERATION_MPU);
        } else if (header == GET_GYROSCOPE_MPU) {
        MpuData* mpuData = mpu->getGyroMPU(mpu);
        appendHex4(outputStream, mpuData->accel_gyro_X);
        append(outputStream,':');
        appendHex4(outputStream, mpuData->accel_gyro_Y);
        append(outputStream,':');
        appendHex4(outputStream, mpuData->accel_gyro_Z);
        ackCommand(outputStream, MPU_DEVICE_HEADER, GET_GYROSCOPE_MPU);
    } else if (header == GET_TEMPERATURE_MPU) {
        MpuData* mpuData = mpu->getTempMPU(mpu);
        appendHex4(outputStream, mpuData->temperature);
        ackCommand(outputStream, MPU_DEVICE_HEADER, GET_TEMPERATURE_MPU);
    } else if (header == GET_ALL_DATA_MPU) {
        MpuData* mpuData = mpu->getAllDataMPU(mpu);
        appendHex4(outputStream, mpuData->accel_X);
        append(outputStream,':');
        appendHex4(outputStream, mpuData->accel_Y);
        append(outputStream,':');
        appendHex4(outputStream, mpuData->accel_Z);
        append(outputStream,'-');
        appendHex4(outputStream, mpuData->accel_gyro_X);
        append(outputStream,':');
        appendHex4(outputStream, mpuData->accel_gyro_Y);
        append(outputStream,':');
        appendHex4(outputStream, mpuData->accel_gyro_Z);
        append(outputStream,'-');
        appendHex4(outputStream, mpuData->temperature);
        ackCommand(outputStream, MPU_DEVICE_HEADER, GET_ALL_DATA_MPU);
    } else if (header == GET_REGISTER_MPU) {    
        unsigned long address = readHex2(inputStream);
        char value = mpu->getRegisterMPU(mpu, address);
        appendHex2(outputStream, value);
        ackCommand(outputStream, MPU_DEVICE_HEADER, GET_REGISTER_MPU);
    }     
}


      
        


static DeviceDescriptor descriptor = {
    .deviceInit = &deviceMpuInit,
    .deviceShutDown = &deviceMpuShutDown,
    .deviceIsOk = &isMpuDeviceOk,
    .deviceHandleRawData = &deviceMpuHandleRawData,
};

DeviceDescriptor* getMpuDeviceDescriptor(Mpu* mpuParam) {
    mpu = mpuParam;
    return &descriptor;
}