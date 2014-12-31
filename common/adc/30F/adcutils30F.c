#include <p30Fxxxx.h>
#include <libpic30.h>
#include <adc12.h>

#include "../adcutils.h"

#include "../../../common/delay/cenDelay.h"

/**
 * 30F Implementation of ANX conversion.
 */
int getANX (char channel) {
    ADCON1bits.ADON = 0; //Stop ADC
    // ADCON1 Register
    ADCON1bits.SSRC = 0; //manual convert option
    ADCON1bits.ASAM = 0; //manual sample
    ADCON1bits.FORM = 0b00; //integer
    // ADCON2 Register
    ADCON2bits.VCFG = 0; //ADD - AGND
    // ADCON3 Register
    ADCON3bits.SAMC = 1;            // ????
    ADCON3bits.ADCS = 0b101010;     // ????

    // ADCHS Register
    // Set up A/D Channel Select Register to convert ANX on Mux A input
    // of CH0 and CH1 S/H amplifiers
    ADCHS = channel;

    // ADCSSL Register
    // Channel Scanning is disabled. All bits left to their default state
    ADCSSL = 0x0000;

    // ADPCFG Register
    // Set up channels ANX as analog input and configure rest as digital
    // Recall that we configured all A/D pins as digital when code execution
    // entered main() out of reset
    unsigned int configport = 1 << channel;
    configport = configport ^ 0b1111111111111111; //inverse configport
    
    ADPCFG = configport;
    // DAC ON
    ADCON1bits.ADON = 1;  
    // start acquisition
    ADCON1bits.SAMP =  1; 

    // Delay of 0.1 ms
    delay100us(1);
    // stop acquisition
    ADCON1bits.SAMP =  0; 
    // wait end of conversion
    while(!ADCON1bits.DONE){
    
    } 
          
    unsigned int result;
    result = ADCBUF0;

    // stop ADC
    ADCON1bits.ADON = 0;    
    
    return result;
}
