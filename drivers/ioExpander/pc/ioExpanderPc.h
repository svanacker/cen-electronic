#ifndef IO_EXPANDER_PC_H
#define IO_EXPANDER_PC_H

#include "../ioExpander.h"

/** 
 * Init a fake IO Expander Pc so that we could simulate it.
 * @param ioExpander the pointer on object (simulates POO)
 * @param pIOExpanderValue pointer on an int value to store the value which is used to store the different read and write
 */
void initIOExpanderPc(IOExpander* ioExpander, int* pIOExpanderValue);

#endif
