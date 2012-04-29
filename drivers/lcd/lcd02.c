#include <I2C.h>
#include <stdlib.h>
#include <string.h>

#include "lcd02.h"

void lcd02_setCursorAtHome (void) {
    lcd02_sendCommand(1);
}

void lcd02_sendCommand (char command) {
  
  IdleI2C();					//attend que le bus soit libre
  StartI2C();

/* Wait till Start sequence is completed */
  while(I2CCONbits.SEN);

  MasterWriteI2C(LCD02_ADDRESS_WRITE);			// adresse I2C
  IdleI2C();

  MasterWriteI2C(LCD02_COMMAND_REGISTER);			// registre de commande
  IdleI2C();

  // commande
  MasterWriteI2C(command);
  IdleI2C();

  StopI2C();
}

void internalSendCommand1(unsigned command, unsigned char value1) {
  //attend que le bus soit libre
  IdleI2C();					
  StartI2C();

  /* Wait till Start sequence is completed */
  while(I2CCONbits.SEN);

  // adresse I2C
  MasterWriteI2C(LCD02_ADDRESS_WRITE);			
  IdleI2C();

  // registre de commande
  MasterWriteI2C(LCD02_COMMAND_REGISTER);			
  IdleI2C();

  // commande
  MasterWriteI2C(command);
  IdleI2C();

  // data
  MasterWriteI2C(value1);			
  IdleI2C();

  StopI2C();
}

void internalSendCommand2(unsigned command, unsigned char value1, unsigned char value2) {
  IdleI2C();					//attend que le bus soit libre
  StartI2C();

  /* Wait till Start sequence is completed */
  while(I2CCONbits.SEN);

  MasterWriteI2C(LCD02_ADDRESS_WRITE);			// adresse I2C
  IdleI2C();

  MasterWriteI2C(LCD02_COMMAND_REGISTER);			// registre de commande
  IdleI2C();

  MasterWriteI2C(command);			// commande
  IdleI2C();

  MasterWriteI2C(value1);			// commande
  IdleI2C();

  MasterWriteI2C(value2);			// commande
  IdleI2C();

  StopI2C();
}

void lcd02_setCursorPosition (char position) {
	internalSendCommand1(2, position);
}

void lcd02_setCursorRowAndColumn(char row, char column) {
	internalSendCommand2(3, row, column);
}

void lcd02_hideCursor (void){
  lcd02_sendCommand(4);
}

void lcd02_showUnderlineCursor(void){
   lcd02_sendCommand(5);
}

void lcd02_setBlinkCursor(void){
   lcd02_sendCommand(6);
}

void lcd02_backSpaceCursor (void){
   lcd02_sendCommand(8);
}

void lcd02_setBacklight(unsigned char enabled) {
	if (enabled) {
		lcd02_sendCommand(BACKLIGHT_ON);
	}
	else {
		lcd02_sendCommand(BACKLIGHT_OFF);
	}
}

void lcd02_tabCursor (void){
    lcd02_sendCommand(9);
}

void lcd02_smartLineCursor (void){
   lcd02_sendCommand(10);
}

void lcd02_verticalTabCursor (void){
   lcd02_sendCommand(11);
}

void lcd02_clearScreen (void){
  lcd02_sendCommand(12);
}

void lcd02_carriageReturnCursor (void){
  lcd02_sendCommand(13);
}

void lcd02_clearColumnCursor (void){
  lcd02_sendCommand(17);
}

void lcd02_setTabulationSize (char tabulationSize) {
  internalSendCommand1(18, tabulationSize);
}

void lcd02_writeChar (char c) {
  // the command to write a char is the same as writing command but with limited range of char to only non binary character
 lcd02_sendCommand(c);
}

unsigned int getLCD02SoftwareRevision (void){
  unsigned int version;
 
  IdleI2C();

  StartI2C();
  /* Wait till Start sequence is completed */
  while(I2CCONbits.SEN);

  MasterWriteI2C(LCD02_ADDRESS_WRITE);		//adddresse I2C de la carte
  IdleI2C();

  MasterWriteI2C(3);		//registre de version
  IdleI2C();
  
  StopI2C();
  IdleI2C();
  StartI2C();
  /* Wait till Start sequence is completed */
  while(I2CCONbits.SEN)
  //adddresse I2C de la carte
  MasterWriteI2C(LCD02_ADDRESS_READ);		
  IdleI2C();
  //registre de version
  version = MasterReadI2C();		
  IdleI2C();

  return (version);
}

unsigned int isLCD02DeviceOk ( void ) {
	return getLCD02SoftwareRevision() < 255;
}

void initLCD02 ( void ) {
	lcd02_clearScreen();
	lcd02_setBacklight(1);
}

void stopLCD02 ( void ) {
	// Disable backlight when it will be managed
	lcd02_setBacklight(0);
}

const char* getLCD02DeviceName( void ) {
	return "LCD02";
}

DeviceDescriptor getLCD02DeviceDescriptor() {
	DeviceDescriptor result;
	result.deviceInit = &initLCD02;
	result.deviceShutDown = &stopLCD02;
	result.deviceIsOk = &isLCD02DeviceOk;
	result.deviceGetSoftwareRevision = &getLCD02SoftwareRevision;
	result.deviceGetName = &getLCD02DeviceName;
	result.enabled = 1;

	return result;
}
