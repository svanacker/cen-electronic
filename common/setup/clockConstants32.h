#ifndef CLOCK_CONSTANTS_32_H
#define CLOCK_CONSTANTS_32_H

// calcul de la fréquence du bus
#define	GetSystemClock() 			(80000000ul)
#define	GetPeripheralClock()		(GetSystemClock()/(1 << OSCCONbits.PBDIV))

#endif
