#ifndef EEPROM_TYPE_H
#define EEPROM_TYPE_H

#include "../../common/io/outputStream.h"

enum EepromType {
	/**
	* In Memory.
	*/
	EEPROM_TYPE_MEMORY,
    /** 
     * Hardware Eeprom
     */
    EEPROM_TYPE_HARDWARE,
    /**
     * File Eeprom (For PC for example)
     */
    EEPROM_TYPE_FILE
};

unsigned int appendEepromTypeAsString(OutputStream* outputStream, enum EepromType eepromType);

unsigned int addEepromTypeTableData(OutputStream* outputStream, enum EepromType eepromType, int columnSize);

#endif