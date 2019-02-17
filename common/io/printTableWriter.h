#ifndef PRINT_TABLE_WRITER_H
#define PRINT_TABLE_WRITER_H

#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/string/cenString.h"


/** 
* How many chars on a page. On windows, default width is 80, but it could be change.
*/
#define PRINT_TABLE_WRITER_DEFAULT_PAGE_CHAR_WIDTH   114

// COMMON TABLE FUNCTIONS

/**
 * Append the symbol '|'.
 * @param outputStream the pointer on outputStream (POO simulation)
 */
void appendTableSeparator(OutputStream* outputStream);

// HEADER

/**
* Create a dash line to fill a line and return to the next line via println.
*/
void appendTableHeaderSeparatorLine(OutputStream* outputStream);

/**
 * Append an header followed by '|' character.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param s string the header
 */
void appendStringHeader(OutputStream* outputStream, char* s, int columnSize);

/**
* Append an header composed by a string and a decimal value followed by '|' character.
* @param outputStream the pointer on outputStream (POO simulation)
* @param s string the header
* @param value the value after the string
*/
void appendStringAndDecHeader(OutputStream* outputStream, char* s, int value, int columnSize);

void appendEndOfTableColumn(OutputStream* outputStream, int columnSize);

// DATA

/**
* Add a String table data to the outputStream with | and space arround
* @param s the string to add
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendStringTableData(OutputStream* outputStream, const char* s, int columnSize);

/**
* Add a String (with only XXXX chars, fixed length) table data to the outputStream with | and space arround
* @param s the string to add
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendFixedCharArrayTableData(OutputStream* outputStream, FixedCharArray* s, int columnSize);

/**
* Add a String (with only XXXX chars, fixed length) table data (but encoded in hexadecimal) to the outputStream with | and space arround
* @param s the string to add
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendHexFixedCharArrayTableData(OutputStream* outputStream, FixedCharArray* s, int columnSize);

/**
* Add a Char table data to the outputStream with | and space arround
* @param c the char to append
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendCharTableData(OutputStream* outputStream, const char c, int columnSize);

/**
* Add a Decimal table data to the outputStream with | and space arround
* @param value the value to append (in decimal)
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendDecTableData(OutputStream* outputStream, const int value, int columnSize);

/**
* Add a Decimal Floating point table data to the outputStream with | and space arround
* @param value the value to append (in decimal with floating)
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendDecfTableData(OutputStream* outputStream, const float value, int columnSize);

/**
* Add a Boolean table (short => 0/1) data to the outputStream with | and space arround
* @param value the value to append (boolean)
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendBoolTableData(OutputStream* outputStream, const bool value, int columnSize);

/**
 * Add a Boolean table data (true / false) to the outputStream with | and space arround
* @param value the value to append (boolean)
* @param columnSize the size of the column (for alignment)
 */
unsigned int appendBoolAsStringTableData(OutputStream* outputStream, const bool value, int columnSize);

/**
* Add an hexadecimal table data to the outputStream with | and space arround
* @param value the value to append (in hexadecimal)
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendHex2TableData(OutputStream* outputStream, char value, int columnSize);

/**
* Add an hexadecimal table data to the outputStream with | and space arround
* @param value the value to append (in hexadecimal)
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendHex4TableData(OutputStream* outputStream, signed int value, int columnSize);

/**
* Add an hexadecimal table data to the outputStream with | and space arround
* @param value the value to append (in hexadecimal)
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendHex6TableData(OutputStream* outputStream, signed long value, int columnSize);

/**
* Add an hexadecimal table data to the outputStream with | and space arround
* @param value the value to append (in hexadecimal)
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendHexFloat4TableData(OutputStream* outputStream, float value, unsigned int digitPrecision, int columnSize);

/**
* Add an hexadecimal table data to the outputStream with | and space arround
* @param value the value to append (in hexadecimal)
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendHexFloat6TableData(OutputStream* outputStream, float value, unsigned int digitPrecision, int columnSize);

/**
* Add an binary table data to the outputStream with | and space arround
* @param value the value to append (in binary) and group by xxxx chars
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendBinary8TableData(OutputStream* outputStream, unsigned int value, unsigned int groupBy, int columnSize);

/**
* Add an binary table data to the outputStream with | and space arround
* @param value the value to append (in binary) and group by xxxx chars
* @param columnSize the size of the column (for alignment)
*/
unsigned int appendBinary16TableData(OutputStream* outputStream, unsigned int value, unsigned int groupBy, int columnSize);

#endif
