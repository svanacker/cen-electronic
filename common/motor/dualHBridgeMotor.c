#include "dualHBridgeMotor.h"

#include <stdlib.h>

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerConstants.h"
#include "../../common/timer/timerList.h"
//#include "pin.h"

void initDualHBridge(DualHBridgeMotor* dualHBridgeMotor,
        dualHBridgeMotorInitFunction* dualHBridgeMotorInit,
        dualHBridgeMotorReadValueFunction* dualHBridgeMotorReadValue,
        dualHBridgeMotorWriteValueFunction* dualHBridgeMotorWriteValue,
        dualHBridgeMotorGetSoftwareRevisionFunction* dualHBridgeMotorGetSoftwareRevision,
        int* object) {
    dualHBridgeMotor->dualHBridgeMotorInit = dualHBridgeMotorInit;
    dualHBridgeMotor->dualHBridgeMotorReadValue = dualHBridgeMotorReadValue;
    dualHBridgeMotor->dualHBridgeMotorWriteValue = dualHBridgeMotorWriteValue;
    dualHBridgeMotor->pin1StopEventType = NO_ACTION;
    dualHBridgeMotor->pin2StopEventType = NO_ACTION;
    dualHBridgeMotor->dualHBridgeMotorGetSoftwareRevision = dualHBridgeMotorGetSoftwareRevision;
    dualHBridgeMotor->object = object;
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
    DualHBridgeMotor* dualHBridgeMotor = (DualHBridgeMotor*) timer->object;
    if (dualHBridgeMotor->pin1UsageType != NO_USAGE) {
        enum DualHBridgePinStopEventType pin1Stop = dualHBridgeMotor->pin1StopEventType;
        /*
        switch (pin1Stop):
        case NO_ACTION:
        }
        if (pin1Stop != NO_ACTION) {
            
        }
         */
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
