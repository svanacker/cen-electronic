#ifndef COMMON_MPU_H    /* Guard against multiple inclusion */
#define COMMON_MPU_H

#include <stdbool.h>

/**
 * Universal MPU definition.
 */
typedef struct {
    int accel_X;
    int accel_Y;
    int accel_Z;
    int accel_gyro_X;
    int accel_gyro_Y;
    int accel_gyro_Z;
    int temperature;
    float rall;  //rotation about the X-axis      phi
    float pitch;  // rotation about the Y-axis    theta
    float yaw;  //rotation about the Z-axis       psi
} MpuData;

// forward declaration
struct Mpu;
typedef struct Mpu Mpu;

/**
 * initialise the specific MPU hardware.
 * @param mpuParam the pointer on Mpu object
 */
typedef void InitMPUFunction(Mpu* mpuParam);

/**
 * Update the specific MPU hardware with value from the struct.
 * @param mpuParam the pointer on Mpu object
 */
typedef MpuData* GetAccelMPUFunction(Mpu* mpuParam);

/**
 * Update the software mpu structure from the hardware.
 * @param mpuParam the pointer on Mpu object.
 * @return the pointer on MpuData with refresh data (from hardware)
 */
typedef MpuData* GetGyroMPUFunction(Mpu* mpuParam);

/**
 * Update the software mpu structure from the hardware.
 * @param mpuParam the pointer on Mpu object.
 * @return the pointer on MpuData with refresh data (from hardware)
 */
typedef MpuData* GetTempMPUFunction(Mpu* mpuParam);


/**
 * Update the software mpu structure from the hardware.
 * @param mpuParam the pointer on Mpu object.
 * @return the pointer on MpuData with refresh data (from hardware)
 */
typedef MpuData* GetAllDataMPUFunction(Mpu* mpuParam);


/**
 * Defines the contract for a Mpu object.
 */
struct Mpu {
    /** the function which must be used to initialise the hardwre MPU */
    InitMPUFunction* initMPU;
    /** The function which must be used to write the content of data to the hardware. */
    GetAccelMPUFunction* getAccelMPU;
    /** The function which must be used to read the content in the hardware to store in the mpuData */
    GetGyroMPUFunction* getGyroMPU;
    /** The function wich must be used to read the content in the hardware to store the temp mpuData */
    GetTempMPUFunction* getTempMPU;
    /** */
    GetAllDataMPUFunction* getAllDataMPU;
    /** The content with all values. */    
    MpuData mpuData;
    /** A pointer on generic object (for example to store I2cBus ...). */
    int* object;
};

/**
 * Returns true if the mpu is initialized (if the fields of callbacks are NOT NULL), false else.
 * @param mpu a pointer on the Mpu object (Simulates POO programming) 
 * @return true if the mpu is initialized (if the fields of callbacks are NOT NULL), false else.
 */
bool isMpuInitialized(Mpu* Mpu);

/**
 * Initializes (Constructor in POO).
 * @param mpuParam a pointer on Mpu structure to initialize it.
 * @param GetAccelMPUFunction a pointer on the GetAccelMPUFunction
 * @param GetGyroMPUFunction a pointer on the GetGyroMPUFunction
 * @param object A pointer on generic object (for example to store I2cBus ...).
 */
void initMpu(Mpu* mpuParam, 
        InitMPUFunction* InitMPUFunction,
        GetAccelMPUFunction* GetAccelMPUFunction, 
        GetGyroMPUFunction* GetGyroMPUFunction, 
        GetTempMPUFunction* GetTempMPUFunction,
        GetAllDataMPUFunction* GetAllDataMPUFunction,
        int* object);

#endif