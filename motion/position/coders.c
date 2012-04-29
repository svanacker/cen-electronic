#include <p30fxxxx.h>
#include <libpic30.h>

#include "coders.h"

#include "../../common/commons.h"
#include "../../common/delay/delay30F.h"
#include "../../common/math/cenMath.h"
#include "../../device/device.h"

#define CODERS_MASKA_1 0b00000001
#define CODERS_MASKB_1 0b00000010
#define CODERS_MASKZ_1 0b00000100
#define CODERS_MASKA_2 0b00001000
#define CODERS_MASKB_2 0b00010000
#define CODERS_MASKZ_2 0b00100000

#define CODERS_RESOLUTION 2000
#define CODERS_ERROR 2

static unsigned char CODERS_MASKA[MAX_CODERS];
static unsigned char CODERS_MASKB[MAX_CODERS];
static unsigned char CODERS_MASKZ[MAX_CODERS];

#define CODERS_TRIS TRISB
#define CODERS_PORT	PORTB

// the current value of the input canal for the two coder
static volatile unsigned char canal;								
// the saved value of the input canal for the two coder
static volatile unsigned char oldCanal;
							
static volatile signed long codersPositions[MAX_CODERS];
static volatile signed long initialPositions[MAX_CODERS];
static volatile signed long lastZPositions[MAX_CODERS];
static volatile unsigned char codersErrorCounts[MAX_CODERS];
static volatile int checkCodersFlags[MAX_CODERS];
static volatile int codersZCounts[MAX_CODERS];
static volatile int codersErrorValues[MAX_CODERS];

void updateCoders(void) {
	oldCanal = canal;
	// save the PORT to avoid the changement of PORT during read operation
	canal = CODERS_PORT;

	int i;
	for (i=0; i<MAX_CODERS; i++) {
		// Codeur0
		if ((canal & CODERS_MASKA[i]) > 0) {
			if ((oldCanal & CODERS_MASKA[i]) == 0) {
				// coderPosition++;
				if ((canal & CODERS_MASKB[i]) == 0) {				// CASE (1)
					codersPositions[i]++;
				}
				else {									// CASE (6)
					codersPositions[i]--;
				}
			}
		}
		else {
			if ((oldCanal & CODERS_MASKA[i]) > 0) {
				if ((canal & CODERS_MASKB[i]) == 0) {				// CASE (8)
					codersPositions[i]--;
				}
				else {									// CASE (3)
					codersPositions[i]++;
				}
			}
		}
		if ((canal & CODERS_MASKB[i]) > 0) {
			if ((oldCanal & CODERS_MASKB[i]) == 0) {
				if ((canal & CODERS_MASKA[i]) == 0) {				// CASE (5)
					codersPositions[i]--;
				}
				else {									// CASE (2)
					codersPositions[i]++;
				}
			}
		}
		else {
			if ((oldCanal & CODERS_MASKB[i]) > 0) {
				if ((canal & CODERS_MASKA[i]) == 0) {				// CASE (4)
					codersPositions[i]++;
				}		
				else {									// CASE (7)
					codersPositions[i]--;
				}
			}
		}

		// Test du passage de 0 à 1 du bit Z
		if (((oldCanal & CODERS_MASKZ[i]) == 0 ) && ((canal & CODERS_MASKZ[i]) != 0)) {
			if (initialPositions[i] == 0) {
				initialPositions[i]=codersPositions[i];
			}
			lastZPositions[i]=codersPositions[i];
			codersZCounts[i]++;
			checkCodersFlags[i]=TRUE;
		}
	}
}

signed long getCoderValue(int index) {
	return codersPositions[index];
}

void clearCoders() {
	int i;
	for (i=0; i<MAX_CODERS; i++) {
		codersPositions[i]=0;
		codersErrorCounts[i]=0;
		codersErrorValues[i]=0;
		initialPositions[i]=0;
		lastZPositions[i]=0;
		codersZCounts[i]=0;
		checkCodersFlags[i]=FALSE;
	}
}

void initCoders(void) {
	// PortB as inputs for coders
	CODERS_TRIS = 0xFF;
	CODERS_PORT = 0xFF;

	canal = CODERS_PORT;

	CODERS_MASKA[0] = CODERS_MASKA_1;	
	CODERS_MASKB[0] = CODERS_MASKB_1;	
	CODERS_MASKZ[0] = CODERS_MASKZ_1;	
	CODERS_MASKA[1] = CODERS_MASKA_2;	
	CODERS_MASKB[1] = CODERS_MASKB_2;
	CODERS_MASKZ[1] = CODERS_MASKZ_2;

	clearCoders();
	registerInterrupt(CODER_TIMER_INDEX, 0, updateCoders);
}

void checkCoders() {
	int i;
	for (i=0; i<MAX_CODERS; i++) {
		if (!checkCodersFlags[i]) {
			continue;
		}
	
		checkCodersFlags[i]=FALSE;

		long position;
		long initial;
		long position2;
		long initial2;
		
		do
		{
			position=lastZPositions[i];
			initial=initialPositions[i];
			position2=lastZPositions[i];
			initial2=initialPositions[i];
		} while ((position != position2) || (initial != initial2));

		position %= CODERS_RESOLUTION;
		if (position<0) {
			position += CODERS_RESOLUTION;
		}
		initial %= CODERS_RESOLUTION;
		if (initial<0) {
			initial += CODERS_RESOLUTION;
		}
		long diff=position-initial;
		if ((diff < -CODERS_ERROR) || (diff > CODERS_ERROR)) {
			codersErrorCounts[i]++;
			codersErrorValues[i] += absLong(diff);
			initialPositions[i]=0;
		}
	}
}

int getCodersErrorCount(int index) {
	return codersErrorCounts[index];
}

int getCodersErrorValue(int index) {
	return codersErrorValues[index];
}

signed long getCodersInitialPosition(int index) {
	return initialPositions[index];
}

int getCodersZCount(int index) {
	return codersZCounts[index];
}

// DEVICE INTERFACE

void stopCoders(void) {

}	

unsigned int getCodersSoftwareRevision( void ) {
	return 1;
}

unsigned int isCodersDeviceOk( void ) {
	return 1;
}

char* getCodersDeviceName(void) {
	return "Coders";
}

DeviceDescriptor getCodersDeviceDescriptor() {
	DeviceDescriptor result;
	result.initDeviceFunction = *initCoders;
	result.stopDeviceFunction = *stopCoders;
	result.isDeviceOkFunction =  *isCodersDeviceOk;
	result.getSoftwareRevisionFunction = *getCodersSoftwareRevision;
	result.getDeviceNameFunction = getCodersDeviceName;  
	result.enabled = 1;

	return result;
}

