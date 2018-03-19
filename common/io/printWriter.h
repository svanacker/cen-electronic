#ifndef PRINT_WRITER_H
#define PRINT_WRITER_H

#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/buffer.h"

#include "../../common/string/cenString.h"

// STRINGS

/**
 * Append a char to the outputStream.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param c the char to write
 */
void append(OutputStream* outputStream, char c);

/**
 * Append a bool value (1 for true, 0 for false)
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param b the bool value to write
 */
unsigned int appendBool(OutputStream* outputStream, bool b);

/**
 * Append a bool value, but as string ("true" for true, "false" for false)
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param b the bool value to write
 */
unsigned int appendBoolAsString(OutputStream* outputStream, bool b);

/**
 * Append a separator to the outputStream.
 * @param outputStream the pointer on outputStream (POO simulation)
 */
void appendSeparator(OutputStream* outputStream);

/**
* Append a space to the outputStream.
* @param outputStream the pointer on outputStream (POO simulation)
*/
void appendSpace(OutputStream* outputStream);

/**
* Append by repeating chars to the outputStream.
* @param outputStream the pointer on outputStream (POO simulation)
* @param c the char to repeat
* @param count how many char we repeat
*/
unsigned int appendRepeatedChars(OutputStream* outputStream, char c, int count);

/**
* Append by repeating '-' to the outputStream.
* @param outputStream the pointer on outputStream (POO simulation)
* @param count how many dash we repeat
*/
unsigned int appendDashes(OutputStream* outputStream, int count);

/**
* Append a certain amount of spaces (use of table aligment).
* @param outputStream the pointer on outputStream (POO simulation)
* @param count how many spaces we want to append
*/
unsigned int appendSpaces(OutputStream* outputStream, int count);

/**
 * Append a string to the buffer.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param s a standard C String (terminated by \0)
 * @return how many chars were written
 */
unsigned int appendString(OutputStream* outputStream, const char* s);

/**
 * Append a char array with a specific length.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param s the pointer on the char array
 * @return how many chars were written
 */
unsigned int appendFixedCharArray(OutputStream* outputStream, FixedCharArray* s);

/**
* Append a char array with a specific length but encoded in hexadecimal.
* @param outputStream the pointer on outputStream (POO simulation)
* @param s the pointer on the char array
* @return how many chars were written
*/
unsigned int appendHexFixedCharArray(OutputStream* outputStream, FixedCharArray* s);

/**
 * Append a string with CRLF to the buffer.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param s a standard C String (terminated by \0)
 */
unsigned int appendStringCRLF(OutputStream* outputStream, const char* s);

/**
 * Add an acknowledgement to the outputStream.
 * @param outputStream the pointer on outputStream (POO simulation)
 */
unsigned int appendAck(OutputStream* outputStream);

/**
 * Write a LF to the outputStream.
 * @param outputStream the pointer on outputStream (POO simulation)
 */
unsigned int println(OutputStream* outputStream);

/**
 * Write a CRLF to the outputStream.
 * @param outputStream the pointer on outputStream (POO simulation)
 */
unsigned int appendCRLF(OutputStream* outputStream);

// BUFFER

/**
 * Print the content of buffer to the output Stream.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param buffer the buffer that we want to write
 */
unsigned int printBuffer(OutputStream* outputStream, Buffer* buffer);

// --- Management of hex conversion

/**
 * Sends an hexadecimal value to the serial output.
 * char c must be >= 0 and <= 15 to be appended to the outputStream. If not, the char will not be converted and we will write an error !
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param c the char value to write as hexadecimal
 * @return true if the char was appended, false else
 */
bool appendHex(OutputStream* outputStream, char c);

/**
 * Send a char value into hexadecimal value (2 chars)
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the value which must be sent
 */
void appendHex2(OutputStream* outputStream, char value);

/**
 * Send an signed int into hexadecimal value (3 chars)
 * @param value the value which must be sent
 */
void appendHex3(OutputStream* outputStream, signed int value);

/**
 * Send an signed int into hexadecimal value (4 chars)
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the value which must be sent
 */
void appendHex4(OutputStream* outputStream, signed int value);

/**
 * Send an signed int into hexadecimal value (5 chars)
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the value which must be sent
 */
void appendHex5(OutputStream* outputStream, signed int value);

/**
 * Send an signed long into hexadecimal value (6 chars)
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the value which must be sent
 */
void appendHex6(OutputStream* outputStream, signed long value);

/**
 * Send an signed long into hexadecimal value (8 chars)
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the value which must be sent
 */
void appendHex8(OutputStream* outputStream, signed long value);

// Hex - Float

/**
* Append a float value into hexadecimal value (2 chars).
* @param outputStream the pointer on outputStream (POO simulation)
* @param value the float value
* @param digitPrecision how many digit we would like to have
*/
void appendHexFloat2(OutputStream* outputStream, float value, unsigned int digitPrecision);

/**
 * Append a float value into hexadecimal value (4 chars).
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the float value
 * @param digitPrecision how many digit we would like to have
 */
void appendHexFloat4(OutputStream* outputStream, float value, unsigned int digitPrecision);

/**
* Append a float value into hexadecimal value (6 chars).
* @param outputStream the pointer on outputStream (POO simulation)
* @param value the float value
* @param digitPrecision how many digit we would like to have
*/
void appendHexFloat6(OutputStream* outputStream, float value, unsigned int digitPrecision);

/**
 * Append a float value into hexadecimal value (8 chars).
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the float value
 * @param digitPrecision how many digit we would like to have
 */
void appendHexFloat8(OutputStream* outputStream, float value, unsigned int digitPrecision);

/**
 * Sends the decimal value of a long.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the value to send
 * @return the number of characters sent
 * @return the number of char which are written
 */
int appendDec(OutputStream* outputStream, signed long value);

/**
 * Sends the decimal value of a float. The precision after the comma depend on the value. For value very low, we have 3 chars after the comma, but we could have only 1.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the value to send
 * @return the number of char which are written including part before comma, the comma, and after the comma
 */
int appendDecf(OutputStream* outputStream, float value);

// AGGREGATE FUNCTION

/**
 * Append a string followed by a float value.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param s the string to write
 * @param float the float value to write
 */
void appendStringAndDecf(OutputStream* outputStream, const char* s, float value);

/**
 * Append a string followed by a long value.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param s the string to write
 * @param value the value to write
 */
void appendStringAndDec(OutputStream* outputStream, const char* s, long value);

/**
* Append a string followed by a bool value.
* @param outputStream the pointer on outputStream (POO simulation)
* @param s the string to write
* @param value the value to write
*/
void appendStringAndBool(OutputStream* outputStream, const char* s, bool value);

/**
 * Append both string : key followed by a value.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param key the key to write
 * @param name the name to write
 */
void appendKeyAndName(OutputStream* outputStream, const char* key, const char* name);

#endif
