#include "hd44780Test.h"

#include "../common/delay/delay30F.h"
#include "../device/drivers/lcd/lcd.h"
#include "../device/drivers/lcd/lcdHd44780.h"

void hd44780Test (void){

	char *message_init1="CONTROLEUR   HD44780";
	char *message_init2="    EUROBOT 2011";
	char *message_init3="CYBERNETIQUE EN NORD"; 
	char *message_init4="31-08-2010    Jerome"; 


	delaymSec(3000);

	hd44780_initLcd();

	hd44780_setCursorRowAndColumn(2,1);
	hd44780_setBlinkCursor();

	hd44780_clearScreen();

	hd44780_writeChar('a');

	while (1) {

	}	
	setCursorRowAndColumn(1,1);
	hd44780_writeString(message_init1);


	setCursorAtHome();
	delaymSec(1000);

	setCursorRowAndColumn(2,1);
	hd44780_writeString(message_init2);
	setCursorAtHome();
	delaymSec(1000);

	setCursorRowAndColumn(3,1);
	hd44780_writeString(message_init3);
	setCursorAtHome();
	delaymSec(1000);

	hideCursor();
	delaymSec(1000);

	showUnderlineCursor();
	delaymSec(1000);

	setBlinkCursor();
	delaymSec(1000);

	setCursorRowAndColumn(4,1);
	hd44780_writeString(message_init4);
	setCursorAtHome();
	delaymSec(1000);
}
