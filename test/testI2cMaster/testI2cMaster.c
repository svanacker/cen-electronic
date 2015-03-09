#include <p30Fxxxx.h>
#include <stdlib.h>

#include "../../common/setup/pic30FSetup.h"

#include "../../common/delay/delay30F.h"

#include "../../common/i2c/master/i2cMasterSetup.h"
#include "../../common/i2c/master/i2cMasterInputStream.h"
#include "../../common/i2c/master/i2cMasterOutputStream.h"

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

#include "../../drivers/pcf/pcf8574.h"

// serial link DEBUG 
static Buffer debugInputBuffer;
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// logs
static LogHandler serialLogHandler;

// I2C Master
static InputStream i2cInputStream;
static OutputStream i2cOutputStream;
static Buffer i2cBuffer;

/**
* Test PCF8574
*/
void testPcf8574() {
    unsigned char SERIAL_PORT_DEBUG = SERIAL_PORT_2;
    // Open the serial Link
    openSerialLink(    &debugSerialStreamLink,
                    &debugInputBuffer,
                    &debugOutputBuffer,
                    &debugOutputStream,
                    SERIAL_PORT_DEBUG);

    // Logs
    initLog(DEBUG);
    addLogHandler(&serialLogHandler, "UART", &debugOutputStream, DEBUG);
    appendString(getInfoOutputStreamLogger(), "TEST I2C MASTER ");

    delaymSec(1000);

    i2cMasterInitialize();

    while (1) {
        delaymSec(1000);

        testPCF8574(&debugOutputStream);
        appendCRLF(&debugOutputStream);
        InputStream* inputStream = getInputStream(&debugInputBuffer);
        copyInputToOutputStream(inputStream, &debugOutputStream, NULL);
    }
}

/**
* Test I2C_MASTER WITH CUSTOM I2C_SLAVE
*/
void testInputStream() {
    unsigned char SERIAL_PORT_DEBUG = SERIAL_PORT_2;
    // Open the serial Link
    openSerialLink(    &debugSerialStreamLink,
                    &debugInputBuffer,
                    &debugOutputBuffer,
                    &debugOutputStream,
                    SERIAL_PORT_DEBUG);

    // Logs
    initLog(DEBUG);
    addLogHandler(&serialLogHandler, "UART", &debugOutputStream, DEBUG);
    appendString(getInfoOutputStreamLogger(), "TEST I2C MASTER ");

    delaymSec(1000);

    // i2cMasterInitialize();

    initMasterI2cOutputStream(&i2cOutputStream, &i2cBuffer, 0x50);
    initMasterI2cInputStream(&i2cInputStream, 0x50);

    // appendString(&i2cOutputStream, "I2C Hello From Master");
    appendString(&i2cOutputStream, "t20");
    i2cOutputStream.flush(&i2cOutputStream);

    while (1) {
        delaymSec(2000);
        // Read data from the slave to the UART
        copyInputToOutputStream(&i2cInputStream, &debugOutputStream, NULL);

        delaymSec(2000);
        appendString(&i2cOutputStream, "t20");
        i2cOutputStream.flush(&i2cOutputStream);
    }
}

/**
 * TEST FOR I2C Master
 */
int main(void) {
    testInputStream();

    return 0;
}


