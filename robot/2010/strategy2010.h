#ifndef STRATEGY2010_H
#define STRATEGY2010_H


/** Mask for the homologation. */
#define STRATEGY_HOMOLOGATION         0b00000001
#define STRATEGY_2                     0b00000010
#define STRATEGY_3                     0b00000011
#define STRATEGY_4                     0b00000100
#define STRATEGY_5                     0b00000101
#define STRATEGY_6                     0b00000110
#define STRATEGY_7                     0b00000111


/** The corn was not taken. */
#define CORN_BLACK_NOT_TAKEN 0

/** The corn was taken. */
#define CORN_WHITE_TAKEN 1

/**
 * Function used to manage strategy.
 */
void strategy2010(unsigned char strategy);

/**
 * Take corn if not black
 */
unsigned char takeCornIfNotBlack(int plierIndex);

#endif
