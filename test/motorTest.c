#include "i2cSetup.h"
#include "motor.h"
#include "delay.h"
#include "serial.h"
#include "coders.h"
#include "motorClient.h"

int main(void) {
	initializeI2C();
	initMD22();
	initCoders();
	openSerial(DEFAULT_SERIAL_SPEED);

	
	writeMD22Speeds(0, 0);

	int i;
	char c;
	while (1) {
		for (i=-128; i<127; i++) {
//			writeMD22Speeds(i, i);
			printf("%d", i);
			delaymSec(50);
			handleChar(0);
			loadNextInstruction();
			if (kbhit()) {
		   		// get the byte
	    	    c = getc();
				putc(c);
				if (c=='c') {
					stopMotors();
					delaymSec(1000);
				}
			}
		}
	}
}
