#ifndef DISTRIBUTOR_2018_H
#define DISTRIBUTOR_2018_H

enum DistributorSquareContent {
    /** The square is empty */
    SQUARE_CONTENT_EMPTY,
    /** The square contains a Clean Ball */
    SQUARE_CONTENT_CLEAN,
    /** The square contains a Dirty Ball */
    SQUARE_CONTENT_DIRTY,
};

struct Distributor;
typedef struct Distributor Distributor;

struct Distributor {
    enum DistributorSquareContent (*squares)[];
    unsigned int squareIndex;
};


#endif
