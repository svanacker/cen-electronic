#ifndef MULTIPLEXER_PC_H
#define MULTIPLEXER_PC_H

#include "../multiplexer.h"

/** 
 * Init a fake IO Multiplexer Pc so that we could simulate it.
 * @param multiplexer the pointer on object (simulates POO)
 * @param pMultiplexerValue pointer on an int value to store the value which is used to store the different read and write
 */
void initMultiplexerPc(Multiplexer* multiplexer, int* pMultiplexerValue);

#endif
