#include "distributorDeviceInterface2019.h"

#include <stdbool.h>

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceDistributor2019GetName(void) {
    return "distributor2019";
}

int deviceDistributor2019GetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // DISTRIBUTOR
    // Prepare Take
    if (commandHeader == COMMAND_2019_DISTRIBUTOR_PREPARE_TAKE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Prepare Take Distributor");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // -> Take
    else if (commandHeader == COMMAND_2019_DISTRIBUTOR_TAKE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Take 2 Pucks on Distributor");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // ACCELERATOR
    // -> Fake Init
    else if (commandHeader == COMMAND_2019_DISTRIBUTOR_ACCELERATOR_FAKE_INIT) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Fake Init");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // -> Prepare Drop
    else if (commandHeader == COMMAND_2019_DISTRIBUTOR_ACCELERATOR_PREPARE_DROP) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Prepare Drop");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // -> Fake Move Forward
    else if (commandHeader == COMMAND_2019_DISTRIBUTOR_ACCELERATOR_FAKE_MOVE_FORWARD) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Fake Move Forward");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // -> Drop
    else if (commandHeader == COMMAND_2019_DISTRIBUTOR_ACCELERATOR_DROP) {
        if (fillDeviceArgumentList) {
            setFunction("Accelerator Drop", 1, 0);
            setArgumentUnsignedChar1(0, "First side to release (1=L, 2=R)");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    // -> Complete Sequence
    else if (commandHeader == COMMAND_2019_DISTRIBUTOR_ACCELERATOR_COMPLETE_SEQUENCE) {
        if (fillDeviceArgumentList) {
            setFunction("Accelerator Complete Sequence", 1, 0);
            setArgumentUnsignedChar1(0, "First side to release (1=L, 2=R)");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = DISTRIBUTOR_2019_DEVICE_HEADER,
    .deviceGetName = &deviceDistributor2019GetName,
    .deviceGetInterface = &deviceDistributor2019GetInterface
};

DeviceInterface* getDistributor2019DeviceInterface(void) {
    return &deviceInterface;
}
