#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <p32xxxx.h>

#include "../adcutils.h"

#include "../../../common/error/error.h"

// TODO : Remove this Include and see if the warning is important
// #include _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <peripheral/adc10.h>
#include <peripheral/ports.h>

#include <stdbool.h>

#define CONFIG1 (ADC_MODULE_ON | ADC_FORMAT_INTG32 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON)
#define CONFIG2 (ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_5 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF)
#define CONFIG3 (ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_2)
#define CONFIGPORT (ENABLE_AN2_ANA | ENABLE_AN3_ANA | ENABLE_AN4_ANA | ENABLE_AN5_ANA | ENABLE_AN15_ANA)
#define CONFIGSCAN (SKIP_SCAN_AN0 | SKIP_SCAN_AN1 | SKIP_SCAN_AN6 | SKIP_SCAN_AN7 | SKIP_SCAN_AN8 | SKIP_SCAN_AN9 | SKIP_SCAN_AN10 | SKIP_SCAN_AN11 | SKIP_SCAN_AN12 | SKIP_SCAN_AN13 | SKIP_SCAN_AN14 )

static bool adcInitialized = false;

/**
 * @private
 * Initialise the Analog Digital Converter
 * @param CONFIG1 bit-masks first turns the module on, formats the output as 32-bit integers,
 * triggers its conversions automatically, and automatically samples.
 * @param CONFIG2 bit-masks sets the voltage references to Vdd and Vss, disables the offset calculation,
 * enables scanning, specifies how many samples are to be read per interrupt (which
 * should be changed if multiple analog pins are being read?ADC_SAMPLES_PER_INT_x where x is the
 * number of pins to be read), disables the buffer, and disables input sample mode.
 * @param CONFIG3 bit-masks selects which clock to use, and selects the auto-sample time bits.
 * @param CONFIGPORT bit-masks selects which analog pins are enabled. This is similar to setting the AD1PCFG register.
 * @param CONFIGSCAN bit-masks selects which analog pins are to be scanned or skipped.
 */
void _initADC(){
    if (adcInitialized) {
        return;
    }
    adcInitialized = true;
    CloseADC10();       
    SetChanADC10(ADC_CH0_NEG_SAMPLEA_NVREF);
    OpenADC10(CONFIG1, CONFIG2, CONFIG3, CONFIGPORT, CONFIGSCAN);
    EnableADC10();
    // mAD1GetIntFlag() checks the interrupt flag for the AD10.
    // Waits till a conversion is finished so that there's
    // values in the ADC result registers.
    while (!mAD1GetIntFlag() ) {
    
    }
}

int getANX (char channel){
    if (channel <= 0 || channel > getANXCount()) {
        writeError(ADC_BAD_INDEX);
        return 0;
    }
    _initADC();        
    int result = ReadADC10(channel - 1);
    return result;
 }
