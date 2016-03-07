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
    appendHex2(outputStream, mpuData->gyro_X);

    append(outputStream, '/');
    appendHex2(outputStream, mpuData->gyro_Y);
    append(outputStream, '/');
    appendHex2(outputStream, mpuData->gyro_Z);
}

void initMpu(Mpu* mpu, WriteMpuFunction* writeMpu, ReadMpuFunction* readMpu, int* object) {
    mpu->writeMpu = writeMpu;
    mpu->readMpu = readMpu;
    mpu->object = object;
}

bool isMpuInitialized(Mpu* mpu) {
    if (mpu->writeMpu == NULL ) {
        return false;
    }
    return true;
}
