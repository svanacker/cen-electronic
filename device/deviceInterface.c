#include "deviceInterface.h"

/** Singleton */
static DeviceMethodMetaData deviceMethodMetaData;

DeviceMethodMetaData* getDeviceMethodMetaData(void) {
    return &deviceMethodMetaData;
}

void setFunction(const char* functionName, int argumentsSize, int resultsSize) {
    deviceMethodMetaData.functionName = functionName;
    deviceMethodMetaData.argumentsSize = argumentsSize;
    deviceMethodMetaData.resultsSize = resultsSize;
}

void setFunctionNoArgumentAndNoResult(const char* functionName) {
    deviceMethodMetaData.functionName = functionName;
    deviceMethodMetaData.argumentsSize = 0;
    deviceMethodMetaData.resultsSize = 0;
}

void setNotification(const char* notificationName, int notificationArguments) {
   deviceMethodMetaData.functionName = notificationName;
   deviceMethodMetaData.argumentsSize = notificationArguments;
   deviceMethodMetaData.resultsSize = 0;
}

int getLengthOfType(int parameterType) {
    switch (parameterType) {
        case DEVICE_ARG_SEPARATOR : return 1;
        case DEVICE_ARG_UNSIGNED_CHAR_1 : return 1;
        case DEVICE_ARG_UNSIGNED_CHAR_2 : return 2;
        case DEVICE_ARG_SIGNED_HEX_2 : return 2;
        case DEVICE_ARG_UNSIGNED_HEX_2: return 2;
        case DEVICE_ARG_UNSIGNED_HEX_3 : return 3;
        case DEVICE_ARG_UNSIGNED_HEX_4 : return 4;
        case DEVICE_ARG_SIGNED_HEX_4 : return 4;
        case DEVICE_ARG_UNSIGNED_HEX_5 : return 5;
        case DEVICE_ARG_SIGNED_HEX_5 : return 5;
        case DEVICE_ARG_UNSIGNED_HEX_6 : return 6;
        case DEVICE_ARG_SIGNED_HEX_6 : return 6;
        case DEVICE_ARG_UNSIGNED_HEX_8 : return 8;
        case DEVICE_ARG_SIGNED_HEX_8 : return 8;
        case DEVICE_ARG_FIXED_CHAR_ARRAY: return 8;
        case DEVICE_ARG_UNSIGNED_HEX_9 : return 9;
        case DEVICE_ARG_UNSIGNED_HEX_10 : return 10;
        case DEVICE_ARG_UNSIGNED_HEX_12 : return 12;
        case DEVICE_ARG_UNSIGNED_FLOAT_HEX_2: return 2;
        case DEVICE_ARG_UNSIGNED_FLOAT_HEX_4: return 4;
        case DEVICE_ARG_UNSIGNED_FLOAT_HEX_6: return 6;
    }
    return -1;
}

int commandLengthValueForMode(DeviceInterfaceMode mode, int input, int output) {
    if (mode == DEVICE_MODE_INPUT) {
        return input;
    }
    else if (mode == DEVICE_MODE_OUTPUT) {
        return output;
    }
    return DEVICE_HEADER_NOT_HANDLED;
}


void setArgument(int index, int type, const char* name) {
    deviceMethodMetaData.arguments[index].type = type;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentUnsignedChar1(int index, const char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_UNSIGNED_CHAR_1;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentSignedHex2(int index, const char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_SIGNED_HEX_2;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentUnsignedHex2(int index, const char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_UNSIGNED_HEX_2;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentUnsignedHex4(int index, const char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_UNSIGNED_HEX_4;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentSignedHex4(int index, const char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_SIGNED_HEX_4;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentUnsignedHex6(int index, const char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_UNSIGNED_HEX_6;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentUnsignedHex8(int index, const char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_UNSIGNED_HEX_8;
    deviceMethodMetaData.arguments[index].name = name;
}


// Float

void setArgumentFloatHex2(int index, const char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_UNSIGNED_FLOAT_HEX_2;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentFloatHex4(int index, const char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_UNSIGNED_FLOAT_HEX_4;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentFloatHex6(int index, const char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_UNSIGNED_FLOAT_HEX_6;
    deviceMethodMetaData.arguments[index].name = name;
}


// Fixed Char Array

void setArgumentFixedCharArray(int index, const char* name) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_FIXED_CHAR_ARRAY;
    deviceMethodMetaData.arguments[index].name = name;
}

void setArgumentSeparator(int index) {
    deviceMethodMetaData.arguments[index].type = DEVICE_ARG_SEPARATOR;
    deviceMethodMetaData.arguments[index].name = "-";
}

// RESULT

void setResult(int index, int type, const char* name) {
    deviceMethodMetaData.results[index].type = type;
    deviceMethodMetaData.results[index].name = name;
}

void setResultUnsignedChar1(int index, const char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_UNSIGNED_CHAR_1;
    deviceMethodMetaData.results[index].name = name;
}

void setResultSignedHex2(int index, const char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_SIGNED_HEX_2;
    deviceMethodMetaData.results[index].name = name;
}

void setResultUnsignedHex2(int index, const char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_UNSIGNED_HEX_2;
    deviceMethodMetaData.results[index].name = name;
}

void setResultUnsignedHex4(int index, const char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_UNSIGNED_HEX_4;
    deviceMethodMetaData.results[index].name = name;
}

void setResultUnsignedHex6(int index, const char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_UNSIGNED_HEX_6;
    deviceMethodMetaData.results[index].name = name;
}

void setResultUnsignedHex8(int index, const char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_UNSIGNED_HEX_8;
    deviceMethodMetaData.results[index].name = name;
}

// Fixed Array

void setResultFixedCharArray(int index, const char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_FIXED_CHAR_ARRAY;
    deviceMethodMetaData.results[index].name = name;
}

// Float

void setResultFloatHex2(int index, const char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_UNSIGNED_FLOAT_HEX_2;
    deviceMethodMetaData.results[index].name = name;
}

void setResultFloatHex4(int index, const char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_UNSIGNED_FLOAT_HEX_4;
    deviceMethodMetaData.results[index].name = name;
}

void setResultFloatHex6(int index, const char* name) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_UNSIGNED_FLOAT_HEX_6;
    deviceMethodMetaData.results[index].name = name;
}

void setResultSeparator(int index) {
    deviceMethodMetaData.results[index].type = DEVICE_ARG_SEPARATOR;
    deviceMethodMetaData.results[index].name = "-";
}
