#include <peripheral/legacy/i2c_legacy.h>

#include "MPU-6050.h"

#include "../../common/MPU/MPU.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

I2cBusConnection* _mpu6050GetI2cBusConnection(Mpu* mpu) {
    I2cBusConnection* result = (I2cBusConnection*) mpu->object;

    return result;
}

/**
 * @see MPU.h
 * @private
 * Read the acceleration from the MPU-6050 and store in the structure.
 * @param mpu the mpu
 */
MpuData* _readMpu6050AccMpu(Mpu* mpu) {
    
    //temporary storage
    int data_h;
    int data_l;
    
    // I2C Bus Prepare   
    I2cBusConnection* i2cBusConnection = _mpu6050GetI2cBusConnection(mpu);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    // init pointer
    MpuData* mpuData = &(mpu->mpuData);
       
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_RA_ACCEL_XOUT_H);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_READ_ADDRESS);
    WaitI2C(i2cBus);
    
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->accel_X = ((data_h<<8)|data_l);
    
    
    WaitI2C(i2cBus);
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->accel_Y = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);
    
    WaitI2C(i2cBus);
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    
    mpuData->accel_Z = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);
        
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    

    return mpuData;
}

/**
 * @see MPU.h
 * @private
 * Read the gyroscope from the MPU-6050 and store in the structure.
 * @param mpu the mpu
 */
MpuData* _readMpu6050GyroMpu(Mpu* mpu) {
    
    int data_h;
    int data_l;
    
    I2cBusConnection* i2cBusConnection = _mpu6050GetI2cBusConnection(mpu);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    MpuData* mpuData = &(mpu->mpuData);
       
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_RA_GYRO_XOUT_H);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_READ_ADDRESS);
    WaitI2C(i2cBus);
    
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->gyro_X = ((data_h<<8)|data_l);
    
    
    WaitI2C(i2cBus);
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->gyro_Y = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);
    
    WaitI2C(i2cBus);
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    
    mpuData->gyro_Z = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);
        
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    return mpuData;
}

/**
 * @see MPU.h
 * @private
 * Read the temperature from the MPU-6050 and store in the structure.
 * @param mpu the mpu
 */
MpuData* _readMpu6050TemperatureMpu(Mpu* mpu) {
    
    int data_h;
    int data_l;
    
    I2cBusConnection* i2cBusConnection = _mpu6050GetI2cBusConnection(mpu);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    MpuData* mpuData = &(mpu->mpuData);
       
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_RA_TEMP_OUT_H);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_READ_ADDRESS);
    WaitI2C(i2cBus);
    
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    
    mpuData->temperature = ((data_h<<8)|data_l);
        
    WaitI2C(i2cBus);
        
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    return mpuData;
}

void initMpuMPU6050(Mpu* mpu, I2cBusConnection* i2cBusConnection) {
    initMpu(mpu,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
            _readMpu6050GyroMpu,
            _readMpu6050TemperatureMpu,
            (int*) i2cBusConnection);
}