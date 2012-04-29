#include <p30fxxxx.h>
#include <stdlib.h>

#include "../../common/setup/pic30FSetup.h"

#include "../../common/delay/delay30F.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/streamLink.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

// serial link DEBUG 
static Buffer debugInputBuffer;
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;


/**
* Test the putc function.
*/
void putcTest() {
	unsigned char SERIAL_PORT_DEBUG = SERIAL_PORT_2;
	openSerialAtDefaultSpeed(SERIAL_PORT_DEBUG);
	putc(SERIAL_PORT_DEBUG, 't');
	putc(SERIAL_PORT_DEBUG, 'e');
	putc(SERIAL_PORT_DEBUG, 's');
	putc(SERIAL_PORT_DEBUG, 't');
	putc(SERIAL_PORT_DEBUG, ' ');
	putc(SERIAL_PORT_DEBUG, 'u');
	putc(SERIAL_PORT_DEBUG, 'a');
	putc(SERIAL_PORT_DEBUG, 'r');
	putc(SERIAL_PORT_DEBUG, 't');
}

/**
* Test UART Link
*/
void serialLinkTest() {
	unsigned char SERIAL_PORT_DEBUG = SERIAL_PORT_2;
	// Open the serial Link
	openSerialLink(	&debugSerialStreamLink,
					&debugInputBuffer,
					&debugOutputBuffer,
					&debugOutputStream,
					SERIAL_PORT_DEBUG);

	initLog(DEBUG);

	while (1) {
		delaymSec(100);
		InputStream* inputStream = getInputStream(&debugInputBuffer);
		// OutputStream* outputStream = getOutputStream(&debugInputBuffer);
		copyInputToOutputStream(inputStream, &debugOutputStream, NULL);
	}

}

/**
 * ECHO PROGRAM
 */
int main(void) {
	putcTest();
	serialLinkTest();

	return 0;
}

