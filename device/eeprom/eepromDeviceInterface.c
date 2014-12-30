#include "eepromDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getEepromDeviceName(void) {
    return "EEPROM";
}

int deviceEepromGetInterface(char header, DeviceInterfaceMode mode, bool fillDeviceArgumentList){
    if (header == COMMAND_READ_DATA_EEPROM ) {
        if (fillDeviceArgumentList) {
            setFunction("Data Read", 1, 1);
            setArgumentUnsignedHex4(0, "SET ADDRESS");
            setResultUnsignedHex2(0, "DATA");
        }
        return commandLengthValueForMode(mode, 4, 2);

    } else if (header == COMMAND_WRITE_DATA_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Date Write", 2, 0);
            setArgumentUnsignedHex4(0, "ADDRESS");
            setArgumentUnsignedHex2(1, "DATA");
        }
        return commandLengthValueForMode(mode, 6, 0);

    } else if (header == COMMAND_READ_BLOC_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Bloc Read", 1, 9);
            setArgumentUnsignedHex4(0, "SET ADDRESS");
            setResultUnsignedHex2(0, "DATA");
            setResultUnsignedHex2(1, "DATA");
            setResultUnsignedHex2(2, "DATA");
            setResultUnsignedHex2(3, "DATA");
            setResultUnsignedHex2(4, "DATA");
            setResultUnsignedHex2(5, "DATA");
            setResultUnsignedHex2(6, "DATA");
            setResultUnsignedHex2(7, "DATA");
            setResultSeparator(8);
        }
        return commandLengthValueForMode(mode, 4, 17);

    } else if (header == COMMAND_WRITE_BLOC_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Bloc Write", 5, 0);
            setArgumentUnsignedHex4(0, "SET ADDRESS");
            setArgumentUnsignedHex2(1, "DATA0");
            setArgumentUnsignedHex2(2, "DATA1");
            setArgumentUnsignedHex2(3, "DATA2");
            setArgumentUnsignedHex2(4, "DATA3");
        }
        return commandLengthValueForMode(mode, 12, 0);

    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = EEPROM_DEVICE_HEADER,
    .deviceGetName = &getEepromDeviceName,
    .deviceGetInterface = &deviceEepromGetInterface
};

DeviceInterface* getEepromDeviceInterface(void) {
    return &deviceInterface;
}
