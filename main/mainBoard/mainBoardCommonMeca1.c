#include "mainBoardCommonMeca1.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/streamLink.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../device/deviceConstants.h"
#include "../../device/deviceList.h"

#include "../../drivers/dispatcher/uartDriverDataDispatcher.h"

// serial link Meca1
static char meca1InputBufferArray[MAIN_BOARD_MECA_1_INPUT_BUFFER_LENGTH];
static Buffer meca1InputBuffer;
static char meca1OutputBufferArray[MAIN_BOARD_MECA_1_OUTPUT_BUFFER_LENGTH];
static Buffer meca1OutputBuffer;
static OutputStream meca1OutputStream;
static StreamLink meca1SerialStreamLink;


/**
 * @private. 
 */
void mainBoardCommonMeca1AddDevices(void) {
    // Mechanical Board 1->UART
    // addUartRemoteDevice(getLauncher2018DeviceInterface(), MAIN_BOARD_SERIAL_PORT_MECA_1);
}

void mainBoardCommonMeca1AddDispatcher(void) {
    // Uart Stream for mechanicalBoard 1
    addUartDriverDataDispatcher(
        &meca1SerialStreamLink,
        "MECA_1_UART_DISPATCHER",
        MAIN_BOARD_SERIAL_PORT_MECA_1);
}

void mainBoardCommonMeca1Main(void) {
    // Open the serial Link for the Mechanical Board
    openSerialLink(&meca1SerialStreamLink,
                   "SERIAL_MECA_1", 
                   &meca1InputBuffer, &meca1InputBufferArray, MAIN_BOARD_MECA_1_INPUT_BUFFER_LENGTH,
                   &meca1OutputBuffer, &meca1OutputBufferArray, MAIN_BOARD_MECA_1_OUTPUT_BUFFER_LENGTH,
                   &meca1OutputStream,
                   MAIN_BOARD_SERIAL_PORT_MECA_1,
                   DEFAULT_SERIAL_SPEED);

}