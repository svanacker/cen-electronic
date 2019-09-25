#ifndef JENNIC_5139_INPUT_STREAM_H
#define JENNIC_5139_INPUT_STREAM_H

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"

/**
 * Init a specific InputStream dedicated to provide "payload" data which are transmitted from another Jennic.
 * It use in background a specific Parser and a buffer.
 */
void initZigbeeInputStream(InputStream* inputStream, char* jennicAddress);

#endif

