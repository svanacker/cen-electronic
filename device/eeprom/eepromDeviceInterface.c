#include "eepromDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getEepromDeviceName (){
    return "EEPROM";
}

int deviceEepromGetInterface(char header, int mode, bool fillDeviceArgumentList){
    if (header == COMMAND_READ_DATA_EEPROM ) {
        if (fillDeviceArgumentList) {
            setFunction("Data Read", 0, 1);
            setResultUnsignedHex2(0, "DATA");
        }
        return commandLengthValueForMode(mode, 0, 2);
    } else if (header == COMMAND_WRITE_DATA_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Date Write", 2, 0);

        }
        return commandLengthValueForMode(mode, 6, 0);
    } else if (header == COMMAND_READ_BUFFER_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Buffer Read", 0, 1);
            setResultUnsignedHex2(0, "BUFFER");
        }
        return commandLengthValueForMode(mode, 0, 2);
    } else if (header == COMMAND_READ_BUFFER_EEPROM) {
        if (fillDeviceArgumentList) {
            setFunction("Buffer Write", 32, 0);

        }
        return commandLengthValueForMode(mode, 6, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = EEPROM_DEVICE_HEADER,
    .deviceGetName = &getEepromDeviceName,
    .deviceGetInterface = &deviceEepromGetInterface
};

DeviceInterface* getEepromDeviceInterface() {
    return &deviceInterface;
}
