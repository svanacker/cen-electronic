#include <p30fxxxx.h>

#include "pin.h"

#include "../../common/commons.h"
#include "../../common/error/error.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/outputStream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

void setPinValue(int pinIndex, BOOL pinValue) {
    switch (pinIndex) {
            // PORT B
        case PIN_INDEX_RB0: LATBbits.LATB0 = pinValue;
            break;
        case PIN_INDEX_RB1: LATBbits.LATB1 = pinValue;
            break;
        case PIN_INDEX_RB2: LATBbits.LATB2 = pinValue;
            break;
        case PIN_INDEX_RB3: LATBbits.LATB3 = pinValue;
            break;
        case PIN_INDEX_RB4: LATBbits.LATB4 = pinValue;
            break;
        case PIN_INDEX_RB5: LATBbits.LATB5 = pinValue;
            break;
        case PIN_INDEX_RB6: LATBbits.LATB6 = pinValue;
            break;
        case PIN_INDEX_RB7: LATBbits.LATB7 = pinValue;
            break;
        case PIN_INDEX_RB8: LATBbits.LATB8 = pinValue;
            break;
        case PIN_INDEX_RB9: LATBbits.LATB9 = pinValue;
            break;
        case PIN_INDEX_RB10: LATBbits.LATB10 = pinValue;
            break;
        case PIN_INDEX_RB11: LATBbits.LATB11 = pinValue;
            break;
        case PIN_INDEX_RB12: LATBbits.LATB12 = pinValue;
            break;

            // PORT C
        case PIN_INDEX_RC13: LATCbits.LATC13 = pinValue;
            break;
        case PIN_INDEX_RC14: LATCbits.LATC14 = pinValue;
            break;
        case PIN_INDEX_RC15: LATCbits.LATC15 = pinValue;
            break;

            // PORT D
        case PIN_INDEX_RD0: LATDbits.LATD0 = pinValue;
            break;
        case PIN_INDEX_RD1: LATDbits.LATD1 = pinValue;
            break;
        case PIN_INDEX_RD2: LATDbits.LATD2 = pinValue;
            break;
        case PIN_INDEX_RD3: LATDbits.LATD3 = pinValue;
            break;
        case PIN_INDEX_RD8: LATDbits.LATD8 = pinValue;
            break;
        case PIN_INDEX_RD9: LATDbits.LATD9 = pinValue;
            break;

            // PORT A
        case PIN_INDEX_RA11: LATAbits.LATA11 = pinValue;
            break;

            // PORT F
        case PIN_INDEX_RF0: LATFbits.LATF0 = pinValue;
            break;
        case PIN_INDEX_RF6: LATFbits.LATF6 = pinValue;
            break;

        default:
        {
            writeError(IO_PIN_INDEX_ERROR);
        }
    }

}

BOOL getPinValue(int pinIndex) {
    switch (pinIndex) {
            // PORT B
        case PIN_INDEX_RB0: return PORTBbits.RB0;
        case PIN_INDEX_RB1: return PORTBbits.RB1;
        case PIN_INDEX_RB2: return PORTBbits.RB2;
        case PIN_INDEX_RB3: return PORTBbits.RB3;
        case PIN_INDEX_RB4: return PORTBbits.RB4;
        case PIN_INDEX_RB5: return PORTBbits.RB5;
        case PIN_INDEX_RB6: return PORTBbits.RB6;
        case PIN_INDEX_RB7: return PORTBbits.RB7;
        case PIN_INDEX_RB8: return PORTBbits.RB8;
        case PIN_INDEX_RB9: return PORTBbits.RB9;
        case PIN_INDEX_RB10: return PORTBbits.RB10;
        case PIN_INDEX_RB11: return PORTBbits.RB11;
        case PIN_INDEX_RB12: return PORTBbits.RB12;

            // PORT C
        case PIN_INDEX_RC13: return PORTCbits.RC13;
        case PIN_INDEX_RC14: return PORTCbits.RC14;
        case PIN_INDEX_RC15: return PORTCbits.RC15;

            // PORT D
        case PIN_INDEX_RD0: return PORTDbits.RD0;
        case PIN_INDEX_RD1: return PORTDbits.RD1;
        case PIN_INDEX_RD2: return PORTDbits.RD2;
        case PIN_INDEX_RD3: return PORTDbits.RD3;
        case PIN_INDEX_RD8: return PORTDbits.RD8;
        case PIN_INDEX_RD9: return PORTDbits.RD9;

            // PORT A
        case PIN_INDEX_RA11: return PORTAbits.RA11;

            // PORTF
        case PIN_INDEX_RF0: return PORTFbits.RF0;
        case PIN_INDEX_RF6: return PORTFbits.RF6;
    }
    writeError(IO_PIN_INDEX_ERROR);

    // log the error
    return FALSE;
}

void printAllPinValues(OutputStream* outputStream) {
    int i = 0;
    for (i = PIN_MIN_INDEX; i <= PIN_MAX_INDEX; i++) {
        BOOL value = getPinValue(i);
        appendString(outputStream, "Pin ");
        appendHex2(outputStream, i);
        append(outputStream, '=');
        appendBOOL(outputStream, value);
        println(outputStream);
    }
}

