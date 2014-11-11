#ifndef SERIAL_H
#define SERIAL_H

/** Define the index of serial port 1. */
#define SERIAL_PORT_1         1

/** Define the index of serial port 2. */
#define SERIAL_PORT_2         2

/** Define the index of serial port 3. */
#define SERIAL_PORT_3         3

/** Define the index of serial port 4. */
#define SERIAL_PORT_4         4

/** Define the index of serial port 5. */
#define SERIAL_PORT_5         5

/** Define the index of serial port 6. */
#define SERIAL_PORT_6         6

/** The default speed of the serial tranmission is fixed to 115200. */
#define DEFAULT_SERIAL_SPEED 115200L

/**
 * Open the serial port with the specified transmission rate.
 * 8 data bits, 1 stop bit, no parity bits.
 * @param serialPortIndex the serialPortIndex we want to use
 * @param baudRate the number of bits per second
 */
void openSerial(unsigned char serialPortIndex, unsigned long baudRate);

/**
 * Open the serial port with a default serial speed.
 * @param serialPortIndex the serialPortIndex we want to use
 */
void openSerialAtDefaultSpeed(unsigned char serialPortIndex);

/**
 * Closes the serial port.
 * @param serialPortIndex the serialPortIndex we want to close
 */
void closeSerial(unsigned char serialPortIndex);

/**
 * Sends a character to the serial output. This
 * function will block until the char can be
 * transmitted.
 * @param serialPortIndex the serialPortIndex we want to use
 * @param c the character to send
 */
void serialPutc(unsigned char serialPortIndex, char c);

/**
 * Reads a char from the serial input. This function
 * blocks until a char is received. Use kbhit() to
 * avoid blocking.
 * @param serialPortIndex the serialPortIndex we want to use
 * @return the character read
 */
char serialGetc(unsigned char serialPortIndex);

/**
 * Checks whether a character is available from the serial input.
 * return true or false
 * @param serialPortIndex the serialPortIndex we want to use
 * @return returns zero if no char is pending, else non-zero
 */
int kbhit(unsigned char serialPortIndex);

#endif
