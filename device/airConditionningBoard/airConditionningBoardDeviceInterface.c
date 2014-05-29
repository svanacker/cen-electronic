#include "airConditionningBoardDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* deviceAirConditioningGetName(void) {
    return "AirConditionningBoard";
}

/**
 * @param header the character which is the header
 * @param mode either MODE_INPUT to know the length of the inputBuffer to handle the command of the header
 * @param fillDeviceArgumentList if TRUE, the function will update the argumentList
 * Returns a value >= 0 if the device handle this char, and -1, if it's not handled
 */
int deviceAirConditioningGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
    if (COMMAND_AIR_CONDITIONNING == header) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
                setFunction("Start", 1);
                setArgumentUnsignedHex2(0, "powerState");
            }

            return 2;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
                setFunction("Start", 0);
            }
            return 0;
        }
    }

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceAirConditioningGetName,
    .deviceGetInterface = &deviceAirConditioningGetInterface
};

DeviceInterface* getAirConditioningDeviceInterface() {
    return &deviceInterface;
}