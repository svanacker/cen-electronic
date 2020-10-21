#ifndef IO_EXPANDER_FILE_PC_H
#define IO_EXPANDER_FILE_PC_H

#include "../ioExpander.h"

#define IO_EXPANDER_FILE_BIT_COUNT 8

/** 
 * Init a fake IO Expander Pc based on a file Implementation.
 * @param ioExpander the pointer on object (simulates POO)
 * @param ioExpanderFileName the fileName of the FILE which will 
 */
void initIOExpanderFilePc(IOExpander* ioExpander, const char* name, const char* fileName);

#endif
