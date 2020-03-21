#include "eepromType.h"

#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

unsigned int appendEepromTypeAsString(OutputStream* outputStream, enum EepromType eepromType) {
    if (eepromType == EEPROM_TYPE_MEMORY) {
        return appendString(outputStream, "MEMORY");
    } else if (eepromType == EEPROM_TYPE_HARDWARE) {
        return appendString(outputStream, "HARD");
    } else if (eepromType == EEPROM_TYPE_FILE) {
        return appendString(outputStream, "FILE");
    } else {
        append(outputStream, '?');
        return 1;
    }
    return 0;
}

unsigned int addEepromTypeTableData(OutputStream* outputStream, enum EepromType eepromType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendEepromTypeAsString(outputStream, eepromType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}
