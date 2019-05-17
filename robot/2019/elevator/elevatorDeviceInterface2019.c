#include "elevatorDeviceInterface2019.h"

#include <stdbool.h>

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceElevator2019GetName(void) {
    return "elevator2019";
}

int deviceElevator2019GetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // ELEVATOR
    if (commandHeader == COMMAND_2019_ELEVATOR_VALUE) {
        if (fillDeviceArgumentList) {
            setFunction("Elevator Up/Down", 1, 0);
            setArgumentUnsignedHex4(0, "Servo Pos value");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    else if (commandHeader == COMMAND_2019_ELEVATOR_BOTTOM) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("ELEVATOR Bottom");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_2019_ELEVATOR_DISTRIBUTOR_SCAN) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("ELEVATOR Distributor Scan");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_2019_ELEVATOR_LEFT) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("ELEVATOR Left");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_2019_ELEVATOR_MIDDLE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("ELEVATOR Middle");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_2019_ELEVATOR_RIGHT) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("ELEVATOR Right");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_2019_ELEVATOR_GOLDENIUM_POSITION) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("ELEVATOR Goldenium Pos.");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_2019_ELEVATOR_INIT_POSITION) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("ELEVATOR Init Position");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_2019_ELEVATOR_ACCELERATOR_SECOND_DROP) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("ELEVATOR ACC SECOND DROP");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_2019_ELEVATOR_UP) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("ELEVATOR Up");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = ELEVATOR_2019_DEVICE_HEADER,
    .deviceGetName = &deviceElevator2019GetName,
    .deviceGetInterface = &deviceElevator2019GetInterface
};

DeviceInterface* getElevator2019DeviceInterface(void) {
    return &deviceInterface;
}
