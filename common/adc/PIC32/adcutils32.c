#include <p32xxxx.h>
#include <peripheral/adc10.h>
#include <peripheral/ports.h>

//                Turn module on | ouput format      | trigger     | enable autosample
#define PARAM1  ADC_MODULE_ON | ADC_FORMAT_INTG16 | ADC_CLK_TMR | ADC_AUTO_SAMPLING_ON
//                 ADC ref external   | disable offset test    | scan mode   | perform 16 samples     | dual buffers    | use alternate mode
#define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_16 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF
//             use ADC internal clock | set sample time
#define PARAM3  ADC_CONV_CLK_SYSTEM | ADC_SAMPLE_TIME_13 | ADC_CONV_CLK_16Tcy    //ADC_SAMPLE_xx     conversion period in multiples of TAD
                                                                                //ADC_CONV_CLK_xx     ADC sample clock rate
                                                                                 //TAD =             TPB * 2 * (ADCS<7:0>+1)
                                                                                 //xx_16Tcy =         ADCS<7:0> = 0x001F (see adc10.h)
// set all ANx as analog inputs
#define PARAM4    ENABLE_ALL_ANA
// do not assign channels to scan
#define PARAM5  0
 unsigned long int full_scan;
 unsigned long int i = 0;

int getANX (char channel){
    // configure and enable the ADC
    CloseADC10();    // ensure the ADC is off before setting the configuration
    mPORTBSetPinsAnalogIn(BIT_2 );       //Set PortB pins as Analog Inputs, AN2 
    SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF ); // Select VR- for MUX A negative input
    OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 ); // configure ADC using the parameters defined above
    EnableADC10(); // Enable the ADC

             full_scan = ReadADC10(channel);

      mAD1ClearIntFlag();        // clear ADC interrupt flag
      return(full_scan);
 }
