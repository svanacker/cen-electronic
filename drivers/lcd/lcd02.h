#ifndef LCD02_H
#define LCD02_H

#include "../device.h"

/**
* LCD02 DEVANTECH DRIVER
* @version 30-01-2010 Basic command
*/

#define LCD02_ADDRESS_WRITE 0xC6
#define LCD02_ADDRESS_READ 0xC7
#define LCD02_COMMAND_REGISTER 0

// Backlight

#define BACKLIGHT_ON 19
#define BACKLIGHT_OFF 20

/**
* Returns a descriptor on the device LC02.
*/
DeviceDescriptor getLCD02DeviceDescriptor();

/**
* Set the cursor at the top and left of the screen.
*/
void lcd02_setCursorAtHome(void);

/**
* Set the cursor at the specified position (combinaison of row and line).
* @param position 1 to 80 (Ex : 36 corresponds to the row 2 and the column 16 (1 * 20 + 16)
*/
void lcd02_setCursorPosition (char position);

/**
* Set the cursor at the specified row and column.
* @param row row index between 1 and 4 = N° de la ligne de 1 à 4
* @param column column index de 1 à 20
*/
void lcd02_setCursorRowAndColumn(char row, char column);

/**
* Hide the cursor.
*/
void lcd02_hideCursor (void);

/**
* Set an underline to see the cursor.
*/
void lcd02_showUnderlineCursor (void);

/**
* Use blink cursor.
*/
void lcd02_setBlinkCursor(void);

/**
* Clean the previous character.
*/
void lcd02_backSpaceCursor (void);

/**
* Write a tabulation character.
*/
void lcd02_tabCursor (void);

/**
* go down the cursor of 1 row.
*/
void lcd02_smartLineCursor (void);

/**
* ???
*/
void lcd02_verticalTabCursor (void);

/**
* Clear the screen.
*/
void lcd02_clearScreen (void);

/**
* Active or not the backlight on the LCD.
*/
void lcd02_setBacklight(unsigned char enabled);

/**
* Do a carriage return operation on the cursor.
*/
void lcd02_carriageReturnCursor (void);

/**
* Clear the current column and shift the cursor from 1 column to the right.
**/
void lcd02_clearColumnCursor (void);

/**
* Sets the size of a tabulation character (default value is 4).
* @param tabulationSize size of tabulation (between 1 and 10)
*/
void lcd02_setTabulationSize (char tabulationSize);

/**
* writes a character at the current position of the cursor.
* @param c character to write on the LCD
*/
void lcd02_writeChar (char c);

/**
* Writes a string at the current position of the cursor.
* @param *s pointer on the string to write
*/
void lcd02_writeString (const char *s);

/**
* Writes a string at the current position of the cursor and returns the carriage at the begin of next line.
* @param *s pointer on the string to write
*/
void lcd02_writeStringCR(const char *s);

/**
* Send a command to the LCD.
* @param command the command to send
*/
void lcd02_sendCommand (char command);

/**
* Writes an int to the LCD
* @param value the number to write
*/
void lcd02_writeInt (signed long value);

/**
* Writes an int to the LCD and do a carriage Return
* @param value the number to write
*/
void lcd02_writeIntCR(signed long value);

// DEVICE INTERFACE

void initLCD02 ( void );

/**
* Returns the software revision of the LCD.
* @return Returns the software revision of the LCD.
*/
unsigned int getLCD02SoftwareRevision (void);

#endif
