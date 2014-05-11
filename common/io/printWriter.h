#ifndef PRINT_WRITER_H
#define PRINT_WRITER_H

#include "../../common/commons.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/buffer.h"

// STRINGS

/**
 * Append a char to the outputStream.
 */
void append(OutputStream* stream, char c);

/**
 * Append a bool value (1 for true, 0 for false)
 */
void appendBool(OutputStream* outputStream, bool b);

/**
 * Append a separator to the outputStream.
 */
void appendSeparator(OutputStream* outputStream);

/**
 * Append a string to the buffer.
 * @param s a standard C String (terminated by \0)
 */
void appendString(OutputStream* stream, const char* s);

void appendStringCRLF(OutputStream* stream, const char* s);

/**
 * Add an acknowledgment to the stream.
 */
void appendAck(OutputStream* stream);

void println(OutputStream* stream);

void appendCRLF(OutputStream* stream);

// BUFFER

/**
* Print the content of buffer to the output Stream.
*/
void printBuffer(OutputStream* outputStream, Buffer* buffer);



// --- Management of hex conversion

/**
 * Sends an hexadecimal value to the serial output.
 */
void appendHex(OutputStream* outputStream, char c);

/**
 * Send a char value into hexadecimal value (2 chars)
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
 * @param value the value which must be sent
 */
void appendHex4(OutputStream* outputStream, signed int value);

/**
 * Send an signed int into hexadecimal value (5 chars)
 * @param value the value which must be sent
 */
void appendHex5(OutputStream* outputStream, signed int value);

/**
 * Send an signed long into hexadecimal value (6 chars)
 * @param value the value which must be sent
 */
void appendHex6(OutputStream* outputStream, signed long value);

/**
 * Send an signed long into hexadecimal value (8 chars)
 * @param value the value which must be sent
 */
void appendHex8(OutputStream* outputStream, signed long value);

/**
 * Append a float value into hexadecimal value (4 chars).
 * We use a factor to decide how to trunc value (we multiply by factorToTrunc)
 */
void appendHexFloat4(OutputStream* outputStream, float value, float factorToTrunc);

/**
 * Append a float value into hexadecimal value (8 chars).
 * We use a factor to decide how to trunc value (we multiply by factorToTrunc)
 */
void appendHexFloat8(OutputStream* outputStream, float value, float factorToTrunc);

/**
 * Sends the decimal value of a long.
 * @param value the value to send
 * @return the number of characters sent
 */
int appendDec(OutputStream* stream, signed long value);

/**
 * Sends the decimal value of a float.
 * @param value the value to send
 */
int appendDecf(OutputStream* stream, float value);

// AGGREGATE FUNCTION

/**
 * Append a string followed by a float value
 */
void appendStringAndDecf(OutputStream* stream, const char* s, float value);

/**
 * Append a string followed by a long value
 */
void appendStringAndDec(OutputStream* stream, const char* s, long value);

/**
 * Append both string : key followed by a value.
 */
void appendKeyAndName(OutputStream* stream, const char* key, const char* name);

#endif
