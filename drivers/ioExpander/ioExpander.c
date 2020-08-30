#include "ioExpander.h"

void initIOExpander(IOExpander* ioExpander,
        char* name,
        ioExpanderInitFunction* ioExpanderInit,
        ioExpanderReadValueFunction* ioExpanderReadValue,
        ioExpanderWriteValueFunction* ioExpanderWriteValue,
        ioExpanderReadSingleValueFunction* ioExpanderReadSingleValue,
        ioExpanderWriteSingleValueFunction* ioExpanderWriteSingleValue,
        unsigned int count,
        int* object) {
    ioExpander->name = name;
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
