#include "../../common/commons.h"

#ifdef PROG_32
	#include <p32xxxx.h>
#else
	#include <p30fxxxx.h>
#endif

#include <string.h>

#include "lcdHd44780.h"
#include "../../common/delay/cenDelay.h"

#define LCD_ROW_COUNT	 4
#define LCD_COLUMN_COUNT 20

static char currentRow;
static char currentColumn;

/**
 * Verifie et attend si l'afficheur a fini d'effectuer ses op�rations interne.
 */
void busyFlag(void) {

    TRIS_D7_LCD = 1;
    TRIS_D6_LCD = 1;
    TRIS_D5_LCD = 1;
    TRIS_D4_LCD = 1;

    // do {
    E_LCD = 0;
    RS_LCD = 0;
    RW_LCD = 1;

    delay100us(5);
    E_LCD = 1;

    delay100us(5);

    E_LCD = 0;
    // Provoque des blocages en mode normal => supprim� par SV
    // }
    //while (D7_LCD);

    E_LCD = 0;

    /////////////adresse � enregistrer//////////////

    TRIS_D7_LCD = 0;
    TRIS_D6_LCD = 0;
    TRIS_D5_LCD = 0;
    TRIS_D4_LCD = 0;
}

void hd44780_sendIniComLcd(char D7, char D6, char D5, char D4) {
    delay100us(5);
    E_LCD = 0;
    delay100us(5);
    RS_LCD = 0;
    delay100us(5);
    RW_LCD = 0;
    delay100us(5);
    D7_LCD = D7;
    D6_LCD = D6;
    D5_LCD = D5;
    D4_LCD = D4;
    delay100us(5);
    E_LCD = 1;
    delay100us(5);
    E_LCD = 0;
    delay100us(5);
}

void hd44780_sendComLcd(char comLcd) {
    // Transfer du MSB pr�paration des signaux de commande
    delay100us(5);
    E_LCD = 0;
    delay100us(5);
    RS_LCD = 0;
    delay100us(5);
    RW_LCD = 0;
    delay100us(5);

    // transfer des 4 bits de poid fort
    D7_LCD = (comLcd & 0b10000000) >> 7;
    D6_LCD = (comLcd & 0b01000000) >> 6;
    D5_LCD = (comLcd & 0b00100000) >> 5;
    D4_LCD = (comLcd & 0b00010000) >> 4;

    //validation des 4 bits
    delay100us(5);
    E_LCD = 1;
    delay100us(5);
    E_LCD = 0;
    delay100us(5);

    // Transfer du LSB pr�paration des signaux de commande

    // transfer des 4 bits de poid faible
    D7_LCD = (comLcd & 0b00001000) >> 3;
    D6_LCD = (comLcd & 0b00000100) >> 2;
    D5_LCD = (comLcd & 0b00000010) >> 1;
    D4_LCD = (comLcd & 0b00000001);

    //validation des 4 bits
    delay100us(5);
    E_LCD = 1;
    delay100us(5);
    E_LCD = 0;
}

void hd44780_sendDataLcd(char DataLcd) {
    // Transfer du MSB pr�paration des signaux de commande
    delay100us(5);
    E_LCD = 0;
    delay100us(5);
    RS_LCD = 1;
    delay100us(5);
    RW_LCD = 0;
    delay100us(5);

    // transfer des 4 bits de poid fort
    D7_LCD = (DataLcd & 0b10000000) >> 7;
    D6_LCD = (DataLcd & 0b01000000) >> 6;
    D5_LCD = (DataLcd & 0b00100000) >> 5;
    D4_LCD = (DataLcd & 0b00010000) >> 4;

    //validation des 4 bits
    delay100us(5);
    E_LCD = 1;
    delay100us(5);
    E_LCD = 0;
    delay100us(5);

    // Transfer du LSB pr�paration des signaux de commande

    // transfer des 4 bits de poid faible
    D7_LCD = (DataLcd & 0b00001000) >> 3;
    D6_LCD = (DataLcd & 0b00000100) >> 2;
    D5_LCD = (DataLcd & 0b00000010) >> 1;
    D4_LCD = (DataLcd & 0b00000001);

    //validation des 4 bits
    delay100us(5);
    E_LCD = 1;
    delay100us(5);
    E_LCD = 0;
}

void hd44780_initLcd(void) {
    currentRow = 0;
    currentColumn = 0;
    busyFlag();

    // PORT de Commande et de DAta en Sortie
    TRIS_RS_LCD = 0;
    TRIS_RW_LCD = 0;
    TRIS_E_LCD = 0;
    TRIS_D7_LCD = 0;
    TRIS_D6_LCD = 0;
    TRIS_D5_LCD = 0;
    TRIS_D4_LCD = 0;

    delaymSec(5);
    hd44780_sendIniComLcd(0, 0, 1, 1); //fonction set : 8bits

    delaymSec(5);
    hd44780_sendIniComLcd(0, 0, 1, 1); //fonction set : 8bits

    delaymSec(5);
    hd44780_sendIniComLcd(0, 0, 1, 1); //fonction set : 8bits

    delaymSec(5);
    hd44780_sendIniComLcd(0, 0, 1, 0); //fonction set : 4bits
    hd44780_sendComLcd(0b00101000); //fonction set : 4 bits  2lignes  5x8dots
    hd44780_sendComLcd(0b00001000); //display off  curs off  blinkin cursor off
    hd44780_sendComLcd(0b00001111); //display on  curs on  blinkin cursor on
    hd44780_sendComLcd(0b00000001); //display clear
    hd44780_sendComLcd(0b00000110); //increment   accompagnies display shift
    hd44780_setCursorAtHome();
}

void hd44780_writeString(char *text) {
    char i;
    char a;

    a = strlen(text);

    for (i = 1; i <= a; i++) {
        hd44780_sendDataLcd(*text);
        text++;
    }
}

void hd44780_affTexteLcdXY(char *text, char column, char row) {
    char i;
    char a;

    hd44780_setCursorRowAndColumn(column, row);

    a = strlen(text);

    for (i = 1; i <= a; i++) {
        hd44780_sendDataLcd(*text);
        text++;
    }
}

void incLcdRow() {
    currentRow++;
    if (currentRow >= LCD_ROW_COUNT) {
        currentRow = 0;
    }
}

void incLcdColumn() {
    currentColumn++;
    if (currentColumn >= LCD_COLUMN_COUNT) {
        incLcdRow();
        currentColumn = 0;
    }
}

void hd44780_setCursorRowAndColumn(char row, char column) {
    currentRow = row;
    currentColumn = column;

    char cursor;
    if (row == 0) {
        cursor = 0x80;
    }
    if (row == 1) {
        cursor = 0xC0;
    }
    if (row == 2) {
        cursor = 0x94;
    }
    if (row == 3) {
        cursor = 0xD4;
    }
    cursor = cursor + column;
    hd44780_sendComLcd(cursor);

}

void hd44780_hideCursor(void) {
    hd44780_sendComLcd(0b00001100);
}

void hd44780_showUnderlineCursor(void) {
    hd44780_sendComLcd(0b00001110);
}

void hd44780_setBlinkCursor(void) {
    hd44780_sendComLcd(0b00001111);
}

void initCursorPosition() {
    currentColumn = 0;
    currentRow = 0;
}

void hd44780_setCursorAtHome(void) {
    initCursorPosition();
    hd44780_sendComLcd(0b00000010);
}

void hd44780_clearScreen(void) {
    initCursorPosition();
    hd44780_sendComLcd(0b00000001);
}

void hd44780_writeChar(char c) {
    hd44780_setCursorRowAndColumn(currentRow, currentColumn);

    // does not handle CR
    if (c == CR) {
        return;
    }
    if (c == LF) {
        while (currentColumn != 0) {
            // Fill with spaces
            hd44780_sendDataLcd(' ');
            incLcdColumn();
        }
        hd44780_setCursorRowAndColumn(currentRow, currentColumn);
    }
	else if (c == CLS) {
		hd44780_setCursorAtHome();
		hd44780_clearScreen();
	}
	 else {
        hd44780_sendDataLcd(c);
        incLcdColumn();
    }
}
