#ifndef SERIAL_H
#define SERIAL_H

/**
 * Wrap the port number for a serial link.
 */
enum SerialPort {
    /** Define the index of serial port 1. */
    SERIAL_PORT_1 = 1,

    /** Define the index of serial port 2. */
    SERIAL_PORT_2 = 2,

    /** Define the index of serial port 3. */
    SERIAL_PORT_3 = 3,

    /** Define the index of serial port 4. */
    SERIAL_PORT_4 = 4,

    /** Define the index of serial port 5. */
    SERIAL_PORT_5 = 5,

    /** Define the index of serial port 6. */
    SERIAL_PORT_6 = 6
};

/** The default speed of the serial transmission is fixed to 115200. */
#define DEFAULT_SERIAL_SPEED 115200L

/**
 * Open the serial port with the specified transmission rate.
 * 8 data bits, 1 stop bit, no parity bits.
 * @param serialPort the serial Port we want to use
 * @param baudRate the number of bits per second
 */
void openSerial(enum SerialPort serialPort, unsigned long baudRate);

/**
 * Open the serial port with a default serial speed.
 * @param serialPort the serialPortIndex we want to use
 */
void openSerialAtDefaultSpeed(enum SerialPort serialPort);

/**
 * Closes the serial port.
 * @param serialPortIndex the serialPortIndex we want to close
 */
void closeSerial(enum SerialPort serialPort);

/**
 * Sends a character to the serial output. This
 * function will block until the char can be
 * transmitted.
 * @param serialPortIndex the serialPortIndex we want to use
 * @param c the character to send
 */
void serialPutc(enum SerialPort serialPort, unsigned char c);

#endif
