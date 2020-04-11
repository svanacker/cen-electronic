#include "dualHBridgeMotor.h"

#include <stdlib.h>

#include "../../common/io/pin.h"
#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerConstants.h"
#include "../../common/timer/timerList.h"

void initDualHBridge(DualHBridgeMotor* dualHBridgeMotor,
        dualHBridgeMotorInitFunction* dualHBridgeMotorInit,
        dualHBridgeMotorReadValueFunction* dualHBridgeMotorReadValue,
        dualHBridgeMotorWriteValueFunction* dualHBridgeMotorWriteValue,
        dualHBridgeMotorGetSoftwareRevisionFunction* dualHBridgeMotorGetSoftwareRevision,
        int* object,
        int* pinListObject
    ) {
    dualHBridgeMotor->dualHBridgeMotorInit = dualHBridgeMotorInit;
    dualHBridgeMotor->dualHBridgeMotorReadValue = dualHBridgeMotorReadValue;
    dualHBridgeMotor->dualHBridgeMotorWriteValue = dualHBridgeMotorWriteValue;
    dualHBridgeMotor->pin1StopEventType = PIN_STOP_EVENT_NO_ACTION;
    dualHBridgeMotor->pin2StopEventType = PIN_STOP_EVENT_NO_ACTION;
    dualHBridgeMotor->pin1UsageType = PIN_USAGE_TYPE_NO_USAGE;
    dualHBridgeMotor->pin2UsageType = PIN_USAGE_TYPE_NO_USAGE;

    dualHBridgeMotor->dualHBridgeMotorGetSoftwareRevision = dualHBridgeMotorGetSoftwareRevision;
    dualHBridgeMotor->object = object;
    dualHBridgeMotor->pinListObject = pinListObject;
}

void stopMotors(DualHBridgeMotor* dualHBridgeMotor) {
    dualHBridgeMotor->dualHBridgeMotorWriteValue(dualHBridgeMotor, 0, 0);
}

void setMotorSpeeds(DualHBridgeMotor* dualHBridgeMotor, signed int hBridgeSpeed1, signed int hBridgeSpeed2) {
    dualHBridgeMotor->dualHBridgeMotorWriteValue(dualHBridgeMotor, hBridgeSpeed1, hBridgeSpeed2);
}

// TIMER PART

/**
 * The interrupt timer to know if we must stop the motor.
 */
void interruptMotorTimerCallbackFunc(Timer* timer) {
    DualHBridgeMotor* dualHBridgeMotor = (DualHBridgeMotor*)timer->object;
    PinList* pinList = (PinList*) (dualHBridgeMotor->pinListObject);
    if (pinList == NULL) {
        writeError(IO_PIN_LIST_NULL);
        return;
    }
    signed int motorValue1 = dualHBridgeMotor->dualHBridgeMotorReadValue(dualHBridgeMotor, HBRIDGE_1);
    enum DualHBridgePinStopEventType pin1Stop = dualHBridgeMotor->pin1StopEventType;
    signed int motorValue2 = dualHBridgeMotor->dualHBridgeMotorReadValue(dualHBridgeMotor, HBRIDGE_2);
    enum DualHBridgePinStopEventType pin2Stop = dualHBridgeMotor->pin2StopEventType;

    unsigned char pinIndex1 = PIN_INDEX_RB12;
    unsigned char pinIndex2 = PIN_INDEX_RB13;

    signed int newMotorValue1 = motorValue1;
    signed int newMotorValue2 = motorValue2;

    // Pin1
    if (pin1Stop != PIN_STOP_EVENT_NO_ACTION) {
        bool pinValue1 = getPinValue(pinList, pinIndex1);

        // Motor 1
        if ((dualHBridgeMotor->pin1UsageType == PIN_USAGE_TYPE_MOTOR_1_FORWARD_END && motorValue1 > 0)
            || (dualHBridgeMotor->pin1UsageType == PIN_USAGE_TYPE_MOTOR_1_BACKWARD_END && motorValue1 < 0)) {

            if ( (pin1Stop == PIN_STOP_EVENT_LOW_STOP && !pinValue1)
                || (pin1Stop == PIN_STOP_EVENT_HIGH_STOP && pinValue1)) {
                newMotorValue1 = 0;
            }
        }
        // Motor 2
        else if ((dualHBridgeMotor->pin1UsageType == PIN_USAGE_TYPE_MOTOR_2_FORWARD_END && motorValue2 > 0)
            || (dualHBridgeMotor->pin1UsageType == PIN_USAGE_TYPE_MOTOR_2_BACKWARD_END && motorValue2 < 0)) {
            if ((pin1Stop == PIN_STOP_EVENT_LOW_STOP && !pinValue1)
                || (pin1Stop == PIN_STOP_EVENT_HIGH_STOP && pinValue1)) {
                newMotorValue2 = 0;
            }
        }
    }
    // Pin 2
    if (pin2Stop != PIN_STOP_EVENT_NO_ACTION) {
        bool pinValue2 = getPinValue(pinList, pinIndex2);

        // Motor 1
        if ((dualHBridgeMotor->pin1UsageType == PIN_USAGE_TYPE_MOTOR_1_FORWARD_END && motorValue1 > 0)
            || (dualHBridgeMotor->pin1UsageType == PIN_USAGE_TYPE_MOTOR_1_BACKWARD_END && motorValue1 < 0)) {
            if ((pin2Stop == PIN_STOP_EVENT_LOW_STOP && !pinValue2)
                || (pin2Stop == PIN_STOP_EVENT_HIGH_STOP && pinValue2)) {
                newMotorValue1 = 0;
            }
        }
        // Motor 2
        else if ((dualHBridgeMotor->pin1UsageType == PIN_USAGE_TYPE_MOTOR_2_FORWARD_END && motorValue2 > 0)
            || (dualHBridgeMotor->pin1UsageType == PIN_USAGE_TYPE_MOTOR_2_BACKWARD_END && motorValue2 < 0)) {
            if ((pin2Stop == PIN_STOP_EVENT_LOW_STOP && !pinValue2)
                || (pin2Stop == PIN_STOP_EVENT_HIGH_STOP && pinValue2)) {
                newMotorValue2 = 0;
            }
        }
    }

    // if we must update the value of the HBridge
    if (newMotorValue1 != motorValue1 && newMotorValue2 != motorValue2) {
        dualHBridgeMotor->dualHBridgeMotorWriteValue(dualHBridgeMotor, newMotorValue1, motorValue2);
    }
}

void initDualHBridgeTimer(DualHBridgeMotor* dualHBridgeMotor) {
    Timer* motorTimer = getTimerByCode(MOTOR_TIMER_CODE);
    // Avoid to add several timer of the same nature
    if (motorTimer == NULL) {
        addTimer(MOTOR_TIMER_CODE,
                TIME_DIVIDER_10_HERTZ,
                &interruptMotorTimerCallbackFunc,
                "MOTOR",
                (int*) dualHBridgeMotor);
    }
}
