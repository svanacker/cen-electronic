#include "../../common/commons.h"

#include "pwmPic.h"

#ifdef PROG_32
	#include <p32xxxx.h>
#else
	#include <p30fxxxx.h>
#endif


void pwmInit() {
    // simple pwm mode without protection
    OC1CONbits.OCM = 0b110;
    OC2CONbits.OCM = 0b110;
    OC3CONbits.OCM = 0b110;
    OC4CONbits.OCM = 0b110;
}
