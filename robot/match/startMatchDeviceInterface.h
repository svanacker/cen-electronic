#ifndef START_MATCH_DEVICE_INTERFACE_H
#define START_MATCH_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Defines the pin which must be used to detect the start. */
#ifdef PROG_32
    #define START_DETECTOR_PIN      PORTGbits.RG3
#endif
#ifdef PROG_30
    #define START_DETECTOR_PIN      PORTFbits.RF6
#endif

/** Defines if the match is started or not. */
#define COMMAND_MATCH_IS_STARTED 'r'

/** Simulates that the match is started ! */
#define COMMAND_MATCH_SET_STARTED 'w'

// Notifications

/** Define the message sent to the PC to indicates start. */
#define NOTIFY_TO_PC_RESET      "xXyY"

/** Define the message sent to the PC to PIC reset. */
#define NOTIFY_TO_PC_START "s"

/**
 * The interface for the device StartMatchDetectorDevice.
 */
DeviceInterface* getStartMatchDeviceInterface();

#endif
