#ifndef PWM_MOTOR_H
#define PWM_MOTOR_H

void setMotorSpeeds(signed int leftSpeed, signed int rightSpeed);

signed int getLeftSpeed();

signed int getRightSpeed();

void stopMotors( void );

#endif
