#ifndef LAUNCHER_DEVICE_2018_H
#define LAUNCHER_DEVICE_2018_H

#include "../../device/device.h"

#include "../../drivers/relay/relay.h"
#include "../../drivers/ioExpander/ioExpander.h"

#define LAUNCHER_LEFT_INDEX          0
#define LAUNCHER_RIGHT_INDEX         1

// To activate Relay
#define LAUNCHER_LEFT_RELAY_INDEX         1
#define LAUNCHER_RIGHT_RELAY_INDEX        2

// To Read IoExapnder
#define LAUNCHER_LEFT_IO_EXPANDER_INDEX   7
#define LAUNCHER_RIGHT_IO_EXPANDER_INDEX  6

// Forward declaration
typedef struct Launcher2018 Launcher2018;

/** Encapsulates all information needed to launch balls */
struct Launcher2018{
    /** To detect if the launcher position */
    IOExpander* ioExpander;
    /** To launch balls */
    Relay* relay;
};

void launch2018(int launcherIndex, bool prepare);

/**
 * The descriptor for the launcher 2018 device.
 */
DeviceDescriptor* getLauncher2018DeviceDescriptor(Launcher2018* launcher2018);

/**
 * Initialize the Launcher 2018 structure.
 * @param launcher2018
 * @param ioExpander
 * @param relay
 */
void initLauncher2018(Launcher2018* launcher2018,
                      IOExpander* ioExpander,
                      Relay* relay);

#endif
