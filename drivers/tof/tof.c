#include "tof.h"

#include "vl53l0x/vl53l0x_api.h"
#include "vl53l0x/vl53l0x_def.h"

#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "vl53l0x/vl53l0x_platform.h"

// TODO : Encapsulates the information

/** Store the latest status of the VL53L0X */
static VL53L0X_Error     tofStatus = VL53L0X_ERROR_NONE; ///< indicates whether or not the sensor has encountered an error
static VL53L0X_Dev_t            tofDevice;
static VL53L0X_Version_t        tofVersion;
static VL53L0X_DeviceInfo_t     tofDeviceInfo;

typedef char FixedVl53L0x [VL53L0X_MAX_STRING_LENGTH];

/**
 * To print specific String of vl530x_api
 */
void appendVl53l0xString(OutputStream* outputStream, FixedVl53L0x* s) {
    unsigned int i;
    char* sPointer = (char*)s;
    for (i = 0; i < VL53L0X_MAX_STRING_LENGTH; i++) {
        char c = *sPointer;
        append(outputStream, c);
        if (c == 0) {
            return;
        }
        sPointer++;
    }
}

bool tof_vl53l0x_begin(uint8_t i2c_addr, bool debug) {
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    // int32_t status_int;
    int32_t init_done = 0;

    uint32_t refSpadCount;
    uint8_t isApertureSpads;
    uint8_t VhvSettings;
    uint8_t PhaseCal;

    // Initialize Comms
    tofDevice.I2cDevAddr = i2c_addr;
    tofDevice.comms_type = 1;
    tofDevice.comms_speed_khz = 100;

    // TODO SVA Wire.begin(); // VL53L0X_i2c_init();

    // Data initialization
    tofStatus = VL53L0X_DataInit(&tofDevice); 

    // TODO SVA
    /*
    if (!setAddress(i2c_addr)) {
        return false;
    }
    */

    tofStatus = VL53L0X_GetDeviceInfo(&tofDevice, &tofDeviceInfo);

    if (tofStatus == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendString(debugOutputStream, "VL53L0X Info:\n");
            appendString(debugOutputStream, "Device Name: ");
            appendVl53l0xString(debugOutputStream, &(tofDeviceInfo.Name));
            appendString(debugOutputStream, ", Type: ");
            appendVl53l0xString(debugOutputStream, &(tofDeviceInfo.Type));
            appendString(debugOutputStream, ", ID: ");
            appendVl53l0xString(debugOutputStream, &(tofDeviceInfo.ProductId));
            appendString(debugOutputStream, "Rev Major: ");
            appendDec(debugOutputStream, tofDeviceInfo.ProductRevisionMajor);
            appendString(debugOutputStream, ", Minor: ");
            appendDec(debugOutputStream, tofDeviceInfo.ProductRevisionMinor);
            println(debugOutputStream);
        }

        if ((tofDeviceInfo.ProductRevisionMinor != 1) && (tofDeviceInfo.ProductRevisionMinor != 1)) {
            if (debug) {
                appendString(debugOutputStream, "Error expected cut 1.1 but found : ");
                appendDec(debugOutputStream, tofDeviceInfo.ProductRevisionMajor);
                appendString(debugOutputStream, ".");
                appendDec(debugOutputStream, tofDeviceInfo.ProductRevisionMinor);
                println(debugOutputStream);
            }

            tofStatus = VL53L0X_ERROR_NOT_SUPPORTED;
        }
    }

    if (tofStatus == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendString(debugOutputStream, "VL53L0X: StaticInit\n");
        }

        tofStatus = VL53L0X_StaticInit(&tofDevice); // Device Initialization
    }

    if (tofStatus == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendString(debugOutputStream, "VL53L0X: PerformRefSpadManagement\n");
        }

        tofStatus = VL53L0X_PerformRefSpadManagement(&tofDevice, &refSpadCount, &isApertureSpads); // Device Initialization

        if (debug) {
            appendString(debugOutputStream, "refSpadCount = ");
            appendDec(debugOutputStream, refSpadCount);
            appendString(debugOutputStream, ", isApertureSpads = ");
            appendDec(debugOutputStream, isApertureSpads);
        }
    }

    if (tofStatus == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendString(debugOutputStream, "VL53L0X: PerformRefCalibration\n");
        }

        tofStatus = VL53L0X_PerformRefCalibration(&tofDevice, &VhvSettings, &PhaseCal); // Device Initialization
    }

    if (tofStatus == VL53L0X_ERROR_NONE) {
        // no need to do this when we use VL53L0X_PerformSingleRangingMeasurement
        if (debug) {
            appendString(debugOutputStream, "VL53L0X: SetDeviceMode\n");
        }

        tofStatus = VL53L0X_SetDeviceMode(&tofDevice, VL53L0X_DEVICEMODE_SINGLE_RANGING); // Setup in single ranging mode
    }

    // Enable/Disable Sigma and Signal check
    if (tofStatus == VL53L0X_ERROR_NONE) {
        tofStatus = VL53L0X_SetLimitCheckEnable(&tofDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
    }

    if (tofStatus == VL53L0X_ERROR_NONE) {
        tofStatus = VL53L0X_SetLimitCheckEnable(&tofDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
    }

    if (tofStatus == VL53L0X_ERROR_NONE) {
        tofStatus = VL53L0X_SetLimitCheckEnable(&tofDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1);
    }

    if (tofStatus == VL53L0X_ERROR_NONE) {
        tofStatus = VL53L0X_SetLimitCheckValue(&tofDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, (FixPoint1616_t) (1.5 * 0.023 * 65536));
    }

    if (tofStatus == VL53L0X_ERROR_NONE) {
        return true;
    } else {
        if (debug) {
            appendString(debugOutputStream, "VL53L0X Error: ");
            appendDec(debugOutputStream, tofStatus);
        }

        return false;
    }
}