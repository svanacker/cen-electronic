#include "tof_vl53l0x.h"

#include "../tof.h"

#include "vl53l0x_api.h"
#include "vl53l0x_def.h"
#include "vl53l0x_platform.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../../common/delay/cenDelay.h"

#include "../../../common/i2c/i2cConstants.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"

// Store the latest status of the VL53L0X
// indicates whether or not the sensor has encountered an error
typedef char FixedVl53L0x [VL53L0X_MAX_STRING_LENGTH];

/**
 * To print specific String of vl530x_api
 */
void appendVl53l0xString(OutputStream* outputStream, FixedVl53L0x* s) {
    unsigned int i;
    char* sPointer = (char*) s;
    for (i = 0; i < VL53L0X_MAX_STRING_LENGTH; i++) {
        char c = *sPointer;
        if (c == 0) {
            return;
        }
        append(outputStream, c);
        sPointer++;
    }
}

bool tof_vl53l0x_begin(TofSensorVL53L0X* tofSensorVL53L0X, bool debug) {
    tofSensorVL53L0X->status = VL53L0X_ERROR_NONE;
    VL53L0X_Dev_t* tofDevice = &(tofSensorVL53L0X->device);
    VL53L0X_DeviceInfo_t* tofDeviceInfo = &(tofSensorVL53L0X->deviceInfo);

    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    uint32_t refSpadCount;
    uint8_t isApertureSpads;
    uint8_t VhvSettings;
    uint8_t PhaseCal;

    // Initialize Comms
    I2cBusConnection* i2cBusConnection = tofSensorVL53L0X->i2cBusConnection;
    tofDevice->I2cDevAddr = i2cBusConnection->i2cAddress;
    tofDevice->comms_type = 1;
    tofDevice->comms_speed_khz = 100;

    // Data initialization
    tofSensorVL53L0X->status = VL53L0X_DataInit(tofDevice);

    tofSensorVL53L0X->status = VL53L0X_GetDeviceInfo(tofDevice, tofDeviceInfo);

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendString(debugOutputStream, "VL53L0X Info:\n");
            appendString(debugOutputStream, "Device Name: ");
            appendVl53l0xString(debugOutputStream, &(tofDeviceInfo->Name));
            appendString(debugOutputStream, ", Type: ");
            appendVl53l0xString(debugOutputStream, &(tofDeviceInfo->Type));
            appendString(debugOutputStream, ", ID: ");
            appendVl53l0xString(debugOutputStream, &(tofDeviceInfo->ProductId));
            appendString(debugOutputStream, "Rev Major: ");
            appendDec(debugOutputStream, tofDeviceInfo->ProductRevisionMajor);
            appendString(debugOutputStream, ", Minor: ");
            appendDec(debugOutputStream, tofDeviceInfo->ProductRevisionMinor);
            println(debugOutputStream);
        }

        if ((tofDeviceInfo->ProductRevisionMinor != 1) && (tofDeviceInfo->ProductRevisionMinor != 1)) {
            if (debug) {
                appendString(debugOutputStream, "Error expected cut 1.1 but found : ");
                appendDec(debugOutputStream, tofDeviceInfo->ProductRevisionMajor);
                appendString(debugOutputStream, ".");
                appendDec(debugOutputStream, tofDeviceInfo->ProductRevisionMinor);
                println(debugOutputStream);
            }

            tofSensorVL53L0X->status = VL53L0X_ERROR_NOT_SUPPORTED;
        }
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendString(debugOutputStream, "VL53L0X: StaticInit\n");
        }

        tofSensorVL53L0X->status = VL53L0X_StaticInit(tofDevice); // Device Initialization
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendString(debugOutputStream, "VL53L0X: PerformRefSpadManagement\n");
        }

        // Device Initialization
        tofSensorVL53L0X->status = VL53L0X_PerformRefSpadManagement(tofDevice, &refSpadCount, &isApertureSpads);

        if (debug) {
            appendString(debugOutputStream, "refSpadCount = ");
            appendDec(debugOutputStream, refSpadCount);
            appendString(debugOutputStream, ", isApertureSpads = ");
            appendDec(debugOutputStream, isApertureSpads);
        }
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendString(debugOutputStream, "VL53L0X: PerformRefCalibration\n");
        }

        // Device Initialization
        tofSensorVL53L0X->status = VL53L0X_PerformRefCalibration(tofDevice, &VhvSettings, &PhaseCal);
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        // no need to do this when we use VL53L0X_PerformSingleRangingMeasurement
        if (debug) {
            appendString(debugOutputStream, "VL53L0X: SetDeviceMode\n");
        }
        
        // In Single
        // tofSensorVL53L0X->status = VL53L0X_SetDeviceMode(tofDevice, VL53L0X_DEVICEMODE_SINGLE_RANGING);

        // In continuous
        tofSensorVL53L0X->status = VL53L0X_SetDeviceMode(tofDevice, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
    }

    // Enable/Disable Sigma and Signal check
    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        tofSensorVL53L0X->status = VL53L0X_SetLimitCheckEnable(tofDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        tofSensorVL53L0X->status = VL53L0X_SetLimitCheckEnable(tofDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        tofSensorVL53L0X->status = VL53L0X_SetLimitCheckEnable(tofDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1);
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        tofSensorVL53L0X->status = VL53L0X_SetLimitCheckValue(tofDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, (FixPoint1616_t) (1.5 * 0.023 * 65536));
    }
    
    // If in Continuous Mode
    if(tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
		printf ("Call of VL53L0X_StartMeasurement\n");
		tofSensorVL53L0X->status = VL53L0X_StartMeasurement(tofDevice);
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        return true;
    } else {
        if (debug) {
            appendString(debugOutputStream, "VL53L0X Error: ");
            appendDec(debugOutputStream, tofSensorVL53L0X->status);
        }

        return false;
    }
}

bool tofSetAddress(TofSensorVL53L0X* tofSensorVL53L0X, I2cBusConnection* newI2cBusConnection) {
    tofSensorVL53L0X->status = VL53L0X_ERROR_NONE;
    VL53L0X_Dev_t* tofDevice = &(tofSensorVL53L0X->device);

    uint8_t newAddress = newI2cBusConnection->i2cAddress;
    if (newAddress != VL530X_ADDRESS_0) {
        tofSensorVL53L0X->status = VL53L0X_SetDeviceAddress(tofDevice, newAddress);
        delaymSec(10);
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        tofDevice->I2cDevAddr = newAddress;
        tofSensorVL53L0X->i2cBusConnection = newI2cBusConnection;
        return true;
    }
    return false;
}

VL53L0X_Error getSingleRangingMeasurement(TofSensorVL53L0X* tofSensorVL53L0X, bool debug) {
    tofSensorVL53L0X->status = VL53L0X_ERROR_NONE;
    VL53L0X_Dev_t* tofDevice = &(tofSensorVL53L0X->device);
    VL53L0X_RangingMeasurementData_t* rangingMeasurementData = &(tofSensorVL53L0X->rangingMeasurementData);

    FixPoint1616_t limitCheckCurrent;
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendString(debugOutputStream, "sVL53L0X: PerformSingleRangingMeasurement\n");
        }
        tofSensorVL53L0X->status = VL53L0X_PerformSingleRangingMeasurement(tofDevice, rangingMeasurementData);

        if (debug) {
            VL53L0X_GetLimitCheckCurrent(tofDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, &limitCheckCurrent);

            appendString(debugOutputStream, "RANGE IGNORE THRESHOLD: ");
            appendDecf(debugOutputStream, limitCheckCurrent / 65536.0f);
            println(debugOutputStream);
            appendString(debugOutputStream, "Measured distance: ");
            appendDecf(debugOutputStream, rangingMeasurementData->RangeMilliMeter);
            println(debugOutputStream);
        }
    }

    return tofSensorVL53L0X->status;
}

VL53L0X_Error waitMeasurementDataReady(VL53L0X_DEV Dev) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint8_t NewDatReady = 0;
    uint32_t LoopNb;

    // Wait until it finished
    // use timeout to avoid deadlock
    if (Status == VL53L0X_ERROR_NONE) {
        LoopNb = 0;
        do {
            Status = VL53L0X_GetMeasurementDataReady(Dev, &NewDatReady);
            if ((NewDatReady == 0x01) || Status != VL53L0X_ERROR_NONE) {
                break;
            }
            LoopNb = LoopNb + 1;
            VL53L0X_PollingDelay(Dev);
        } while (LoopNb < VL53L0X_DEFAULT_MAX_LOOP);

        if (LoopNb >= VL53L0X_DEFAULT_MAX_LOOP) {
            Status = VL53L0X_ERROR_TIME_OUT;
        }
    }

    return Status;
}

VL53L0X_Error getContinousRangingMeasurement(TofSensorVL53L0X* tofSensorVL53L0X, bool debug) {
    tofSensorVL53L0X->status = VL53L0X_ERROR_NONE;
    VL53L0X_Dev_t* tofDevice = &(tofSensorVL53L0X->device);
    VL53L0X_RangingMeasurementData_t* rangingMeasurementData = &(tofSensorVL53L0X->rangingMeasurementData);

    FixPoint1616_t limitCheckCurrent;
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendString(debugOutputStream, "sVL53L0X: VL53L0X_GetRangingMeasurementData\n");
        }
        waitMeasurementDataReady(tofDevice);
        tofSensorVL53L0X->status = VL53L0X_GetRangingMeasurementData(tofDevice, rangingMeasurementData);

        if (debug) {
            VL53L0X_GetLimitCheckCurrent(tofDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, &limitCheckCurrent);

            appendString(debugOutputStream, "RANGE IGNORE THRESHOLD: ");
            appendDecf(debugOutputStream, limitCheckCurrent / 65536.0f);
            println(debugOutputStream);
            appendString(debugOutputStream, "Measured distance: ");
            appendDecf(debugOutputStream, rangingMeasurementData->RangeMilliMeter);
            println(debugOutputStream);
        }
    }

    return tofSensorVL53L0X->status;
}

/**
 * Get the underlying tofSensor object.
 * @param TofSensor
 * @return 
 */
TofSensorVL53L0X* getTofSensorVL53L0X(TofSensor* tofSensor) {
    return (TofSensorVL53L0X*) (tofSensor->object);
}

/**
 * Tof POO Implementation for VL53L0X
 * @private
 */
bool tofSensorInitVL53L0X(TofSensor* tofSensor) {
    TofSensorVL53L0X* tofSensorVL53L0X = getTofSensorVL53L0X(tofSensor);
    tof_vl53l0x_begin(tofSensorVL53L0X, true);
    return true;
}

/**
 * Tof POO Implementation for VL53L0X
 * @private
 */
unsigned int tofSensorGetDistanceVL53L0XMM(TofSensor* tofSensor) {
    TofSensorVL53L0X* tofSensorVL53L0X = getTofSensorVL53L0X(tofSensor);

    // Single Mode
    // getSingleRangingMeasurement(tofSensorVL53L0X, false);

    // Continous Mode
    getContinousRangingMeasurement(tofSensorVL53L0X, false);

    VL53L0X_RangingMeasurementData_t* data = &(tofSensorVL53L0X->rangingMeasurementData);
    
    // Store the last Value
    tofSensor->lastDistanceMM = data->RangeMilliMeter;

    return data->RangeMilliMeter;
}

void initTofSensorVL53L0X(TofSensor* tofSensor,
        TofSensorVL53L0X* tofSensorVL53L0X,
        I2cBusConnection* i2cBusConnection,
        unsigned int thresholdDistanceMM,
        float orientationRadian) {
    tofSensorVL53L0X->i2cBusConnection = i2cBusConnection;
    initTofSensor(tofSensor,
            &tofSensorInitVL53L0X,
            &tofSensorGetDistanceVL53L0XMM,
            thresholdDistanceMM,
            orientationRadian,
            (int*) tofSensorVL53L0X);

}
