#ifndef READER_H
#define READER_H

#include "inputStream.h"

// READ METHODS

/**
 * Read a char with filtering.
 * Do NOT use it if the char is hexadecimal (with 2 chars)
 */
char readFilteredChar(InputStream* inputStream);

/**
* Read an hexadecimal value between 0 and 15.
* Read only one character.
* Same as readHex2, but considered the first char to be '0'
*/
int readHex(InputStream* inputStream);

/**
 * Read an hexadecimal value from an inputStream (2 hex char as "B5").
 * All value are positive
 */
int readHex2(InputStream* inputStream);

/**
 * Read an hexadecimal value from an inputStream (2 hex char as "B5").
 * Value is positive if < 128, and negative if >= 128
 */
signed int readSignedHex2(InputStream* inputStream);

/**
 * Read an hexadecimal value from an inputStream (4 hex char as "B51D").
 */
long readHex4(InputStream* inputStream);

/**
* Read a Hex4 and returns signed value.
*/
signed long readSignedHex4(InputStream* inputStream);

/**
 * Read an hexadecimal value from an inputStream (6 hex char as "04B51D").
 */
float readHex6(InputStream* inputStream);

// CHECK METHODS 
// 1) isXXX returns if the condition is ok, and return a BOO
// 2) checkIsXXX  checks that the value is right, and if it's not the case, write a DEBUG information


/**
 * Get next char and check if the stream contains ack.
 * @return TRUE if the next char is a ack, FALSE else
 */
BOOL isAck(InputStream* inputStream);

/**
 * Get next char and check if the stream contains the asked char.
 * @param expectedChar the character that we want to check
 * @return TRUE if the char is the right char, FALSE else
 */
BOOL isChar(InputStream* inputStream, char expectedChar);

/**
 * Check that the next char is a ack, and if not, write a DEBUG information
 * @param inputStream the inputStream in which we read char
 * @return TRUE if the data is a ack, FALSE else
 */
BOOL checkIsAck(InputStream* inputStream);

/**
 * Check that the next char is the char passed in argument, and if not, write a DEBUG information
 * @param inputStream the inputStream in which we read char
 * @param char expectedChar the character that we want to check
 * @return TRUE if the data is the wanted char, FALSE else
 */
BOOL checkIsChar(InputStream* inputStream, char expectedChar);

#endif
