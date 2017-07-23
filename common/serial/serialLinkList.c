#include <stdlib.h>
#include <stdbool.h>

#include "serialLinkList.h"
#include "serialLink.h"
#include "serial.h"

#include "../../common/error/error.h"
#include "../../common/io/outputStream.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/math/cenMath.h"

// Singleton
static SerialLinkList serialLinkList;

SerialLinkList* getSerialLinkList(void) {
    return &serialLinkList;
}

void initSerialLinkList(SerialLink (*serialLinkArray)[], unsigned char serialLinkSize) {
    serialLinkList.links = serialLinkArray;
    serialLinkList.size = 0;
    serialLinkList.maxSize = serialLinkSize;
}

SerialLink* addSerialLink(void) {
    if (serialLinkList.maxSize == 0) {
        writeError(SERIAL_LINK_LIST_NOT_INITIALIZED);
        return NULL;
    }

    unsigned char size = serialLinkList.size;
    if (size < serialLinkList.maxSize) {
        SerialLink* serialLink = getSerialLink(size);
        // get a pointer on a serialLink already allocated (because we provide at init a pointer on an array of serialLink
        // serialLink->todo = todo;
        serialLinkList.size++;
        return serialLink;
    } else {
        writeError(SERIAL_LINK_LIST_TOO_MUCH_LINKS);
        return NULL;
    }
}

SerialLink* getSerialLink(int index) {
    if (serialLinkList.maxSize == 0) {
        writeError(SERIAL_LINK_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if (index < 0 || index >= serialLinkList.maxSize) {
        writeError(SERIAL_LINK_LIST_OUT_OF_BOUNDS);
        return NULL;
    }
    SerialLink* result = (SerialLink*) serialLinkList.links;
    // we don't need use sizeof because our pointer is a SerialLink* pointer, so the shift
    // is already of the structure, we just have to shift of index.
    result += index;

    return result;
}

SerialLink* getSerialLinkBySerialPort(enum SerialPort serialPort) {
    if (serialLinkList.maxSize == 0) {
        writeError(SERIAL_LINK_LIST_NOT_INITIALIZED);
        return NULL;
    }
    int i;
    for (i = 0; i < serialLinkList.maxSize; i++) {
        SerialLink* serialLink = getSerialLink(i);
        if (serialLink->serialPort == serialPort) {
            return serialLink;
        }
    } 
    return NULL;
}


int getSerialLinkCount() {
    return serialLinkList.size;
}


