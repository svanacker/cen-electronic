#include <p30fxxxx.h>

#include "cenIO.h"

void initIO() {

    // D2 as Input for laser
    TRISDbits.TRISD2 = 1;

    // D3 as Input for match detector
    TRISDbits.TRISD3 = 1;


    // PORTDbits.RD2 = 0;

    // F0 as ouput
    // TRISFbits.TRISF0 = 0;

    // PORTFbits.RF0 = 1;
}
