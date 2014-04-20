#include <p30fxxxx.h>
#include <stdlib.h>

#include "../common/setup/pic30FSetup.h"

#include "../common/delay/cenDelay.h"

#include "../common/io/buffer.h"
#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"
#include "../common/io/ioUtils.h"
#include "../common/io/streamLink.h"

#include "../common/log/logHandler.h"
#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

#include "../common/serial/serial.h"
#include "../common/serial/serialLink.h"

// serial link DEBUG
#define    DEBUG_INPUT_BUFFER_ARRAY_LENGTH 30
static char debugInputBufferArray[DEBUG_INPUT_BUFFER_ARRAY_LENGTH];
static Buffer debugInputBuffer;

#define    DEBUG_OUTPUT_BUFFER_ARRAY_LENGTH 30
static char debugOutputBufferArray[DEBUG_OUTPUT_BUFFER_ARRAY_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

/**
 * Test the putc function.
 */
void putcTest() {
    unsigned char SERIAL_PORT_DEBUG = SERIAL_PORT_2;
    openSerialAtDefaultSpeed(SERIAL_PORT_DEBUG);
    serialPutc(SERIAL_PORT_DEBUG, 't');
    serialPutc(SERIAL_PORT_DEBUG, 'e');
    serialPutc(SERIAL_PORT_DEBUG, 's');
    serialPutc(SERIAL_PORT_DEBUG, 't');
    serialPutc(SERIAL_PORT_DEBUG, ' ');
    serialPutc(SERIAL_PORT_DEBUG, 'u');
    serialPutc(SERIAL_PORT_DEBUG, 'a');
    serialPutc(SERIAL_PORT_DEBUG, 'r');
    serialPutc(SERIAL_PORT_DEBUG, 't');
}

/**
 * Test UART Link
 */
void serialLinkTest() {
    unsigned char SERIAL_PORT_DEBUG = SERIAL_PORT_2;
    // Open the serial Link
    openSerialLink(&debugSerialStreamLink,
            &debugInputBuffer,
            &debugInputBufferArray,
            DEBUG_INPUT_BUFFER_ARRAY_LENGTH,
            &debugOutputBuffer,
            &debugOutputBufferArray,
            DEBUG_OUTPUT_BUFFER_ARRAY_LENGTH,
            &debugOutputStream,
            SERIAL_PORT_DEBUG, 0);

    initLog(DEBUG);

    while (1) {
        delaymSec(100);
        InputStream* inputStream = getInputStream(&debugInputBuffer);
        // OutputStream* outputStream = getOutputStream(&debugInputBuffer);
        copyInputToOutputStream(inputStream, &debugOutputStream, NULL, COPY_ALL);
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

