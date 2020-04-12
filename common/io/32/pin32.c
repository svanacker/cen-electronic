#include "../../../common/commons.h"

#define _SUPPRESS_PLIB_WARNING
#include <plib.h>

#include "../pin.h"
#include "pin32.h"

#include "../../../common/error/error.h"

#include "../../../common/io/printWriter.h"
#include "../../../common/io/outputStream.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

void setPinValue32(PinList* pinList, int pinIndex, bool pinValue) {
    switch (pinIndex) {
            // PORT A : only for 100 pin
        case PIN_INDEX_RA0:
            // LATAbits.LATA0 = pinValue;
            break;
        case PIN_INDEX_RA1:
            // LATAbits.LATA1 = pinValue;
            break;
        case PIN_INDEX_RA2:
            // LATAbits.LATA2 = pinValue;
            break;
        case PIN_INDEX_RA3:
            // LATAbits.LATA3 = pinValue;
            break;
        case PIN_INDEX_RA4:
            // LATAbits.LATA4 = pinValue;
            break;
        case PIN_INDEX_RA5:
            // LATAbits.LATA5 = pinValue;
            break;
        case PIN_INDEX_RA6:
            // LATAbits.LATA6 = pinValue;
            break;
        case PIN_INDEX_RA7:
            // LATAbits.LATA7 = pinValue;
            break;
        case PIN_INDEX_RA8:
            // LATAbits.LATA8 = pinValue;
            break;
        case PIN_INDEX_RA9:
            // LATAbits.LATA9 = pinValue;
            break;
        case PIN_INDEX_RA10:
            // LATAbits.LATA10 = pinValue;
            break;
        case PIN_INDEX_RA11:
            // LATAbits.LATA11 = pinValue;
            break;
        case PIN_INDEX_RA12:
            // LATAbits.LATA12 = pinValue;
            break;
        case PIN_INDEX_RA13:
            // LATAbits.LATA13 = pinValue;
            break;
        case PIN_INDEX_RA14:
            // LATAbits.LATA14 = pinValue;
            break;
        case PIN_INDEX_RA15:
            // LATAbits.LATA15 = pinValue;
            break;

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
        case PIN_INDEX_RB13: LATBbits.LATB13 = pinValue;
            break;
        case PIN_INDEX_RB14: LATBbits.LATB14 = pinValue;
            break;
        case PIN_INDEX_RB15: LATBbits.LATB15 = pinValue;
            break;

            // PORT C
            /*
            case PIN_INDEX_RC0: LATCbits.LATC0 = pinValue;
                break;
            case PIN_INDEX_RC1: LATCbits.LATC1 = pinValue;
                break;
            case PIN_INDEX_RC2: LATCbits.LATC2 = pinValue;
                break;
            case PIN_INDEX_RC3: LATCbits.LATC3 = pinValue;
                break;
            case PIN_INDEX_RC4: LATCbits.LATC4 = pinValue;
                break;
            case PIN_INDEX_RC5: LATCbits.LATC5 = pinValue;
                break;
            case PIN_INDEX_RC6: LATCbits.LATC6 = pinValue;
                break;
            case PIN_INDEX_RC7: LATCbits.LATC7 = pinValue;
                break;
            case PIN_INDEX_RC8: LATCbits.LATC8 = pinValue;
                break;
            case PIN_INDEX_RC9: LATCbits.LATC9 = pinValue;
                break;
            case PIN_INDEX_RC10: LATCbits.LATC10 = pinValue;
                break;
            case PIN_INDEX_RC11: LATCbits.LATC11 = pinValue;
                break;
             */
        case PIN_INDEX_RC12: LATCbits.LATC12 = pinValue;
            break;
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
        case PIN_INDEX_RD4: LATDbits.LATD4 = pinValue;
            break;
        case PIN_INDEX_RD5: LATDbits.LATD5 = pinValue;
            break;
        case PIN_INDEX_RD6: LATDbits.LATD6 = pinValue;
            break;
        case PIN_INDEX_RD7: LATDbits.LATD7 = pinValue;
            break;
        case PIN_INDEX_RD8: LATDbits.LATD8 = pinValue;
            break;
        case PIN_INDEX_RD9: LATDbits.LATD9 = pinValue;
            break;
        case PIN_INDEX_RD10: LATDbits.LATD10 = pinValue;
            break;
        case PIN_INDEX_RD11: LATDbits.LATD11 = pinValue;
            break;
            /* For 100 pin bits
            case PIN_INDEX_RD12: LATDbits.LATD12 = pinValue;
                break;
            case PIN_INDEX_RD13: LATDbits.LATD13 = pinValue;
                break;
            case PIN_INDEX_RD14: LATDbits.LATD14 = pinValue;
                break;
            case PIN_INDEX_RD15: LATDbits.LATD15 = pinValue;
                break;
             */

            // PORT E
        case PIN_INDEX_RE0: LATEbits.LATE0 = pinValue;
            break;
        case PIN_INDEX_RE1: LATEbits.LATE1 = pinValue;
            break;
        case PIN_INDEX_RE2: LATEbits.LATE2 = pinValue;
            break;
        case PIN_INDEX_RE3: LATEbits.LATE3 = pinValue;
            break;
        case PIN_INDEX_RE4: LATEbits.LATE4 = pinValue;
            break;
        case PIN_INDEX_RE5: LATEbits.LATE5 = pinValue;
            break;
        case PIN_INDEX_RE6: LATEbits.LATE6 = pinValue;
            break;
        case PIN_INDEX_RE7: LATEbits.LATE7 = pinValue;
            break;
            /** For 100 pin   
            case PIN_INDEX_RE8: LATEbits.LATE8 = pinValue;
                break;
            case PIN_INDEX_RE9: LATEbits.LATE9 = pinValue;
                break;
            case PIN_INDEX_RE10: LATEbits.LATE10 = pinValue;
                break;
             */

            // PORT F
        case PIN_INDEX_RF0: LATFbits.LATF0 = pinValue;
            break;
        case PIN_INDEX_RF1: LATFbits.LATF1 = pinValue;
            break;
            /*
            case PIN_INDEX_RF2: LATFbits.LATF2 = pinValue;
                break;
             */
        case PIN_INDEX_RF3: LATFbits.LATF3 = pinValue;
            break;
        case PIN_INDEX_RF4: LATFbits.LATF4 = pinValue;
            break;
        case PIN_INDEX_RF5: LATFbits.LATF5 = pinValue;
            break;
            /*
            case PIN_INDEX_RF6: LATFbits.LATF6 = pinValue;
                break;
            case PIN_INDEX_RF7: LATFbits.LATF7 = pinValue;
                break;
            case PIN_INDEX_RF8: LATFbits.LATF8 = pinValue;
                break;
             */
        default:
        {
            writeError(IO_PIN_INDEX_ERROR);
        }
    }
}

bool getPinValue32(PinList* pinList, int pinIndex) {
    switch (pinIndex) {
            // PORT A
            /*
            case PIN_INDEX_RA0: return PORTAbits.RA0;
            case PIN_INDEX_RA1: return PORTAbits.RA1;
            case PIN_INDEX_RA2: return PORTAbits.RA2;
            case PIN_INDEX_RA3: return PORTAbits.RA3;
            case PIN_INDEX_RA4: return PORTAbits.RA4;
            case PIN_INDEX_RA5: return PORTAbits.RA5;
            case PIN_INDEX_RA6: return PORTAbits.RA6;
            case PIN_INDEX_RA7: return PORTAbits.RA7;
            case PIN_INDEX_RA8: return PORTAbits.RA8;
            case PIN_INDEX_RA9: return PORTAbits.RA9;
            case PIN_INDEX_RA10: return PORTAbits.RA10;
            case PIN_INDEX_RA11: return PORTAbits.RA11;
            case PIN_INDEX_RA12: return PORTAbits.RA12;
            case PIN_INDEX_RA13: return PORTAbits.RA13;
            case PIN_INDEX_RA14: return PORTAbits.RA14;
            case PIN_INDEX_RA15: return PORTAbits.RA15;
             */

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
        case PIN_INDEX_RB13: return PORTBbits.RB13;
        case PIN_INDEX_RB14: return PORTBbits.RB14;
        case PIN_INDEX_RB15: return PORTBbits.RB15;

            // PORT C
            /*
            case PIN_INDEX_RC0: return PORTCbits.RC0;
            case PIN_INDEX_RC1: return PORTCbits.RC1;
            case PIN_INDEX_RC2: return PORTCbits.RC2;
            case PIN_INDEX_RC3: return PORTCbits.RC3;
            case PIN_INDEX_RC4: return PORTCbits.RC4;
            case PIN_INDEX_RC5: return PORTCbits.RC5;
            case PIN_INDEX_RC6: return PORTCbits.RC6;
            case PIN_INDEX_RC7: return PORTCbits.RC7;
            case PIN_INDEX_RC8: return PORTCbits.RC8;
            case PIN_INDEX_RC9: return PORTCbits.RC9;
            case PIN_INDEX_RC10: return PORTCbits.RC10;
            case PIN_INDEX_RC11: return PORTCbits.RC11;
             */
        case PIN_INDEX_RC12: return PORTCbits.RC12;
        case PIN_INDEX_RC13: return PORTCbits.RC13;
        case PIN_INDEX_RC14: return PORTCbits.RC14;
        case PIN_INDEX_RC15: return PORTCbits.RC15;

            // PORT D
        case PIN_INDEX_RD0: return PORTDbits.RD0;
        case PIN_INDEX_RD1: return PORTDbits.RD1;
        case PIN_INDEX_RD2: return PORTDbits.RD2;
        case PIN_INDEX_RD3: return PORTDbits.RD3;
        case PIN_INDEX_RD4: return PORTDbits.RD4;
        case PIN_INDEX_RD5: return PORTDbits.RD5;
        case PIN_INDEX_RD6: return PORTDbits.RD6;
        case PIN_INDEX_RD7: return PORTDbits.RD7;
        case PIN_INDEX_RD8: return PORTDbits.RD8;
        case PIN_INDEX_RD9: return PORTDbits.RD9;
        case PIN_INDEX_RD10: return PORTDbits.RD10;
        case PIN_INDEX_RD11: return PORTDbits.RD11;
            /*
            case PIN_INDEX_RD12: return PORTDbits.RD12;
            case PIN_INDEX_RD13: return PORTDbits.RD13;
            case PIN_INDEX_RD14: return PORTDbits.RD14;
            case PIN_INDEX_RD15: return PORTDbits.RD15;
             */

            // PORT E
        case PIN_INDEX_RE0: return PORTEbits.RE0;
        case PIN_INDEX_RE1: return PORTEbits.RE1;
        case PIN_INDEX_RE2: return PORTEbits.RE2;
        case PIN_INDEX_RE3: return PORTEbits.RE3;
        case PIN_INDEX_RE4: return PORTEbits.RE4;
        case PIN_INDEX_RE5: return PORTEbits.RE5;
        case PIN_INDEX_RE6: return PORTEbits.RE6;
        case PIN_INDEX_RE7: return PORTEbits.RE7;
            /*
            case PIN_INDEX_RE8: return PORTEbits.RE8;
            case PIN_INDEX_RE9: return PORTEbits.RE9;
            case PIN_INDEX_RE10: return PORTEbits.RE10;
             */
            // PORT F
            /*
            case PIN_INDEX_RF0: return PORTEbits.RF0;
            case PIN_INDEX_RF1: return PORTEbits.RF1;
            case PIN_INDEX_RF2: return PORTEbits.RF2;
            case PIN_INDEX_RF3: return PORTEbits.RF3;
            case PIN_INDEX_RF4: return PORTEbits.RF4;
            case PIN_INDEX_RF5: return PORTEbits.RF5;
            case PIN_INDEX_RF6: return PORTEbits.RF6;
            case PIN_INDEX_RF7: return PORTEbits.RF7;
            case PIN_INDEX_RF8: return PORTEbits.RF8;
             */
    }
    writeError(IO_PIN_INDEX_ERROR);

    // log the error
    return false;
}

bool isPinInput32(PinList* pinList, int pinIndex) {
    switch (pinIndex) {
            // PORT A
            /*
            case PIN_INDEX_RA0: return TRISAbits.TRISA0;
            case PIN_INDEX_RA1: return TRISAbits.TRISA1;
            case PIN_INDEX_RA2: return TRISAbits.TRISA2;
            case PIN_INDEX_RA3: return TRISAbits.TRISA3;
            case PIN_INDEX_RA4: return TRISAbits.TRISA4;
            case PIN_INDEX_RA5: return TRISAbits.TRISA5;
            case PIN_INDEX_RA6: return TRISAbits.TRISA6;
            case PIN_INDEX_RA7: return TRISAbits.TRISA7;
            case PIN_INDEX_RA8: return TRISAbits.TRISA8;
            case PIN_INDEX_RA9: return TRISAbits.TRISA9;
            case PIN_INDEX_RA10: return TRISAbits.TRISA10;
            case PIN_INDEX_RA11: return TRISAbits.TRISA11;
            case PIN_INDEX_RA12: return TRISAbits.TRISA12;
            case PIN_INDEX_RA13: return TRISAbits.TRISA13;
            case PIN_INDEX_RA14: return TRISAbits.TRISA14;
            case PIN_INDEX_RA15: return TRISAbits.TRISA15;
             */

            // PORT B
        case PIN_INDEX_RB0: return TRISBbits.TRISB0;
        case PIN_INDEX_RB1: return TRISBbits.TRISB1;
        case PIN_INDEX_RB2: return TRISBbits.TRISB2;
        case PIN_INDEX_RB3: return TRISBbits.TRISB3;
        case PIN_INDEX_RB4: return TRISBbits.TRISB4;
        case PIN_INDEX_RB5: return TRISBbits.TRISB5;
        case PIN_INDEX_RB6: return TRISBbits.TRISB6;
        case PIN_INDEX_RB7: return TRISBbits.TRISB7;
        case PIN_INDEX_RB8: return TRISBbits.TRISB8;
        case PIN_INDEX_RB9: return TRISBbits.TRISB9;
        case PIN_INDEX_RB10: return TRISBbits.TRISB10;
        case PIN_INDEX_RB11: return TRISBbits.TRISB11;
        case PIN_INDEX_RB12: return TRISBbits.TRISB12;
        case PIN_INDEX_RB13: return TRISBbits.TRISB13;
        case PIN_INDEX_RB14: return TRISBbits.TRISB14;
        case PIN_INDEX_RB15: return TRISBbits.TRISB15;

            // PORT C
            /*
            case PIN_INDEX_RC0: return TRISCbits.TRISC0;
            case PIN_INDEX_RC1: return TRISCbits.TRISC1;
            case PIN_INDEX_RC2: return TRISCbits.TRISC2;
            case PIN_INDEX_RC3: return TRISCbits.TRISC3;
            case PIN_INDEX_RC4: return TRISCbits.TRISC4;
            case PIN_INDEX_RC5: return TRISCbits.TRISC5;
            case PIN_INDEX_RC6: return TRISCbits.TRISC6;
            case PIN_INDEX_RC7: return TRISCbits.TRISC7;
            case PIN_INDEX_RC8: return TRISCbits.TRISC8;
            case PIN_INDEX_RC9: return TRISCbits.TRISC9;
            case PIN_INDEX_RC10: return TRISCbits.TRISC10;
            case PIN_INDEX_RC11: return TRISCbits.TRISC11;
             */
        case PIN_INDEX_RC12: return TRISCbits.TRISC12;
        case PIN_INDEX_RC13: return TRISCbits.TRISC13;
        case PIN_INDEX_RC14: return TRISCbits.TRISC14;
        case PIN_INDEX_RC15: return TRISCbits.TRISC15;

            // PORT D
        case PIN_INDEX_RD0: return TRISDbits.TRISD0;
        case PIN_INDEX_RD1: return TRISDbits.TRISD1;
        case PIN_INDEX_RD2: return TRISDbits.TRISD2;
        case PIN_INDEX_RD3: return TRISDbits.TRISD3;
        case PIN_INDEX_RD4: return TRISDbits.TRISD4;
        case PIN_INDEX_RD5: return TRISDbits.TRISD5;
        case PIN_INDEX_RD6: return TRISDbits.TRISD6;
        case PIN_INDEX_RD7: return TRISDbits.TRISD7;
        case PIN_INDEX_RD8: return TRISDbits.TRISD8;
        case PIN_INDEX_RD9: return TRISDbits.TRISD9;
        case PIN_INDEX_RD10: return TRISDbits.TRISD10;
        case PIN_INDEX_RD11: return TRISDbits.TRISD11;
            /*
            case PIN_INDEX_RD12: return TRISDbits.TRISD12;
            case PIN_INDEX_RD13: return TRISDbits.TRISD13;
            case PIN_INDEX_RD14: return TRISDbits.TRISD14;
            case PIN_INDEX_RD15: return TRISDbits.TRISD15;
             */

            // PORT E
        case PIN_INDEX_RE0: return TRISEbits.TRISE0;
        case PIN_INDEX_RE1: return TRISEbits.TRISE1;
        case PIN_INDEX_RE2: return TRISEbits.TRISE2;
        case PIN_INDEX_RE3: return TRISEbits.TRISE3;
        case PIN_INDEX_RE4: return TRISEbits.TRISE4;
        case PIN_INDEX_RE5: return TRISEbits.TRISE5;
        case PIN_INDEX_RE6: return TRISEbits.TRISE6;
        case PIN_INDEX_RE7: return TRISEbits.TRISE7;
            /*
            case PIN_INDEX_RE8: return TRISEbits.TRISE8;
            case PIN_INDEX_RE9: return TRISEbits.TRISE9;
            case PIN_INDEX_RE10: return TRISEbits.TRISE10;
             */
            // PORT F
            /*
            case PIN_INDEX_RF0: return TRISFbits.TRISF0;
            case PIN_INDEX_RF1: return TRISFbits.TRISF1;
            case PIN_INDEX_RF2: return TRISFbits.TRISF2;
            case PIN_INDEX_RF3: return TRISFbits.TRISF3;
            case PIN_INDEX_RF4: return TRISFbits.TRISF4;
            case PIN_INDEX_RF5: return TRISFbits.TRISF5;
            case PIN_INDEX_RF6: return TRISFbits.TRISF6;
            case PIN_INDEX_RF7: return TRISFbits.TRISF7;
            case PIN_INDEX_RF8: return TRISFbits.TRISF8;
             */
    }
    writeError(IO_PIN_INDEX_ERROR);

    // log the error
    return false;
}

void setPinInput32(PinList* pinList, int pinIndex, bool input) {
    switch (pinIndex) {
            // PORT A : only for 100 pin
        case PIN_INDEX_RA0:
            // TRISAbits.TRISA0 = input;
            break;
        case PIN_INDEX_RA1:
            // TRISAbits.TRISA1 = input;
            break;
        case PIN_INDEX_RA2:
            // TRISAbits.TRISA2 = input;
            break;
        case PIN_INDEX_RA3:
            // TRISAbits.TRISA3 = input;
            break;
        case PIN_INDEX_RA4:
            // TRISAbits.TRISA4 = input;
            break;
        case PIN_INDEX_RA5:
            // TRISAbits.TRISA5 = input;
            break;
        case PIN_INDEX_RA6:
            // TRISAbits.TRISA6 = input;
            break;
        case PIN_INDEX_RA7:
            // TRISAbits.TRISA7 = input;
            break;
        case PIN_INDEX_RA8:
            // TRISAbits.TRISA8 = input;
            break;
        case PIN_INDEX_RA9:
            // TRISAbits.TRISA9 = input;
            break;
        case PIN_INDEX_RA10:
            // TRISAbits.TRISA10 = input;
            break;
        case PIN_INDEX_RA11:
            // TRISAbits.TRISA11 = input;
            break;
        case PIN_INDEX_RA12:
            // TRISAbits.TRISA12 = input;
            break;
        case PIN_INDEX_RA13:
            // TRISAbits.TRISA13 = input;
            break;
        case PIN_INDEX_RA14:
            // TRISAbits.TRISA14 = input;
            break;
        case PIN_INDEX_RA15:
            // TRISAbits.TRISA15 = input;
            break;

            // PORT B
        case PIN_INDEX_RB0: TRISBbits.TRISB0 = input;
            break;
        case PIN_INDEX_RB1: TRISBbits.TRISB1 = input;
            break;
        case PIN_INDEX_RB2: TRISBbits.TRISB2 = input;
            break;
        case PIN_INDEX_RB3: TRISBbits.TRISB3 = input;
            break;
        case PIN_INDEX_RB4: TRISBbits.TRISB4 = input;
            break;
        case PIN_INDEX_RB5: TRISBbits.TRISB5 = input;
            break;
        case PIN_INDEX_RB6: TRISBbits.TRISB6 = input;
            break;
        case PIN_INDEX_RB7: TRISBbits.TRISB7 = input;
            break;
        case PIN_INDEX_RB8: TRISBbits.TRISB8 = input;
            break;
        case PIN_INDEX_RB9: TRISBbits.TRISB9 = input;
            break;
        case PIN_INDEX_RB10: TRISBbits.TRISB10 = input;
            break;
        case PIN_INDEX_RB11: TRISBbits.TRISB11 = input;
            break;
        case PIN_INDEX_RB12: TRISBbits.TRISB12 = input;
            break;
        case PIN_INDEX_RB13: TRISBbits.TRISB13 = input;
            break;
        case PIN_INDEX_RB14: TRISBbits.TRISB14 = input;
            break;
        case PIN_INDEX_RB15: TRISBbits.TRISB15 = input;
            break;

            // PORT C
            /*
            case PIN_INDEX_RC0: TRISCbits.TRISC0 = input;
                break;
            case PIN_INDEX_RC1: TRISCbits.TRISC1 = input;
                break;
            case PIN_INDEX_RC2: TRISCbits.TRISC2 = input;
                break;
            case PIN_INDEX_RC3: TRISCbits.TRISC3 = input;
                break;
            case PIN_INDEX_RC4: TRISCbits.TRISC4 = input;
                break;
            case PIN_INDEX_RC5: TRISCbits.TRISC5 = input;
                break;
            case PIN_INDEX_RC6: TRISCbits.TRISC6 = input;
                break;
            case PIN_INDEX_RC7: TRISCbits.TRISC7 = input;
                break;
            case PIN_INDEX_RC8: TRISCbits.TRISC8 = input;
                break;
            case PIN_INDEX_RC9: TRISCbits.TRISC9 = input;
                break;
            case PIN_INDEX_RC10: TRISCbits.TRISC10 = input;
                break;
            case PIN_INDEX_RC11: TRISCbits.TRISC11 = input;
                break;
             */
        case PIN_INDEX_RC12: TRISCbits.TRISC12 = input;
            break;
        case PIN_INDEX_RC13: TRISCbits.TRISC13 = input;
            break;
        case PIN_INDEX_RC14: TRISCbits.TRISC14 = input;
            break;
        case PIN_INDEX_RC15: TRISCbits.TRISC15 = input;
            break;

            // PORT D
        case PIN_INDEX_RD0: TRISDbits.TRISD0 = input;
            break;
        case PIN_INDEX_RD1: TRISDbits.TRISD1 = input;
            break;
        case PIN_INDEX_RD2: TRISDbits.TRISD2 = input;
            break;
        case PIN_INDEX_RD3: TRISDbits.TRISD3 = input;
            break;
        case PIN_INDEX_RD4: TRISDbits.TRISD4 = input;
            break;
        case PIN_INDEX_RD5: TRISDbits.TRISD5 = input;
            break;
        case PIN_INDEX_RD6: TRISDbits.TRISD6 = input;
            break;
        case PIN_INDEX_RD7: TRISDbits.TRISD7 = input;
            break;
        case PIN_INDEX_RD8: TRISDbits.TRISD8 = input;
            break;
        case PIN_INDEX_RD9: TRISDbits.TRISD9 = input;
            break;
        case PIN_INDEX_RD10: TRISDbits.TRISD10 = input;
            break;
        case PIN_INDEX_RD11: TRISDbits.TRISD11 = input;
            break;
            /* For 100 pin bits
            case PIN_INDEX_RD12: TRISDbits.TRISD12 = input;
                break;
            case PIN_INDEX_RD13: TRISDbits.TRISD13 = input;
                break;
            case PIN_INDEX_RD14: TRISDbits.TRISD14 = input;
                break;
            case PIN_INDEX_RD15: TRISDbits.TRISD15 = input;
                break;
             */

            // PORT E
        case PIN_INDEX_RE0: TRISEbits.TRISE0 = input;
            break;
        case PIN_INDEX_RE1: TRISEbits.TRISE1 = input;
            break;
        case PIN_INDEX_RE2: TRISEbits.TRISE2 = input;
            break;
        case PIN_INDEX_RE3: TRISEbits.TRISE3 = input;
            break;
        case PIN_INDEX_RE4: TRISEbits.TRISE4 = input;
            break;
        case PIN_INDEX_RE5: TRISEbits.TRISE5 = input;
            break;
        case PIN_INDEX_RE6: TRISEbits.TRISE6 = input;
            break;
        case PIN_INDEX_RE7: TRISEbits.TRISE7 = input;
            break;
            /** For 100 pin   
            case PIN_INDEX_RE8: TRISEbits.TRISE8 = input;
                break;
            case PIN_INDEX_RE9: TRISEbits.TRISE9 = input;
                break;
            case PIN_INDEX_RE10: TRISEbits.TRISE10 = input;
                break;
             */

            // PORT F
        case PIN_INDEX_RF0: TRISFbits.TRISF0 = input;
            break;
        case PIN_INDEX_RF1: TRISFbits.TRISF1 = input;
            break;
            /*
            case PIN_INDEX_RF2: TRISFbits.TRISF2 = input;
                break;
             */
        case PIN_INDEX_RF3: TRISFbits.TRISF3 = input;
            break;
        case PIN_INDEX_RF4: TRISFbits.TRISF4 = input;
            break;
        case PIN_INDEX_RF5: TRISFbits.TRISF5 = input;
            break;
            /*
            case PIN_INDEX_RF6: TRISFbits.TRISF6 = input;
                break;
            case PIN_INDEX_RF7: TRISFbits.TRISF7 = input;
                break;
            case PIN_INDEX_RF8: TRISFbits.TRISF8 = input;
                break;
             */
        default:
        {
            writeError(IO_PIN_INDEX_ERROR);
        }
    }
}


bool isPinValid32(PinList* pinList, int pinIndex) {
    // Port A : disabled
    if (pinIndex >= PIN_INDEX_RA0 && pinIndex <= PIN_INDEX_RA15) {
        return false;
    }
    
    // Port B : OK
    if (pinIndex >= PIN_INDEX_RB0 && pinIndex <= PIN_INDEX_RB15) {
        return true;
    }
    // Port C : disabled before RC12
    if (pinIndex >= PIN_INDEX_RC12 && pinIndex <= PIN_INDEX_RC15) {
        return true;
    }
    
    // Port D : disabled from RD12
    if (pinIndex >= PIN_INDEX_RD0 && pinIndex <= PIN_INDEX_RD11) {
        return true;
    }

    // Port E : disabled from RE8
    if (pinIndex >= PIN_INDEX_RE0 && pinIndex <= PIN_INDEX_RE7) {
        return true;
    }

    // Port F : disabled
    if (pinIndex >= PIN_INDEX_RF0 && pinIndex <= PIN_INDEX_RF8) {
        return false;
    }
    
    // In all other cases
    return false;
}


void initPinList32(PinList* pinList) {
    initPinList(pinList, &isPinValid32, &isPinInput32, &setPinInput32, &getPinValue32, &setPinValue32, NULL);
}