#ifndef ARM_DEVICE_2012_H
#define ARM_DEVICE_2012_H

#include "../../device/device.h"


#define ARM_LEFT_PWM_INDEX 		0x01
#define ARM_RIGHT_PWM_INDEX 	0x02


#define ARM_LEFT_DOWN 		0x0260
#define ARM_LEFT_UP			0x0598

#define ARM_RIGHT_DOWN		0x0940
#define ARM_RIGHT_UP		0x0640

void upArm(int armIndex);

void downArm(int armIndex);

/**
 * The descriptor for the arm 2012 device.
 */
DeviceDescriptor* getArm2012DeviceDescriptor();

#endif
