#ifndef LCD24064_H
#define LCD24064_H

/**
* Wait until the LCD is not busy.
*/
void busyLCD_24064(void);

/**
* send a command write to LCD.
* @param  : data            data to send
*/
void commandWriteLCD_24064(int data2);

/**
* send a data to LCD.
* @param  : data            the data to send
*/
void dataWriteLCD_24064(int data1);

/**
* read data from LCD.
* @return : char c  the data
*/
char dataReadLCD_24064 (void);

/**
* Clear the texte Zone memory.
*/
void ClrTexteLCD_24064(void);

/**
* Clear the graphical zone memory.
*/
void ClrGraphLCD_24064(void);

/**
* Set graphical mode.
*/
void SetGraph_24064(void);

/**
* Set graphical and texte mode.
 */
void SetGrTx_24064(void);

/**
 * Set Texte mode.
 */
void SetTxt_24064(void);


/**
*setup the pic32 port to drice the lcd.
*/
void SetupLCD_24064(void);

/**
* set the Cursor position.
* @param    row     the cursor row position
* @param    col     the cursor column position
*/
void setCursorPosition_24064(int row, int col);

/**************************
* clear a text line and set the cursor position to next row.
* @param : row          the row to clear
*/
void clearTextLine_24064(int row);

/**
* scroll the text area and set the cursor at last row.
*/
void scrolltText_24064(void );

/**
* print one caracter on the screen.
* @param : c        the caracter to print
*/
void writeLCDChar(char c);

/**
* clear the graphical and texte area.
*/
void clearScreen_24064(void);

/**
* set the cursor position at home.
 */
void setCursorAtHome_24064 (void);

/**
 * hide the cursor.
 */
void hideCursor_24064 (void);

/**
* set cursor blinking
*/
void showUnderlineCursor_24064 (void);

/**
* print pixel at postion parameter.
* @param x  the x postion
* @param y  the y position
*/
void setPixel_24064(int x,int y);

/**
* draw a line.
* @param x1 the X Axe begin of the line
* @param y1 the Y Axe begin of the line
* @param x2 the X axe end of the line
* @param y2 the Y Axe end of the line
*/
void line_24064(int x1,int y1,int x2,int y2);

/**
* draw a picture.
*/
void drawPicture (void);

/**
 * init the 24064 LCD
 */
void InitLCD_24064(void);

/**
* setup the pic32 port to drive the lcd.
*/
void SetupLCD (void);

#endif