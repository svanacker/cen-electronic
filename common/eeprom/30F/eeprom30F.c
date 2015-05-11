#include <p30Fxxxx.h>
#include <libpic30.h>

#include <stdlib.h>

#include "../../../common/error/error.h"
#include "../eeprom.h"

#define    EEPROM_30F_MAX_INDEX    31

// Pointer to EEPROM data. The declaration causes the first WORD of EEPROM to be initialized when programming the device.
static signed int _EEDATA(EEPROM_30F_MAX_INDEX + 1)* eeData;

void my_eeprom_write_int(Eeprom* eeprom_, unsigned long index, unsigned char value) {
    if (index >= EEPROM_30F_MAX_INDEX) {
        writeError(EEPROM_OUT_OF_BOUNDS);
        return;
    }
    _prog_addressT EE_addr;

    // initialize a variable to represent the EEPROM address
    _init_prog_address(EE_addr, eeData);

    _erase_eedata(EE_addr + (index * _EE_WORD), _EE_WORD);
    _wait_eedata();

    // write value
    _write_eedata_word(EE_addr + (index * _EE_WORD), value);
    _wait_eedata();
}

unsigned char my_eeprom_read_int(Eeprom* eeprom_, unsigned long index) {
    if (index >= EEPROM_30F_MAX_INDEX) {
        writeError(EEPROM_OUT_OF_BOUNDS);
        return -1;
    }
    signed int value;
    _prog_addressT EE_addr;

    // initialize a variable to represent the EEPROM address
    _init_prog_address(EE_addr, eeData);

    // read value
    _memcpy_p2d16(&value, EE_addr + (index * _EE_WORD), _EE_WORD);

    return (unsigned char) value;
}

void eeprom30FReadBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    writeError(UNIMPLETEMENTED_EXCEPTION);
}

void eeprom30FWriteBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    writeError(UNIMPLETEMENTED_EXCEPTION);
}

void _loadEeprom30F(Eeprom* eeprom_) {
    if (eeprom_ == NULL) {
        writeError(UNIMPLETEMENTED_EXCEPTION);
        return;
    }  
}

void _dumpEeprom30F(Eeprom* eeprom_) {
    if (eeprom_ == NULL) {
        writeError(UNIMPLETEMENTED_EXCEPTION);
        return;
    }  
}

void initEeprom30F(Eeprom* eeprom_) {
    initEeprom(eeprom_,
               EEPROM_30F_MAX_INDEX,
               my_eeprom_write_int,
               my_eeprom_read_int,
               eeprom30FWriteBlock,
               eeprom30FReadBlock,
               _loadEeprom30F,
               _dumpEeprom30F,
               NULL);
}
