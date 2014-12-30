#include "../../common/pwm/motor/dualHBridgeMotorPwm.h"

void setMotorSpeeds(signed int leftSpeed, signed int rightSpeed) {
    pwmDualHBridgeMotor(leftSpeed, rightSpeed);
}

void stopMotors(void) {
    pwmDualHBridgeMotor(0, 0);
}

signed int getLeftSpeed() {
    return getDualHBridgeSpeed1();
}

signed int getRightSpeed() {
    return getDualHBridgeSpeed2();
}
