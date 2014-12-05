#ifndef START_MATCH_DETECTOR_DEVICE_INTERFACE_H
#define START_MATCH_DETECTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Defines the pin which must be used to detect the start. */
#ifdef PROG_32
#define START_DETECTOR_PIN      PORTGbits.RG3
#endif
#ifdef PROG_30
#define START_DETECTOR_PIN      PORTFbits.RF6
#endif


/** Define the message sent to the PC to indicates start. */
#define MESSAGE_TO_PC_RESET "xXyY"

/** Define the message sent to the PC to PIC reset. */
#define MESSAGE_TO_PC_START "s"

/** Define the message used to work in step by step mode. */
#define COMMAND_STEP_BY_STEP     'o'

/**
 * The interface for the device StartMatchDetectorDevice.
 */
DeviceInterface* getStartMatchDetectorDeviceInterface();

#endif
