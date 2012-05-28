#include "../../common/commons.h"

#include <uart.h>

#include "serial.h"

#include "../../common/setup/clockConstants.h"

void openSerial(unsigned char serialPortIndex, unsigned long baudRate) {
    unsigned int config1 = UART_EN & UART_IDLE_CON & UART_DIS_ABAUD & UART_DIS_LOOPBACK & UART_NO_PAR_8BIT & UART_1STOPBIT;
    unsigned int config2 = UART_INT_TX_BUF_EMPTY & UART_TX_PIN_NORMAL & UART_TX_ENABLE & UART_INT_RX_CHAR & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR;

    // Fcy de (117964800/4) = 29491200 hz
    // UxBRG = FCY / (Vitesse * 16) - 1
    // ubrg = 191;		// 9600 bps
    // ubrg = 95;		// 19200 bps

    unsigned int ubrg = FCY / (baudRate * 16) - 1;
    if (serialPortIndex == SERIAL_PORT_1) {
        OpenUART1(config1, config2, ubrg);
        // 0 => UART on U1TX and U1RX
        // 1 => UART1 on U1ATX U1ARX
#ifndef PROG_32
		// no alternate mode because UARTxx are on separate PINs
        U1MODEbits.ALTIO = 1;
#endif
        // Interrupt whenever a character is received
        // Used for receiving a single character
        IEC0bits.U1RXIE = 1;
        U1STAbits.URXISEL = 1;
    } else if (serialPortIndex == SERIAL_PORT_2) {
        OpenUART2(config1, config2, ubrg);
        // Interrupt whenever a character is received
        // Used for receiving a single character
        // U2STAbits.U2RXIE = 1;
        IEC1bits.U2RXIE = 1;
        U2STAbits.URXISEL = 1;
    }
}

void openSerialAtDefaultSpeed(unsigned char serialPortIndex) {
    openSerial(serialPortIndex, DEFAULT_SERIAL_SPEED);
}

void closeSerial(unsigned char serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        CloseUART1();
    } else if (serialPortIndex == SERIAL_PORT_2) {
        CloseUART2();
    }
	/*
	 else if (serialPortIndex == SERIAL_PORT_3) {
        CloseUART3();
    } else if (serialPortIndex == SERIAL_PORT_4) {
        CloseUART4();
    }
	*/
}

int kbhit(unsigned char serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        return DataRdyUART1();
    } else if (serialPortIndex == SERIAL_PORT_2) {
        return DataRdyUART2();
    } /*
	 else if (serialPortIndex == SERIAL_PORT_3) {
        return DataRdyUART3();
    } else if (serialPortIndex == SERIAL_PORT_4) {
        return DataRdyUART4();
    }
	*/
    return 0;
}

char serialGetc(unsigned char serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        return ReadUART1();
    } else if (serialPortIndex == SERIAL_PORT_2) {
        return ReadUART2();
    } /*
	 else if (serialPortIndex == SERIAL_PORT_3) {
        return ReadUART3();
    } else if (serialPortIndex == SERIAL_PORT_4) {
        return ReadUART4();
    }
	*/
    return 0;
}

#ifdef MPLAB_SIMULATION

void simulateDelay() {
    int i = 1000;
    while (i > 0) {
        Nop();
        Nop();
        --i;
    }
}
#endif

void serialPutc(unsigned char serialPortIndex, char c) {
	// SERIAL 1
    if (serialPortIndex == SERIAL_PORT_1) {
        // waits for transmit buffer to be ready
		#ifndef MPLAB_SIMULATION
		        while (U1STAbits.UTXBF);
		#else
		        simulateDelay();
		#endif
        // transmits char
        WriteUART1(c);
	// SERIAL 2
    } else if (serialPortIndex == SERIAL_PORT_2) {
		#ifndef MPLAB_SIMULATION
		        while (U2STAbits.UTXBF);
		#else
		        simulateDelay();
		#endif
        // transmits char
        WriteUART2(c);
	}
	/*
	// SERIAL 3 
	#ifdef PROG_32
	    else if (serialPortIndex == SERIAL_PORT_3) {
			#ifndef MPLAB_SIMULATION
			        while (U3STAbits.UTXBF);
			#else
			        simulateDelay();
			#endif
	        // transmits char
	        WriteUART3(c);
		// SERIAL 4 
	    } else if (serialPortIndex == SERIAL_PORT_4) {
			#ifndef MPLAB_SIMULATION
			        while (U4STAbits.UTXBF);
			#else
			        simulateDelay();
			#endif
	        // transmits char
	        WriteUART4(c);
	    }
	#endif
	*/
}
