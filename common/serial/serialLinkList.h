#ifndef SERIAL_LINK_LIST_H
#define SERIAL_LINK_LIST_H

#include "serialLink.h"

/**
 * The struct defining a list of serialLink.
 */
typedef struct SerialLinkList {
    /** An array of pointer on serialLink. */
    SerialLink(*links)[];
    /** the size of the list. */
    unsigned char size;
    /** the max size of the list. */
    unsigned char maxSize;
} SerialLinkList;

/**
 * Initializes the SerialLink List with an array and the size of the array to avoid big and uniform
 * array length.
 * @param serialListArray the array of pointer serial Link to add.
 * @param serialListSize the size of the array of pointer to add.
 */
void initSerialLinkList(SerialLink(*serialLinkListArray)[], unsigned char serialLinkListSize);

/**
 * Get the list of serial Links.
 * @return the list of serial Links.
 */
SerialLinkList* getSerialLinkList(void);

/**
 * Add a serial Link device.
 * @return a pointer on the Device accessible locally
 */
SerialLink* addSerialLink(void);

/**
 * Get the serialLink with specific index.
 * @param index the index of the device
 * @return a pointer on the Device
 */
SerialLink* getSerialLink(int index);

/** 
 * Get the serialLink with serialPort.
 * @param serialPort the searched serialPort
 * @return the serialLink with the search serialPort, NULL else.
 */
SerialLink* getSerialLinkBySerialPort(enum SerialPort serialPort);

/**
 * Get the count of serialLink.
 * @result the count of serialLink
 */
int getSerialLinkCount(void);

#endif

