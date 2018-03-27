#include "ioExpander.h"

void initIOExpander(IOExpander* ioExpander,
    ioExpanderInitFunction* ioExpanderInit,
    ioExpanderReadValueFunction* ioExpanderReadValue,
    ioExpanderWriteValueFunction* ioExpanderWriteValue,
    unsigned int count,
    int* object) {
    ioExpander->ioExpanderInit = ioExpanderInit;
    ioExpander->ioExpanderReadValue = ioExpanderReadValue;
    ioExpander->ioExpanderWriteValue = ioExpanderWriteValue;
    ioExpander->count = count;
    ioExpander->object = object;
}