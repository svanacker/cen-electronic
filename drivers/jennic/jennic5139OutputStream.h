#ifndef JENNIC_5139_OUTPUT_STREAM_H
#define JENNIC_5139_OUTPUT_STREAM_H

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"

/**
 * Init a specific OutputStream dedicated to send data through the Zigbee.
 * The zigbee needs a command which wraps Data in their argument.
 */
void initZigbeeOutputStream(OutputStream* outputStream,
        						Buffer* jennic5139Buffer,
        						char* jennicAddress);


#endif

