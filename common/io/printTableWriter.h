#ifndef PRINT_TABLE_WRITER_H
#define PRINT_TABLE_WRITER_H

#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/string/cenString.h"

// COMMON TABLE FUNCTIONS

/**
 * Append the symbol '|'.
 * @param outputStream the pointer on outputStream (POO simulation)
 */
void appendTableSeparator(OutputStream* outputStream);

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

// HEADER

/**
 * Append an header followed by '|' character.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param s string the header
 */
void appendStringHeader(OutputStream* outputStream, char* s, int columnSize);

// DATA

/**
* Add a String table data to the outputStream with | and space arround
* @param s the string to add
* @param columnSize the size of the column (for alignment)
*/
unsigned int  appendStringTableData(OutputStream* outputStream, const char* s, int columnSize);

/**
* Add a Char table data to the outputStream with | and space arround
* @param c the char to append
* @param columnSize the size of the column (for alignment)
*/
unsigned int  appendCharTableData(OutputStream* outputStream, const char c, int columnSize);

/**
* Add a Decimal table data to the outputStream with | and space arround
* @param value the value to append (in decimal)
* @param columnSize the size of the column (for alignment)
*/
unsigned int  appendDecTableData(OutputStream* outputStream, const value, int columnSize);


#endif
