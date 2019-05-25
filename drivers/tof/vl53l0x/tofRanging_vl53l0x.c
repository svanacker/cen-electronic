#include "tofRanging_vl53l0x.h"

#include "tof_vl53l0x.h"
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

#include "../../../common/timer/delayTimer.h"

#include "../../../drivers/i2c/multiplexer/multiplexer.h"
#include "../../../drivers/i2c/multiplexer/multiplexerList.h"

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
 * Tof POO Implementation for VL53L0X
 */
unsigned int tofSensorGetDistanceVL53L0XMM(TofSensor* tofSensor) {
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_NULL);
        return 0;
    }
    TofSensorVL53L0X* tofSensorVL53L0X = getTofSensorVL53L0X(tofSensor);
    if (tofSensorVL53L0X == NULL) {
        writeError(TOF_SENSOR_OBJECT_NULL);
        return 0;
    }
    // If we detect a problem of I2cBusConnection, we disable the tof !
    if (tofSensorVL53L0X->i2cBusConnection != NULL) {
        if (tofSensorVL53L0X->i2cBusConnection->error != ERROR_NONE) {
            tofSensor->enabled = false;
            return 0;
        }
    }
    // If we use a multiplexer, we must select the channel first
    Multiplexer* multiplexer = tofSensor->multiplexer;
    if (multiplexer != NULL) {
        multiplexerEnableOnly(multiplexer, tofSensor->multiplexerChannel);
    }
    // Single Mode
    // getSingleRangingMeasurement(tofSensorVL53L0X, false);

    // Continous Mode
    getContinousRangingMeasurement(tofSensorVL53L0X, false);

    VL53L0X_RangingMeasurementData_t* data = &(tofSensorVL53L0X->rangingMeasurementData);
    
    // Store the last Value
    tofSensor->lastDistanceMM = data->RangeMilliMeter;

    return data->RangeMilliMeter;
}
