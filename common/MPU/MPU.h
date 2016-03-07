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
    int gyro_X;
    int gyro_Y;
    int gyro_Z;
    int temperature;
} MpuData;

// forward declaration
struct Mpu;
typedef struct Mpu Mpu;

/**
 * Update the specific MPU hardware with value from the struct.
 * @param mpuParam the pointer on Mpu object
 */
typedef void WriteMpuFunction(Mpu* mpuParam);

/**
 * Update the software mpu structure from the hardware.
 * @param mpuParam the pointer on Mpu object.
 * @return the pointer on MpuData with refresh data (from hardware)
 */
typedef MpuData* ReadMpuFunction(Mpu* mpuParam);

/**
 * Defines the contract for a Mpu object.
 */
struct Mpu {
    /** The function which must be used to write the content of data to the hardware. */
    WriteMpuFunction* writeMpu;
    /** The function which must be used to read the content in the hardware to store in the mpuData */
    ReadMpuFunction* readMpu;
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
 * @param WriteMpuFunction a pointer on the writeMpuFunction
 * @param ReadMpuFunction a pointer on the readMpuFunction
 * @param object A pointer on generic object (for example to store I2cBus ...).
 */
void initMpu(Mpu* mpuParam, 
        WriteMpuFunction* writeMpuFunction, 
        ReadMpuFunction* readMpuFunction, 
        int* object);

#endif