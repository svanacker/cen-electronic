#include "ioExpander.h"

void initIOExpander(IOExpander* ioExpander,
        ioExpanderInitFunction* ioExpanderInit,
        ioExpanderReadValueFunction* ioExpanderReadValue,
        ioExpanderWriteValueFunction* ioExpanderWriteValue,
        ioExpanderReadSingleValueFunction* ioExpanderReadSingleValue,
        ioExpanderWriteSingleValueFunction* ioExpanderWriteSingleValue,
        unsigned int count,
        int* object) {
    ioExpander->ioExpanderInit = ioExpanderInit;
    ioExpander->ioExpanderReadValue = ioExpanderReadValue;
    ioExpander->ioExpanderWriteValue = ioExpanderWriteValue;
    ioExpander->ioExpanderReadSingleValue = ioExpanderReadSingleValue;
    ioExpander->ioExpanderWriteSingleValue = ioExpanderWriteSingleValue;
    ioExpander->count = count;
    ioExpander->object = object;
}

void ioExpanderSetOnValueChangeEvent(IOExpander* ioExpander, 
                                     ioExpanderOnValueChangeEventFunction* ioExpanderOnValueChangeEvent,
                                     int* eventContext) {
    ioExpander->ioExpanderOnValueChangeEvent = ioExpanderOnValueChangeEvent;
    ioExpander->eventContext = eventContext;
}
