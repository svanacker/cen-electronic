#ifndef PRINT_WRITER_H
#define PRINT_WRITER_H

#include "../../common/commons.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/buffer.h"

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
void appendBool(OutputStream* outputStream, bool b);

/**
 * Append a separator to the outputStream.
 * @param outputStream the pointer on outputStream (POO simulation)
 */
void appendSeparator(OutputStream* outputStream);

/**
 * Append a string to the buffer.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param s a standard C String (terminated by \0)
 */
void appendString(OutputStream* stream, const char* s);

/**
 * Append a string with CRLF to the buffer.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param s a standard C String (terminated by \0)
 */
void appendStringCRLF(OutputStream* stream, const char* s);

/**
 * Add an acknowledgment to the outputStream.
 * @param outputStream the pointer on outputStream (POO simulation)
 */
void appendAck(OutputStream* stream);

/**
 * Write a LF to the outputStream.
 * @param outputStream the pointer on outputStream (POO simulation)
 */
void println(OutputStream* outputStream);

/**
 * Write a CRLF to the outputStream.
 * @param outputStream the pointer on outputStream (POO simulation)
 */
void appendCRLF(OutputStream* stream);

// BUFFER

/**
 * Print the content of buffer to the output Stream.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param buffer the buffer that we want to write
 */
void printBuffer(OutputStream* outputStream, Buffer* buffer);



// --- Management of hex conversion

/**
 * Sends an hexadecimal value to the serial output.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param c the char value to write as hexadecimal
 */
void appendHex(OutputStream* outputStream, char c);

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

/**
 * Append a float value into hexadecimal value (4 chars).
 * We use a factor to decide how to trunc value (we multiply by factorToTrunc)
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the float value
 * @param factorToTrunc ?????
 */
void appendHexFloat4(OutputStream* outputStream, float value, float factorToTrunc);

/**
 * Append a float value into hexadecimal value (8 chars).
 * We use a factor to decide how to trunc value (we multiply by factorToTrunc)
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the float value
 * @param factorToTrunc ?????
 */
void appendHexFloat8(OutputStream* outputStream, float value, float factorToTrunc);

/**
 * Sends the decimal value of a long.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the value to send
 * @return the number of characters sent
 */
int appendDec(OutputStream* outputStream, signed long value);

/**
 * Sends the decimal value of a float.*
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param value the value to send
 */
int appendDecf(OutputStream* outputStream, float value);

// AGGREGATE FUNCTION

/**
 * Append a string followed by a float value.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param s the string to write
 * @param float the float value to write
 */
void appendStringAndDecf(OutputStream* stream, const char* s, float value);

/**
 * Append a string followed by a long value.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param s the string to write
 * @param value the value to write
 */
void appendStringAndDec(OutputStream* stream, const char* s, long value);

/**
 * Append both string : key followed by a value.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param key the key to write
 * @param name the name to write
 */
void appendKeyAndName(OutputStream* stream, const char* key, const char* name);

#endif
