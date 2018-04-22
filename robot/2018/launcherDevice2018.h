#ifndef LAUNCHER_DEVICE_2018_H
#define LAUNCHER_DEVICE_2018_H

#include "../../common/motor/dualHBridgeMotor.h"

#include "../../device/device.h"

#include "../../drivers/relay/relay.h"
#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/tof/tofList.h"

// LAUNCHER

// To activate Relay
#define LAUNCHER_RIGHT_RELAY_INDEX                     1
#define LAUNCHER_LEFT_RELAY_INDEX                      2

// To Read IoExpander
#define LAUNCHER_RIGHT_IO_EXPANDER_INDEX               0
#define LAUNCHER_LEFT_IO_EXPANDER_INDEX                1

// To Light On
#define LAUNCHER_LIGHT_RIGHT_SERVO_INDEX               1
#define LAUNCHER_LIGHT_RIGHT_SERVO_OFF_POSITION        1500
#define LAUNCHER_LIGHT_RIGHT_SERVO_ON_POSITION         2200
#define LAUNCHER_LIGHT_RIGHT_SERVO_DELAY                75

#define LAUNCHER_LIGHT_LEFT_SERVO_INDEX                2
#define LAUNCHER_LIGHT_LEFT_SERVO_OFF_POSITION         1500
#define LAUNCHER_LIGHT_LEFT_SERVO_ON_POSITION          800
#define LAUNCHER_LIGHT_LEFT_SERVO_DELAY                75

// For Dirty Ejector
#define LAUNCHER_DIRTY_EJECTOR_SERVO_INDEX             5 
#define LAUNCHER_DIRTY_EJECTOR_SERVO_OFF_POSITION      1500
#define LAUNCHER_DIRTY_EJECTOR_SERVO_ON_POSITION       1200
#define LAUNCHER_DIRTY_EJECTOR_SERVO_DELAY             75

// GRABBER
#define DISTRIBUTOR_ROTATE_LEFT_IO_EXPANDER_INDEX      3
#define DISTRIBUTOR_ROTATE_RIGHT_IO_EXPANDER_INDEX     4

#define LAUNCHER_2018_DEFAULT_SPEED                    40

// Forward declaration
typedef struct Launcher2018 Launcher2018;

/** Encapsulates all information needed to launch balls */
struct Launcher2018{
    /** To detect if the launcher position */
    IOExpander* ioExpander;
    /** To launch balls */
    Relay* relay;
    /** The MD22 */
    DualHBridgeMotor* dualHBridgeMotor;
    /** The tof Sensor List */
    TofSensorList* tofSensorList;
};

void launch2018(int launcherIndex, bool prepare);

/**
 * The descriptor for the launcher 2018 device.
 */
DeviceDescriptor* getLauncher2018DeviceDescriptor(Launcher2018* launcher2018);

/**
 * Initializes the Launcher 2018 structure.
 * @param launcher2018
 * @param ioExpander
 * @param relay
 */
void initLauncher2018(Launcher2018* launcher2018,
                      IOExpander* ioExpander,
                      Relay* relay,
                      DualHBridgeMotor* dualHBridgeMotor,
                      TofSensorList* tofSensorList);

#endif
