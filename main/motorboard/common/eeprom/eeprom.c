#include <p30fxxxx.h>
#include <libpic30.h>

#include "eeprom.h"

// Pointer to EEPROM data. The declaration causes the first WORD of EEPROM to be initialized when programming the device.
static signed int _EEDATA(32)* eeData;

void my_eeprom_write_int(unsigned int index, signed int value) {
    _prog_addressT EE_addr;

    // initialize a variable to represent the EEPROM address
    _init_prog_address(EE_addr, eeData);

    _erase_eedata(EE_addr + (index * _EE_WORD), _EE_WORD);
    _wait_eedata();

    // write value
    _write_eedata_word(EE_addr + (index * _EE_WORD), value);
    _wait_eedata();
}

signed int my_eeprom_read_int(unsigned int index) {
    signed int value;
    _prog_addressT EE_addr;

    // initialize a variable to represent the EEPROM address
    _init_prog_address(EE_addr, eeData);

    // read value
    _memcpy_p2d16(&value, EE_addr + (index * _EE_WORD), _EE_WORD);

    return value;
}
