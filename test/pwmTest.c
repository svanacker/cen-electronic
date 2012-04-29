#include "pwmTest.h"

#include "../common/delay/delay30F.h"
#include "../common/pwm/pwmPic.h"

void pwmTest (void){

	pwm1(1000);
	pwm2(1200);
	pwm3(700);
	pwm4(1600);
	delaymSec(1000);
	pwm1(2000);
	pwm2(2200);
	pwm3(1700);
	pwm4(2600);
	delaymSec(1000);
}
