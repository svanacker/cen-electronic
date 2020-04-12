#include "../../common/commons.h"

#include "pin.h"

#include "../../common/error/error.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/outputStream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

char* getPinName(PinList* pinList, int pinIndex) {
    switch (pinIndex) {
            // PORT A
        case PIN_INDEX_RA0: return "A0";
        case PIN_INDEX_RA1: return "A1";
        case PIN_INDEX_RA2: return "A2";
        case PIN_INDEX_RA3: return "A3";
        case PIN_INDEX_RA4: return "A4";
        case PIN_INDEX_RA5: return "A5";
        case PIN_INDEX_RA6: return "A6";
        case PIN_INDEX_RA7: return "A7";
        case PIN_INDEX_RA8: return "A8";
        case PIN_INDEX_RA9: return "A9";
        case PIN_INDEX_RA10: return "A10";
        case PIN_INDEX_RA11: return "A11";
        case PIN_INDEX_RA12: return "A12";
        case PIN_INDEX_RA13: return "A13";
        case PIN_INDEX_RA14: return "A14";
        case PIN_INDEX_RA15: return "A15";

            // PORT B
        case PIN_INDEX_RB0: return "B0";
        case PIN_INDEX_RB1: return "B1";
        case PIN_INDEX_RB2: return "B2";
        case PIN_INDEX_RB3: return "B3";
        case PIN_INDEX_RB4: return "B4";
        case PIN_INDEX_RB5: return "B5";
        case PIN_INDEX_RB6: return "B6";
        case PIN_INDEX_RB7: return "B7";
        case PIN_INDEX_RB8: return "B8";
        case PIN_INDEX_RB9: return "B9";
        case PIN_INDEX_RB10: return "B10";
        case PIN_INDEX_RB11: return "B11";
        case PIN_INDEX_RB12: return "B12";
        case PIN_INDEX_RB13: return "B13";
        case PIN_INDEX_RB14: return "B14";
        case PIN_INDEX_RB15: return "B15";

            // PORT C
        case PIN_INDEX_RC0: return "C0";
        case PIN_INDEX_RC1: return "C1";
        case PIN_INDEX_RC2: return "C2";
        case PIN_INDEX_RC3: return "C3";
        case PIN_INDEX_RC4: return "C4";
        case PIN_INDEX_RC5: return "C5";
        case PIN_INDEX_RC6: return "C6";
        case PIN_INDEX_RC7: return "C7";
        case PIN_INDEX_RC8: return "C8";
        case PIN_INDEX_RC9: return "C9";
        case PIN_INDEX_RC10: return "C10";
        case PIN_INDEX_RC11: return "C11";
        case PIN_INDEX_RC12: return "C12";
        case PIN_INDEX_RC13: return "C13";
        case PIN_INDEX_RC14: return "C14";
        case PIN_INDEX_RC15: return "C15";

            // PORT D
        case PIN_INDEX_RD0: return "D0";
        case PIN_INDEX_RD1: return "D1";
        case PIN_INDEX_RD2: return "D2";
        case PIN_INDEX_RD3: return "D3";
        case PIN_INDEX_RD4: return "D4";
        case PIN_INDEX_RD5: return "D5";
        case PIN_INDEX_RD6: return "D6";
        case PIN_INDEX_RD7: return "D7";
        case PIN_INDEX_RD8: return "D8";
        case PIN_INDEX_RD9: return "D9";
        case PIN_INDEX_RD10: return "D10";
        case PIN_INDEX_RD11: return "D11";
        case PIN_INDEX_RD12: return "D12";
        case PIN_INDEX_RD13: return "D13";
        case PIN_INDEX_RD14: return "D14";
        case PIN_INDEX_RD15: return "D15";

            // PORT E
        case PIN_INDEX_RE0: return "E0";
        case PIN_INDEX_RE1: return "E1";
        case PIN_INDEX_RE2: return "E2";
        case PIN_INDEX_RE3: return "E3";
        case PIN_INDEX_RE4: return "E4";
        case PIN_INDEX_RE5: return "E5";
        case PIN_INDEX_RE6: return "E6";
        case PIN_INDEX_RE7: return "E7";
        case PIN_INDEX_RE8: return "E8";
        case PIN_INDEX_RE9: return "E9";
        case PIN_INDEX_RE10: return "E10";

            // PORT F
        case PIN_INDEX_RF0: return "F0";
        case PIN_INDEX_RF1: return "F1";
        case PIN_INDEX_RF2: return "F2";
        case PIN_INDEX_RF3: return "F3";
        case PIN_INDEX_RF4: return "F4";
        case PIN_INDEX_RF5: return "F5";
        case PIN_INDEX_RF6: return "F6";
        case PIN_INDEX_RF7: return "F7";
        case PIN_INDEX_RF8: return "F8";
    }
    writeError(IO_PIN_INDEX_ERROR);

    // log the error
    return false;
}

void initPinList(PinList* pinList, 
        IsPinValidFunction* isPinValidFunction,
        IsPinInputFunction* isPinInputFunction,
        SetPinInputFunction* setPinInputFunction,
        GetPinValueFunction* getPinValueFunction,
        SetPinValueFunction* setPinValueFunction,
        int* object) {
    pinList->isPinValidFunction = isPinValidFunction;
    pinList->isPinInputFunction = isPinInputFunction;
    pinList->setPinInputFunction = setPinInputFunction;
    pinList->getPinValueFunction = getPinValueFunction;
    pinList->setPinValueFunction = setPinValueFunction;
    pinList->object = object;
}

bool getPinValue(PinList* pinList, int pinIndex) {
    if (pinList == NULL) {
        writeError(IO_PIN_LIST_NULL);
        return false;
    }
    if (pinList->getPinValueFunction == NULL) {
        writeError(IO_PIN_LIST_GET_FUNCTION_NULL);
        return false;
    }
    return pinList->getPinValueFunction(pinList, pinIndex);
}

void setPinValue(PinList* pinList, int pinIndex, bool pinValue) {
    if (pinList == NULL) {
        writeError(IO_PIN_LIST_NULL);
        return;
    }
    if (pinList->setPinValueFunction == NULL) {
        writeError(IO_PIN_LIST_SET_FUNCTION_NULL);
        return;
    }
    pinList->setPinValueFunction(pinList, pinIndex, pinValue);
}

bool isPinInput(PinList* pinList, int pinIndex) {
    if (pinList == NULL) {
        writeError(IO_PIN_LIST_NULL);
        return false;
    }
    if (pinList->isPinInputFunction == NULL) {
        writeError(IO_PIN_LIST_IS_INPUT_FUNCTION_NULL);
        return false;
    }
    return pinList->isPinInputFunction(pinList, pinIndex);
}

void setPinInput(PinList* pinList, int pinIndex, bool input) {
    if (pinList == NULL) {
        writeError(IO_PIN_LIST_NULL);
        return;
    }
    if (pinList->setPinInputFunction == NULL) {
        writeError(IO_PIN_LIST_SET_INPUT_FUNCTION_NULL);
        return;
    }
    pinList->setPinInputFunction(pinList, pinIndex, input);
}

bool isPinValid(PinList* pinList, int pinIndex) {
    if (pinList == NULL) {
        writeError(IO_PIN_LIST_NULL);
        return false;
    }
    if (pinList->isPinInputFunction == NULL) {
        writeError(IO_PIN_LIST_IS_INPUT_FUNCTION_NULL);
        return false;
    }
    return pinList->isPinValidFunction(pinList, pinIndex);
}
