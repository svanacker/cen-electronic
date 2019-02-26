#ifndef EEPROM_TYPE_H
#define EEPROM_TYPE_H

#include "../../common/io/outputStream.h"

/**
 * Type of Eeprom.
 */
enum EepromType {
	/**
	* In Memory.
	*/
	EEPROM_TYPE_MEMORY,
    /** 
     * Hardware Eeprom (Ex : 24C12).
     */
    EEPROM_TYPE_HARDWARE,
    /**
     * File Eeprom (For PC for example)
     */
    EEPROM_TYPE_FILE
};

/**
 * Append the eeprom type as string in the outputStream.
 * @param outputStream
 * @param eepromType
 * @return 
 */
unsigned int appendEepromTypeAsString(OutputStream* outputStream, enum EepromType eepromType);

/**
 * Append the eeprom type as string in the outputStream for a table data formatting.
 * @param outputStream
 * @param eepromType
 * @param columnSize the size of the column
 * @return 
 */
unsigned int addEepromTypeTableData(OutputStream* outputStream, enum EepromType eepromType, int columnSize);

#endif