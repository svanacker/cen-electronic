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

void mainHandleMotorPins(DualHBridgeMotor* dualHBridgeMotor) {
    PinList* pinList = (PinList*)(dualHBridgeMotor->pinListObject);
    if (pinList == NULL) {
        writeError(IO_PIN_LIST_NULL);
        return;
    }
    enum DualHBridgePinStopEventType pin1Stop = dualHBridgeMotor->pin1StopEventType;
    enum DualHBridgePinStopEventType pin2Stop = dualHBridgeMotor->pin2StopEventType;

    if (pin1Stop == PIN_STOP_EVENT_NO_ACTION && pin2Stop == PIN_STOP_EVENT_NO_ACTION) {
        return;
    }

    signed int motorValue1 = dualHBridgeMotor->dualHBridgeMotorReadValue(dualHBridgeMotor, HBRIDGE_1);
    signed int motorValue2 = dualHBridgeMotor->dualHBridgeMotorReadValue(dualHBridgeMotor, HBRIDGE_2);

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

            if ((pin1Stop == PIN_STOP_EVENT_LOW_STOP && !pinValue1)
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
        if ((dualHBridgeMotor->pin2UsageType == PIN_USAGE_TYPE_MOTOR_1_FORWARD_END && motorValue1 > 0)
            || (dualHBridgeMotor->pin2UsageType == PIN_USAGE_TYPE_MOTOR_1_BACKWARD_END && motorValue1 < 0)) {
            if ((pin2Stop == PIN_STOP_EVENT_LOW_STOP && !pinValue2)
                || (pin2Stop == PIN_STOP_EVENT_HIGH_STOP && pinValue2)) {
                newMotorValue1 = 0;
            }
        }
        // Motor 2
        else if ((dualHBridgeMotor->pin2UsageType == PIN_USAGE_TYPE_MOTOR_2_FORWARD_END && motorValue2 > 0)
            || (dualHBridgeMotor->pin2UsageType == PIN_USAGE_TYPE_MOTOR_2_BACKWARD_END && motorValue2 < 0)) {
            if ((pin2Stop == PIN_STOP_EVENT_LOW_STOP && !pinValue2)
                || (pin2Stop == PIN_STOP_EVENT_HIGH_STOP && pinValue2)) {
                newMotorValue2 = 0;
            }
        }
    }

    // if we must update the value of the HBridge
    if (newMotorValue1 != motorValue1 || newMotorValue2 != motorValue2) {
        dualHBridgeMotor->dualHBridgeMotorWriteValue(dualHBridgeMotor, newMotorValue1, newMotorValue2);
    }
}
