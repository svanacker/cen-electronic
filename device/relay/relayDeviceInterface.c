#include "relayDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* deviceRelayGetName() {
	return "relay";
}

unsigned int deviceRelayGetSotwareRevision() {
	return 1;
}

int deviceRelayGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
	if (mode == DEVICE_MODE_INPUT) {
		if (header == COMMAND_RELAY) {
			if (fillDeviceArgumentList) {
				setFunction("setRelay", 2);
				setArgumentUnsignedHex2(0, "RelayIdx");
				setArgumentUnsignedChar1(1, "Value");
			}
			return 3;
		}
	}
	else if (mode == DEVICE_MODE_OUTPUT){
		if (header == COMMAND_RELAY) {
			if (fillDeviceArgumentList) {
				setFunctionNoArgument("setRelay");
			}
			return 0;
		}
	}
	return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
	.deviceGetName = &deviceRelayGetName,
	.deviceGetSoftwareRevision = &deviceRelayGetSotwareRevision,
	.deviceGetInterface = &deviceRelayGetInterface
};

DeviceInterface* getRelayDeviceInterface() {
	return &deviceInterface;
}
