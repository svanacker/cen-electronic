#ifndef READER_H
#define READER_H

#include "inputStream.h"

#include "../string/cenString.h"

// READ METHODS

#define    FILTERED_RESULT -1

/**
 * Read a char as bool (0 or 1) and returns the bool equivalent value.
 * @param inputStream the pointer on inputStream (POO simulation)
 * @return true if the char is equivalent to 1, false in case of 0 or true in case of != 0 || != 1, but writes an error
 */
 bool readBool(InputStream* inputStream);
 
/**
 * Read a char with filtering.
 * TODO : To Review
 * Do NOT use it if the char is hexadecimal (with 2 chars)
 * @param inputStream the pointer on inputStream (POO simulation)
 * @return the char value of the inputStream
 */
char readFilteredChar(InputStream* inputStream);

/**
 * Read a binary value as char of the inputStream without any filtering
 * @param inputStream the pointer on inputStream (POO simulation)
 * @return the value as char of the inputStream without any filtering
 */
char readBinaryChar(InputStream* inputStream);

/**
 * Read 2 octets and convert it to int without any filtering.
 * @param inputStream the pointer on inputStream (POO simulation)
 * @return the int value
 */
int readBinaryWord(InputStream* inputStream);

/**
 * Read an hexadecimal value between 0 and 15.
 * Read only one character.
 * Same as readHex2, but considered the first char to be '0'
 * @param inputStream the pointer on inputStream (POO simulation)
 * @return the hexadecimal value between 0 and 15.
 */
int readHex(InputStream* inputStream);

/**
 * Read an hexadecimal value from an inputStream (2 hex char as "B5").
 * All value are positive.
 * @param inputStream the pointer on inputStream (POO simulation)
 * @return the unsigned value converted from hexadecimal
 */
int readHex2(InputStream* inputStream);

/**
 * Read an hexadecimal value from an inputStream (2 hex char as "B5").
 * Value is positive if < 128, and negative if >= 128
 * @param inputStream the pointer on inputStream (POO simulation)
 * @return the signed value converted from hexadecimal
 */
signed int readSignedHex2(InputStream* inputStream);

/**
 * Read an hexadecimal value from an inputStream (4 hex char as "B51D").
 * @param inputStream the pointer on inputStream (POO simulation)
 * @return the unsigned long value  converted from hexadecimal
 */
long readHex4(InputStream* inputStream);

/**
 * Read a Hex4 and returns signed value.
 * @param inputStream the pointer on inputStream (POO simulation)
 * @return the long value  converted from hexadecimal
 */
signed long readSignedHex4(InputStream* inputStream);

/**
 * Read an hexadecimal value from an inputStream (6 hex char as "04B51D").
 * @param inputStream the pointer on inputStream (POO simulation)
 * TODO : Check the usage to know, if we must have a signed version too ???
 */
float readHex6(InputStream* inputStream);

/**
 * Read an array of chars from an inputStream (chars are encoded as hex).
 * @param s a pointer on a fixed char array
 */
void readHexFixedCharArray(InputStream* inputStream, const FixedCharArray* s);

// CHECK METHODS 
// 1) isXXX returns if the condition is ok, and return a BOO
// 2) checkIsXXX  checks that the value is right, and if it's not the case, write a DEBUG information


/**
 * Get next char and check if the stream contains ack.
 * @param inputStream the pointer on inputStream (POO simulation)
 * @return true if the next char is a ack, false else
 */
bool isAck(InputStream* inputStream);

/**
 * Get next char and check if the stream contains the asked char.
 * @param inputStream the pointer on inputStream (POO simulation)
 * @param expectedChar the character that we want to check
 * @return true if the char is the right char, false else
 */
bool isChar(InputStream* inputStream, char expectedChar);

/**
 * Check that the next char is a ack, and if not, write a DEBUG information
 * @param inputStream the inputStream in which we read char
 * @return true if the data is a ack, false else
 */
bool checkIsAck(InputStream* inputStream);

/**
 * Check that the next char is the char passed in argument, and if not, write a DEBUG information
 * @param inputStream the inputStream in which we read char
 * @param char expectedChar the character that we want to check
 * @return true if the data is the wanted char, false else
 */
bool checkIsChar(InputStream* inputStream, char expectedChar);

/**
 * Check that the next char is a separator
 * @param inputStream the inputStream in which we read char
 * @return true if the data is a separator char, false else
 */
bool checkIsSeparator(InputStream* inputStream);

#endif
