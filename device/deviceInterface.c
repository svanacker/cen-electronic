#include "deviceInterface.h"

/** Singleton */
static DeviceMethodMetaData deviceMethodMetaData;

/**
* Singleton of DeviceArgumentList
*/
DeviceMethodMetaData* getDeviceMethodMetaData() {
    return &deviceMethodMetaData;
}

void setFunction(char* functionName, int argumentsSize, int resultsSize) {
    deviceMethodMetaData.functionName = functionName;
    deviceMethodMetaData.argumentsSize = argumentsSize;
    deviceMethodMetaData.resultsSize = resultsSize;
}

void setFunctionNoArgumentAndNoResult(char* functionName) {
    deviceMethodMetaData.functionName = functionName;
    deviceMethodMetaData.argumentsSize = 0;
    deviceMethodMetaData.resultsSize = 0;
}

inline int commandLengthValueForMode(int mode, int input, int output) {
    if (mode == DEVICE_MODE_INPUT) {
        return input;
    }
    else if (mode == DEVICE_MODE_OUTPUT) {
        return output;
    }
    return -1;
}


void setArgument(int index, int type, char* name) {
    deviceMethodMetaData.arguments[index].type = type;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentUnsignedChar1(int index, char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_UNSIGNED_CHAR_1;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentSignedHex2(int index, char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_SIGNED_HEX_2;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentUnsignedHex2(int index, char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_UNSIGNED_HEX_2;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentUnsignedHex4(int index, char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_UNSIGNED_HEX_4;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentSeparator(int index) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_SEPARATOR;
    deviceMethodMetaData.arguments[index].name = "-";
}

// RESULT

void setResult(int index, int type, char* name) {
    deviceMethodMetaData.results[index].type = type;
    deviceMethodMetaData.results[index].name = name;
}

void setResultUnsignedChar1(int index, char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_UNSIGNED_CHAR_1;
    deviceMethodMetaData.results[index].name = name;
}

void setResultSignedHex2(int index, char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_SIGNED_HEX_2;
    deviceMethodMetaData.results[index].name = name;
}

void setResultUnsignedHex2(int index, char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_UNSIGNED_HEX_2;
    deviceMethodMetaData.results[index].name = name;
}

void setResultUnsignedHex4(int index, char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_UNSIGNED_HEX_4;
    deviceMethodMetaData.results[index].name = name;
}

void setResultSeparator(int index) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_SEPARATOR;
    deviceMethodMetaData.results[index].name = "-";
}
