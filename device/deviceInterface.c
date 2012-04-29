#include "deviceInterface.h"

/** Singleton */
static DeviceArgumentList deviceArgumentList;

/**
* Singleton of DeviceArgumentList
*/
DeviceArgumentList* getDeviceArgumentList() {
	return &deviceArgumentList;
}

void setFunction(char* functionName, int size) {
	deviceArgumentList.functionName = functionName;
	deviceArgumentList.size = size;
}

void setFunctionNoArgument(char* functionName) {
	deviceArgumentList.functionName = functionName;
	deviceArgumentList.size = 0;
}

void setArgument(int index, int type, char* name) {
	deviceArgumentList.args[index].type = type;
	deviceArgumentList.args[index].name = name;
}

void setArgumentUnsignedChar1(int index, char* name) {
	deviceArgumentList.args[index].type = DEVICE_ARG_UNSIGNED_CHAR_1;
	deviceArgumentList.args[index].name = name;
}

void setArgumentSignedHex2(int index, char* name) {
	deviceArgumentList.args[index].type = DEVICE_ARG_SIGNED_HEX_2;
	deviceArgumentList.args[index].name = name;
}

void setArgumentUnsignedHex2(int index, char* name) {
	deviceArgumentList.args[index].type = DEVICE_ARG_UNSIGNED_HEX_2;
	deviceArgumentList.args[index].name = name;
}

void setArgumentUnsignedHex4(int index, char* name) {
	deviceArgumentList.args[index].type = DEVICE_ARG_UNSIGNED_HEX_4;
	deviceArgumentList.args[index].name = name;
}


void setArgumentSeparator(int index) {
	deviceArgumentList.args[index].type = DEVICE_ARG_SEPARATOR;
	deviceArgumentList.args[index].name = "-";
}
