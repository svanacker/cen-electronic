#include "MPU.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printMpu(OutputStream* outputStream, Mpu* mpu) {
    MpuData* mpuData = &(mpu->mpuData);
    appendHex2(outputStream, mpuData->accel_X);
    append(outputStream, ':');
    appendHex2(outputStream, mpuData->accel_Y);
    append(outputStream, ':');
    appendHex2(outputStream, mpuData->accel_Z);

    append(outputStream, ' ');
    appendHex2(outputStream, mpuData->accel_gyro_X);

    append(outputStream, '/');
    appendHex2(outputStream, mpuData->accel_gyro_Y);
    append(outputStream, '/');
    appendHex2(outputStream, mpuData->accel_gyro_Z);
}

void initMpu(Mpu* mpu, 
        InitMPUFunction* initMPU,
        GetAccelMPUFunction* getAccelMPU, 
        GetGyroMPUFunction* getGyroMPU,
        GetTempMPUFunction* getTempMPU, 
        GetAllDataMPUFunction* getAllDataMPU,
        GetRegisterMPUFunction* getRegisterMPU,
        int* object) {
    mpu->initMPU = initMPU;
    mpu->getAccelMPU = getAccelMPU;
    mpu->getGyroMPU = getGyroMPU;
    mpu->getTempMPU = getTempMPU;
    mpu->getAllDataMPU = getAllDataMPU;
    mpu->getRegisterMPU = getRegisterMPU;
    mpu->object = object;
}

bool isMpuInitialized(Mpu* mpu) {
    if (mpu->initMPU == NULL 
            | mpu->getAccelMPU == NULL 
            | mpu->getGyroMPU == NULL 
            | mpu->getTempMPU == NULL 
            | mpu->getAllDataMPU == NULL 
            | mpu->getRegisterMPU == NULL) {
        return false;
    }
    return true;
}
