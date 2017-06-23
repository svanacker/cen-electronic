#ifndef PRINT_TABLE_WRITER_H
#define PRINT_TABLE_WRITER_H

#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/string/cenString.h"

/**
 * Append the symbol '|'.
 * @param outputStream the pointer on outputStream (POO simulation)
 */
void appendTableSeparator(OutputStream* outputStream);

/**
 * Append an header followed by '|' character.
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param s string the header
 */
unsigned int appendStringHeader(OutputStream* outputStream, char* s);

void appendStringTableData(OutputStream* outputStream, const char* s, int totalLength);

void appendCharTableData(OutputStream* outputStream, const char c, int totalLength);

/**
 * Append a certain amount of spaces (use of table aligment).
 * @param outputStream the pointer on outputStream (POO simulation)
 * @param count how many space we want to append
 */
unsigned int appendSpaces(OutputStream* outputStream, int count);

unsigned int appendRepeatedChars(OutputStream* outputStream, char c, int count);

unsigned int appendRepeatedDash(OutputStream* outputStream, int count);

#endif
