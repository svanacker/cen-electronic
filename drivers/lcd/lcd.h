#ifndef LCD_H
#define LCD_H

#include <stdbool.h>

#include "../../device/device.h"
#include "../../common/io/outputStream.h"

// STREAM INTERFACE

/**
* init the outputStream for the LCD.
* @param outputStream the pointer to the outputStream which must be initialized
*/
void initLCDOutputStream(OutputStream* outputStream);

// LCD INTERFACE

/**
* Set the cursor at the top and left of the screen.
*/
void setCursorAtHome(void);

/**
* Set the cursor at the specified position (combinaison of row and line).
* @param position 1 to 80 (Ex : 36 corresponds to the row 2 and the column 16 (1 * 20 + 16)
*/
void setCursorPosition (unsigned char position);

/**
* Set the cursor at the specified row and column.
* @param row row index between 1 and 4 = N° de la ligne de 1 à 4
* @param column column index de 1 à 20
*/
void setCursorRowAndColumn(unsigned char row, unsigned char column);

/**
* Hide the cursor.
*/
void hideCursor (void);

/**
* Set an underline to see the cursor.
*/
void showUnderlineCursor (void);

/**
* Use blink cursor.
*/
void setBlinkCursor(void);

/**
* Clean the previous character.
*/
void backSpaceCursor (void);

/**
* Write a tabulation character.
*/
void tabCursor (void);

/**
* go down the cursor of 1 row.
*/
void smartLineCursor (void);

/**
* ???
*/
void verticalTabCursor (void);

/**
* Clear the screen.
*/
void clearScreen (void);

/**
* Active or not the backlight on the LCD.
*/
void setBacklight(bool enabled);

/**
* Do a carriage return operation on the cursor.
*/
void carriageReturnCursor (void);

/**
* Clear the current column and shift the cursor from 1 column to the right.
**/
void clearColumnCursor (void);

/**
* Sets the size of a tabulation character (default value is 4).
* @param tabulationSize size of tabulation (between 1 and 10)
*/
void setTabulationSize (unsigned char tabulationSize);

/**
* writes a character at the current position of the cursor.
* @param c character to write on the LCD
*/
void writeLCDChar (unsigned char c);

/**
* Send a command to the LCD.
* @param command the command to send
*/
void sendCommand (unsigned char command);

// DEVICE INTERFACE

/**
* Init the Lcd.
*/
void initLCD ( void );

/**
* Returns the software revision of the LCD.
* @return Returns the software revision of the LCD.
*/
unsigned int getLCDSoftwareRevision (void);

#endif
