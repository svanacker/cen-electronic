#include "eeprom.h"

#include "../../common/error/error.h"

void eepromWriteInt(unsigned int index, signed int value) {
    // DO NOTHING
}

signed int eepromReadInt(unsigned int index) {
    return 0;
}

void eepromReadBloc(unsigned int index, char length, Buffer* buffer) {
    writeError(UNIMPLETEMENTED_EXCEPTION);
}

void printEepromBloc (OutputStream* outputStream,long index, unsigned int length, Buffer* buffer) {
    writeError(UNIMPLETEMENTED_EXCEPTION);
}

void eepromWriteBloc(unsigned int index, char length, Buffer* buffer) {
    writeError(UNIMPLETEMENTED_EXCEPTION);
}
