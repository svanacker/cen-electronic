#include "tof_vl53l0x.h"
#include "tofNetwork_vl53l0x.h"
#include "tofRanging_vl53l0x.h"

#include "../tof.h"

#include "vl53l0x_api.h"
#include "vl53l0x_def.h"
#include "vl53l0x_platform.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../../common/delay/cenDelay.h"


#include "../../../common/error/error.h"

#include "../../../common/i2c/i2cConstants.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"

#include "../../../common/math/cenMath.h"

#include "../../../common/timer/delayTimer.h"

#include "../../../drivers/i2c/multiplexer/multiplexer.h"
#include "../../../drivers/i2c/multiplexer/multiplexerList.h"

// Store the latest status of the VL53L0X
// indicates whether or not the sensor has encountered an error
typedef char FixedVl53L0x [VL53L0X_MAX_STRING_LENGTH];

/**
 * To print specific String of vl530x_api
 */
void appendVl53l0xString(OutputStream* outputStream, FixedVl53L0x* s) {
    unsigned int i;
    unsigned char* sPointer = (unsigned char*) s;
    for (i = 0; i < VL53L0X_MAX_STRING_LENGTH; i++) {
        unsigned char c = *sPointer;
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
            return false;
        }
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendString(debugOutputStream, "VL53L0X: StaticInit\n");
        }

        tofSensorVL53L0X->status = VL53L0X_StaticInit(tofDevice); // Device Initialization
    } else {
        return false;
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendString(debugOutputStream, "VL53L0X: PerformRefSpadManagement\n");
        }

        // Device Initialization
        tofSensorVL53L0X->status = VL53L0X_PerformRefSpadManagement(tofDevice, &refSpadCount, &isApertureSpads);

        if (debug) {
            appendStringAndDec(debugOutputStream, "refSpadCount = ", refSpadCount);
            appendStringAndDec(debugOutputStream, ", isApertureSpads = ", isApertureSpads);
        }
    } else {
        return false;
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        if (debug) {
            appendStringLN(debugOutputStream, "VL53L0X: PerformRefCalibration");
        }

        // Device Initialization
        tofSensorVL53L0X->status = VL53L0X_PerformRefCalibration(tofDevice, &VhvSettings, &PhaseCal);
    } else {
        return false;
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        // no need to do this when we use VL53L0X_PerformSingleRangingMeasurement
        if (debug) {
            appendStringLN(debugOutputStream, "VL53L0X: SetDeviceMode");
        }

        // In Single
        // tofSensorVL53L0X->status = VL53L0X_SetDeviceMode(tofDevice, VL53L0X_DEVICEMODE_SINGLE_RANGING);

        // In continuous
        tofSensorVL53L0X->status = VL53L0X_SetDeviceMode(tofDevice, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
    } else {
        return false;
    }

    // Enable/Disable Sigma and Signal check
    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        tofSensorVL53L0X->status = VL53L0X_SetLimitCheckEnable(tofDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
    } else {
        return false;
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        tofSensorVL53L0X->status = VL53L0X_SetLimitCheckEnable(tofDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
    } else {
        return false;
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        tofSensorVL53L0X->status = VL53L0X_SetLimitCheckEnable(tofDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1);
    } else {
        return false;
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        tofSensorVL53L0X->status = VL53L0X_SetLimitCheckValue(tofDevice, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, (FixPoint1616_t) (1.5 * 0.023 * 65536));
    } else {
        return false;
    }

    // If in Continuous Mode
    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        appendString(debugOutputStream, "Call of VL53L0X_StartMeasurement ...");
        tofSensorVL53L0X->status = VL53L0X_StartMeasurement(tofDevice);
    } else {
        return false;
    }

    if (tofSensorVL53L0X->status == VL53L0X_ERROR_NONE) {
        return true;
    } else {
        if (debug) {
            OutputStream* errorOutputStream = getDebugOutputStreamLogger();
            appendString(errorOutputStream, "VL53L0X Error: ");
            appendDec(errorOutputStream, tofSensorVL53L0X->status);
        }

        return false;
    }
}

/**
 * Get the underlying tofSensor object.
 * @param TofSensor
 * @return 
 */
TofSensorVL53L0X* getTofSensorVL53L0X(TofSensor* tofSensor) {
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_NULL);
        return NULL;
    }
    return (TofSensorVL53L0X*) (tofSensor->object);
}

/**
 * Tof POO Implementation for VL53L0X
 * @private
 */
bool tofSensorStartVL53L0X(TofSensor* tofSensor, bool restart, bool debug) {
    TofSensorVL53L0X* tofSensorVL53L0X = getTofSensorVL53L0X(tofSensor);
    if (tofSensorVL53L0X == NULL) {
        writeError(TOF_SENSOR_OBJECT_NULL);
        return false;
    }
    if (restart) {
        // The Tof structure are already initialized, so we just recall
        if (tofSensor->hardwareRestartable) {
            IOExpander* hardRestartIOExpander = tofSensor->hardwareRestartIOExpander;
            if (hardRestartIOExpander == NULL) {
                writeError(IO_EXPANDER_NULL);
                return false;
            }
            // Shutdown via XSHUT pin to low
            hardRestartIOExpander->ioExpanderWriteSingleValue(hardRestartIOExpander, tofSensor->hardwareRestartIOExpanderIoIndex, false);
            timerDelayMilliSeconds(10);
            // Start via XSHUT pin to high
            hardRestartIOExpander->ioExpanderWriteSingleValue(hardRestartIOExpander, tofSensor->hardwareRestartIOExpanderIoIndex, true);
            timerDelayMilliSeconds(30);
            
            // Execute after the HARD RESET the standard start
            return tofStart(tofSensor);
        }
        else {
            // For the "Soft" restart, the connection is already set, but we need to use
            // The multiplexer ...
            tofSensorSelectRightI2cBusConnection(tofSensor, tofSensor->targetAddress, debug);
        }
        bool successInit = tof_vl53l0x_begin(tofSensorVL53L0X, true);
        if (!successInit) {
            tofSensor->startResult = TOF_SENSOR_START_RESULT_INIT_PROBLEM;
            tofSensor->enabled = false;
            return false;
        } else {
            tofSensor->startResult = TOF_SENSOR_START_RESULT_ALREADY_STARTED;
            return true;
        }
        // To let the hardware device initialise properly
        timerDelayMilliSeconds(30);
    } else {
        if (debug) {
            appendString(getDebugOutputStreamLogger(), "    INIT VL53 ...");
        }

        I2cBusConnection* tofBusConnection = tofSensorSelectRightI2cBusConnection(tofSensor, VL530X_ADDRESS_BASE_ADDRESS, debug);
        tofSensorVL53L0X->i2cBusConnection = tofBusConnection;

        bool successInit = tof_vl53l0x_begin(tofSensorVL53L0X, true);
        if (!successInit) {
            // Maybe the sensor is always connected (by the Uart power) and has not reboot
            // We try to reach it at the new address
            tofBusConnection->i2cAddress = tofSensor->targetAddress;
            successInit = tof_vl53l0x_begin(tofSensorVL53L0X, true);

            // If KO
            if (!successInit) {
                tofSensor->startResult = TOF_SENSOR_START_RESULT_INIT_PROBLEM;
                tofSensor->enabled = false;
                return false;
            } else {
                tofSensor->startResult = TOF_SENSOR_START_RESULT_ALREADY_STARTED;
            }
            // To let the hardware device initialise properly
            timerDelayMilliSeconds(30);
        } else {
            if (tofSensorChangeAddressIfNeeded(tofSensor)) {
                tofSensor->startResult = TOF_SENSOR_START_RESULT_OK;
            } else {
                tofSensor->startResult = TOF_SENSOR_START_RESULT_CHANGE_ADDRESS_PROBLEM;
            }
        }
    }

    if (debug) {
        appendStringLN(getDebugOutputStreamLogger(), "OK");
    }
    return tof_vl53l0x_begin(tofSensorVL53L0X, true);
}

void initTofSensorVL53L0X(TofSensor* tofSensor,
        TofSensorVL53L0X* tofSensorVL53L0X
        ) {
    tofSensor->type = TOF_SENSOR_TYPE_VL53L0X;

    // Orientation and Beam Angle
    // TODO : VL53L0X value of beam angle : https://forum.pololu.com/t/vl53l0x-beam-width-angle/11483
    // Be it could change for another tof
    tofSensor->beamAngleRadian = degToRad(25.0f);

    initTofSensor(tofSensor,
            &tofSensorStartVL53L0X,
            &tofSensorGetDistanceVL53L0XMM,
            (int*) tofSensorVL53L0X);
}
