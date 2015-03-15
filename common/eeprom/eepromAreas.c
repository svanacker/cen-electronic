#include "eepromAreas.h"

#include <stdbool.h>
#include "eeprom.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"
#include "../../common/log/logLevel.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/**
 * Returns true if the area is initialized. A marker must be written at the two first character to consider it as initialized.
 */
bool isEepromAreaInitialized(Eeprom* eeprom_, unsigned long initiazedAreaIndex) {
    unsigned int marker = eepromReadInt(eeprom_, initiazedAreaIndex);
    /*
    appendString(getDebugOutputStreamLogger(), "marker=");
    appendDec(getDebugOutputStreamLogger(), marker);
    appendCRLF(getDebugOutputStreamLogger());
    */
    bool result = (marker == EEPROM_AREA_IS_INITIALIZED_MARKER);
    
    return result;
}

void initEepromArea(Eeprom* eeprom_, unsigned long initiazedAreaIndex) {
    eepromWriteInt(eeprom_, initiazedAreaIndex, EEPROM_AREA_IS_INITIALIZED_MARKER);
}