#include <stdbool.h>

#include "../../common/setup/30F/picSetup30F.h"
#include "../../common/setup/30F/clockConstants30F.h"

#include "../../common/picunit/picunit.h"
#include "../../common/math/hexUtils.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"
#include "../../common/log/logLevel.h"

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

// The port for which we write unit Test
#define SERIAL_PORT_TEST     SERIAL_PORT_1

// logs
static LogHandler testLogHandler;

#define TEST_INPUT_BUFFER_LENGTH    100
#define TEST_OUTPUT_BUFFER_LENGTH    100
static char testInputBufferArray[TEST_INPUT_BUFFER_LENGTH];
static Buffer testInputBuffer;
static char testOutputBufferArray[TEST_OUTPUT_BUFFER_LENGTH];
static Buffer testOutputBuffer;
static OutputStream testOutputStream;
static StreamLink testSerialStreamLink;
static OutputStream testOutputStream;

static TestSuite testSuite;

bool hex2CharToIntTest1() {
    return true;
}

int main(void) {
    openSerialLink(&testSerialStreamLink,
            &testInputBuffer,
            &testInputBufferArray,
            100,
            &testOutputBuffer,
            &testOutputBufferArray,
            100,
            &testOutputStream,
            SERIAL_PORT_TEST,
            DEFAULT_SERIAL_SPEED);

    // Configure Logging
    initLog(DEBUG);
    addLogHandler(&testLogHandler, "UART", &testOutputStream, DEBUG);
    appendString(getTestOutputStream(), "TEST MAIN");

    // setBoardName("TEST MAIN");
    addTest(&testSuite, hex2CharToIntTest1, "hex2CharToIntTest1");

    runTestSuite(&testSuite);

    return 0;
}
