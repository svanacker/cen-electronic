#include "lcd4d.h"

#include "../../common/2d/2d.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/delay/delay30F.h"

void initLcd4d(Lcd4d* lcd, OutputStream* outputStream, InputStream* inputStream) {
	lcd->outputStream = outputStream;
	lcd->inputStream = inputStream;	
	setLcd4dColor(lcd, 255, 255, 255);
}

/**
 * 2 bytes (16 bits) define the background colour in RGB format:
 * R4R3R2R1R0G5G4G3G2G1G0B4B3B2B1B0 where: 
 * msb : R4R3R2R1R0G5G4G3
 * lsb : G2G1G0B4B3B2B1B0
 */
int getLcd4dColor(unsigned char r, unsigned char g, unsigned char b) {
	// Red is on the first 
	return ((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F);
}

void setLcd4dColor(Lcd4d* lcd, unsigned char r, unsigned char g, unsigned char b) {
	int color = getLcd4dColor(r, g, b);
	lcd->color = color;
}

void lcd4dAppendColor(Lcd4d* lcd) {
	appendWord(lcd->outputStream, lcd->color);
}

#define LCD4D_STATIC_RESPONSE_DELAY				10
#define LCD4D_STATIC_DELAY_BY_RESPONSE_CHAR		50


/**
 * @private
 */
void waitLcdResponse(Lcd4d* lcd, int charToReceive) {
	int counter = LCD4D_STATIC_RESPONSE_DELAY + LCD4D_STATIC_DELAY_BY_RESPONSE_CHAR * charToReceive;
	while (!lcd->inputStream->availableData(lcd->inputStream)) {
		delaymSec(1);
		counter--;
		if (counter == 0) {	
			appendString(getOutputStreamLogger(ERROR), "\nLCD TIME OUT:\n");
			break;
		}
	}
}

BOOL lcd4dIsAck(Lcd4d* lcd) {
	int result = readBinaryChar(lcd->inputStream);
	if (result == LCD4D_ACK) {
		return TRUE;
	}
	appendString(getOutputStreamLogger(ERROR), "\nBAD ACK:");
	append(getOutputStreamLogger(ERROR), result);
	return FALSE;
}

BOOL setAutoBaud(Lcd4d* lcd) {
	append(lcd->outputStream, LCD4D_AUTOBAUD_COMMAND);
	
	waitLcdResponse(lcd, 1);
	// Set AutoBaud don't return anything the first time
	return lcd4dIsAck(lcd);
	// return TRUE;
}

BOOL setLcd4dBaudRate(Lcd4d* lcd, int baudRateType) {
	append(lcd->outputStream, LCD4D_NEW_BAUD_COMMAND);
	appendByte(lcd->outputStream, baudRateType);
	
	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

void getLcd4dVersionCommand(Lcd4d* lcd, Lcd4dVersion* version) {
	append(lcd->outputStream, LCD4D_VERSION_COMMAND);
	appendByte(lcd->outputStream, LCD4D_VERSION_OUTPUT_SERIAL_LCD);
	
	waitLcdResponse(lcd, 5);
	
	version->deviceType = readBinaryChar(lcd->inputStream);
	version->hardwareRevision = readBinaryChar(lcd->inputStream);
	version->firmwareRevision = readBinaryChar(lcd->inputStream);
	version->horizontalResolution = readBinaryChar(lcd->inputStream);
	version->verticalResolution = readBinaryChar(lcd->inputStream);
}

void lcd4dPrintVersion(OutputStream* outputStream, Lcd4dVersion* version) {
	appendStringAndDec(outputStream, "\ndeviceType=", version->deviceType);
	appendStringAndDec(outputStream, "\nhardwareRevision=", version->hardwareRevision);
	appendStringAndDec(outputStream, "\nfirmwareRevision=", version->firmwareRevision);
	appendStringAndDec(outputStream, "\nhorizontalResolution=", version->horizontalResolution);
	appendStringAndDec(outputStream, "\nverticalResolution=", version->verticalResolution);
	int verticalResolution;
	println(outputStream);
}

// TODO : Doesn't work !!!!
void getLcd4dDisplayResolution(Lcd4d* lcd, Point* point) {
	append(lcd->outputStream, LCD4D_SET_DISPLAY_RESOLUTION_COMMAND);
	
	waitLcdResponse(lcd, 4);
	
	point->x = readBinaryWord(lcd->inputStream);	
	point->y = readBinaryWord(lcd->inputStream);
}


BOOL lcd4dClearScreen(Lcd4d* lcd) {
	append(lcd->outputStream, LCD4D_CLEAR_SCREEN_COMMAND);
	
	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dBacklight(Lcd4d* lcd, BOOL backlight) {
	append(lcd->outputStream, LCD4D_CONTROL_COMMAND);
	append(lcd->outputStream, LCD4D_BACKLIGHT_CONTROL);
	if (backlight) {
		append(lcd->outputStream, LCD4D_BACKLIGHT_ON);
	}
	else {
		append(lcd->outputStream, LCD4D_BACKLIGHT_OFF);
	}

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dDisplay(Lcd4d* lcd, BOOL display) {
	append(lcd->outputStream, LCD4D_CONTROL_COMMAND);
	append(lcd->outputStream, LCD4D_DISPLAY_CONTROL);
	if (display) {
		append(lcd->outputStream, LCD4D_DISPLAY_ON);
	}
	else {
		append(lcd->outputStream, LCD4D_DISPLAY_OFF);
	}

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dSetDisplayResolution(Lcd4d* lcd, unsigned int displayOrientation) {
	append(lcd->outputStream, LCD4D_CONTROL_COMMAND);
	append(lcd->outputStream, LCD4D_DISPLAY_ORIENTATION);

	append(lcd->outputStream, displayOrientation);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dTouchControl(Lcd4d* lcd, BOOL touchControl) {
	append(lcd->outputStream, LCD4D_CONTROL_COMMAND);
	append(lcd->outputStream, LCD4D_TOUCH_CONTROL);
	if (touchControl) {
		append(lcd->outputStream, LCD4D_TOUCH_ENABLE);
	}
	else {
		append(lcd->outputStream, LCD4D_TOUCH_DISABLE);
	}

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dVolume(Lcd4d* lcd, int volume) {
	append(lcd->outputStream, LCD4D_SET_VOLUME_COMMAND);
	append(lcd->outputStream, volume);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

// DRAW Functions

BOOL lcd4dDrawCircle(Lcd4d* lcd, int x, int y, int radius) {
	append(lcd->outputStream, LCD4D_DRAW_CIRCLE_COMMAND);

	appendWord(lcd->outputStream, x);
	appendWord(lcd->outputStream, y);
	appendWord(lcd->outputStream, radius);
	lcd4dAppendColor(lcd);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dDrawTriangle(Lcd4d* lcd, int x1, int y1, int x2, int y2, int x3, int y3) {
	append(lcd->outputStream, LCD4D_DRAW_TRIANGLE_COMMAND);

	appendWord(lcd->outputStream, x1);
	appendWord(lcd->outputStream, y1);
	appendWord(lcd->outputStream, x2);
	appendWord(lcd->outputStream, y2);
	appendWord(lcd->outputStream, x3);
	appendWord(lcd->outputStream, y3);

	lcd4dAppendColor(lcd);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dDrawLine(Lcd4d* lcd, int x1, int y1, int x2, int y2) {
	append(lcd->outputStream, LCD4D_DRAW_LINE_COMMAND);

	appendWord(lcd->outputStream, x1);
	appendWord(lcd->outputStream, y1);
	appendWord(lcd->outputStream, x2);
	appendWord(lcd->outputStream, y2);

	lcd4dAppendColor(lcd);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dDrawRectangle(Lcd4d* lcd, int x1, int y1, int x2, int y2) {
	append(lcd->outputStream, LCD4D_DRAW_RECTANGLE_COMMAND);

	appendWord(lcd->outputStream, x1);
	appendWord(lcd->outputStream, y1);
	appendWord(lcd->outputStream, x2);
	appendWord(lcd->outputStream, y2);

	lcd4dAppendColor(lcd);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dDrawEllipse(Lcd4d* lcd, int x, int y, int rx, int ry) {
	append(lcd->outputStream, LCD4D_DRAW_ELLIPSE_COMMAND);

	appendWord(lcd->outputStream, x);
	appendWord(lcd->outputStream, y);
	appendWord(lcd->outputStream, rx);
	appendWord(lcd->outputStream, ry);

	lcd4dAppendColor(lcd);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dDrawPixel(Lcd4d* lcd, int x, int y) {
	append(lcd->outputStream, LCD4D_DRAW_PIXEL_COMMAND);

	appendWord(lcd->outputStream, x);
	appendWord(lcd->outputStream, y);
	lcd4dAppendColor(lcd);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dSetPenType(Lcd4d* lcd, int penType) {
	append(lcd->outputStream, LCD4D_PEN_SIZE_COMMAND);

	appendByte(lcd->outputStream, penType);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

// TEXT COMMANDS

BOOL lcd4dSetFont(Lcd4d* lcd, int fontSize) {
	append(lcd->outputStream, LCD4D_SET_FONT_COMMAND);

	appendByte(lcd->outputStream, fontSize);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dDrawChar(Lcd4d* lcd, char c, int column, int row) {
	append(lcd->outputStream, LCD4D_DRAW_TEXT_COMMAND);
	append(lcd->outputStream, c);

	appendByte(lcd->outputStream, column);
	appendByte(lcd->outputStream, row);

	lcd4dAppendColor(lcd);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dDrawGraphicChar(Lcd4d* lcd, char c, int x, int y, int width, int height) {
	append(lcd->outputStream, LCD4D_DRAW_TEXT_GRAPHIC_COMMAND);
	append(lcd->outputStream, c);

	appendWord(lcd->outputStream, x);
	appendWord(lcd->outputStream, y);

	lcd4dAppendColor(lcd);

	appendByte(lcd->outputStream, width);
	appendByte(lcd->outputStream, height);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dDrawString(Lcd4d* lcd, int column, int row, int fontSize, char* text) {
	append(lcd->outputStream, LCD4D_DRAW_STRING_COMMAND);

	appendByte(lcd->outputStream, column);
	appendByte(lcd->outputStream, row);

	appendByte(lcd->outputStream, fontSize);
	lcd4dAppendColor(lcd);

    while (*text != '\0') {
        append(lcd->outputStream, *text++);
    }
	append(lcd->outputStream, '\0');

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dDrawGraphicString(Lcd4d* lcd, int x, int y, int fontSize, int width, int height, char* text) {
	append(lcd->outputStream, LCD4D_DRAW_STRING_GRAPHIC_COMMAND);

	appendWord(lcd->outputStream, x);
	appendWord(lcd->outputStream, y);

	appendByte(lcd->outputStream, fontSize);
	lcd4dAppendColor(lcd);

	appendByte(lcd->outputStream, width);
	appendByte(lcd->outputStream, height);

    while (*text != '\0') {
        append(lcd->outputStream, *text++);
    }
	append(lcd->outputStream, '\0');

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

// TODO : Draw Buttons

// TOUCH SCREEN COMMANDS

void lcd4dWaitTouchAndGetTouchCoordinates(Lcd4d* lcd, int touchMode, Point* point) {
	append(lcd->outputStream, LCD4D_GET_TOUCH_COORDINATES_COMMAND);
	appendByte(lcd->outputStream, touchMode);

	waitLcdResponse(lcd, 4);

	point->x = readBinaryWord(lcd->inputStream);
	point->y = readBinaryWord(lcd->inputStream);
}

BOOL lcd4dSetTouchRegion(Lcd4d* lcd, int x1, int y1, int x2, int y2) {
	append(lcd->outputStream, LCD4D_DETECT_TOUCH_REGION_COMMAND);

	appendWord(lcd->outputStream, x1);
	appendWord(lcd->outputStream, y1);
	appendWord(lcd->outputStream, x2);
	appendWord(lcd->outputStream, y2);
	
	// TODO : Wait	
	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

// MEMORY CARD COMMAND

// -> Raw Mode


// -> Fat Mode

BOOL lcd4dInitializeMemoryCardFAT(Lcd4d* lcd) {
	append(lcd->outputStream, LCD4D_MEMORY_EXTENDED_COMMAND);
	// cmd
	append(lcd->outputStream, LCD4D_INITIALIZE_MEMORY_CARD_FAT_COMMAND);

	waitLcdResponse(lcd, 20);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dListDirectoryOfCardFAT(Lcd4d* lcd, char* fileNameToMatch, OutputStream* outputStream) {
	append(lcd->outputStream, LCD4D_MEMORY_EXTENDED_COMMAND);
	// cmd
	append(lcd->outputStream, LCD4D_LIST_DIRECTORY_OF_CARD);
	
	// fileName
	appendString(lcd->outputStream, fileNameToMatch);
	// Terminator
	append(lcd->outputStream, 0);
	
	while (1) {
		if (!lcd->inputStream->availableData(lcd->inputStream)) {
			continue;
		}
		
		int result = readBinaryChar(lcd->inputStream);
		if (result == LCD4D_ACK) {
			return TRUE;
		}
		if (result == LCD4D_NACK) {
			return FALSE;
		}
		append(outputStream, result);
	}		
	return TRUE;
}

BOOL lcd4dScreenCopySaveToCardFAT(Lcd4d* lcd, int x, int y, int width, int height, char* fileName) {
	append(lcd->outputStream, LCD4D_MEMORY_EXTENDED_COMMAND);
	// cmd
	append(lcd->outputStream, LCD4D_SCREEN_COPY_FAT_COMMAND);
	appendWord(lcd->outputStream, x);
	appendWord(lcd->outputStream, y);
	appendWord(lcd->outputStream, width);
	appendWord(lcd->outputStream, height);
	// fileName
	appendString(lcd->outputStream, fileName);
	// Terminator
	append(lcd->outputStream, 0);

	waitLcdResponse(lcd, 100);
	return lcd4dIsAck(lcd);
}

BOOL lcd4dPlayAudioWAVFileFromCardFAT(Lcd4d* lcd, unsigned int option, char* fileName) {
	append(lcd->outputStream, LCD4D_MEMORY_EXTENDED_COMMAND);
	// cmd
	append(lcd->outputStream, LCD4D_PLAY_AUDIO_WAV_FROM_CARD_COMMAND);
	// option
	append(lcd->outputStream, option);
	// fileName
	appendString(lcd->outputStream, fileName);
	// Terminator
	append(lcd->outputStream, 0);

	waitLcdResponse(lcd, 1);
	return lcd4dIsAck(lcd);
}

