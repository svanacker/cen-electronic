#include "lcd4d.h"

#include "../../common/2d/2d.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

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

/**
 * @private
 */
void waitLcdResponse() {

}

BOOL setAutoBaud(Lcd4d* lcd) {
	append(lcd->outputStream, LCD4D_AUTOBAUD_COMMAND);
	
	/*
	waitLcdResponse();

	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
	*/
	return TRUE;
}

BOOL setLcd4dBaudRate(Lcd4d* lcd, int baudRateType) {
	append(lcd->outputStream, LCD4D_NEW_BAUD_COMMAND);
	appendByte(lcd->outputStream, baudRateType);
	
	/*
	waitLcdResponse();

	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
	*/
	return TRUE;
}

void getLcd4dVersionCommand(Lcd4d* lcd, Lcd4dVersion* version) {
	append(lcd->outputStream, LCD4D_VERSION_COMMAND);
	appendByte(lcd->outputStream, LCD4D_VERSION_OUTPUT_SERIAL_LCD);
	
	waitLcdResponse();
	
	version->deviceType = readHex2(lcd->inputStream);
	version->hardwareRevision = readHex2(lcd->inputStream);
	version->firmwareRevision = readHex2(lcd->inputStream);
	version->horizontalResolution = readHex2(lcd->inputStream);
	version->verticalResolution = readHex2(lcd->inputStream);
}

void getLcd4dDisplayResolution(Lcd4d* lcd, Point* point) {
	append(lcd->outputStream, LCD4D_SET_DISPLAY_RESOLUTION_COMMAND);
	
	/*
	waitLcdResponse();
	
	point->x = readHex4(lcd->inputStream);	
	point->y = readHex4(lcd->inputStream);
	*/
}

BOOL lcd4dClearScreen(Lcd4d* lcd) {
	append(lcd->outputStream, LCD4D_CLEAR_SCREEN_COMMAND);
	
	// waitLcdResponse();

	// int result = readHex2(lcd->inputStream);
	// return (result == LCD4D_ACK);
	return TRUE;
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

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
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

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
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

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
}

BOOL lcd4dVolume(Lcd4d* lcd, int volume) {
	append(lcd->outputStream, LCD4D_SET_VOLUME_COMMAND);
	append(lcd->outputStream, volume);

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
}

// DRAW Functions

BOOL lcd4dDrawCircle(Lcd4d* lcd, int x, int y, int radius) {
	append(lcd->outputStream, LCD4D_DRAW_CIRCLE_COMMAND);

	appendWord(lcd->outputStream, x);
	appendWord(lcd->outputStream, y);
	appendWord(lcd->outputStream, radius);
	lcd4dAppendColor(lcd);

	/*
	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
	*/
	return TRUE;
}

BOOL lcd4dDrawTriangle(Lcd4d* lcd, int x1, int y1, int x2, int y2, int x3, int y3) {
	append(lcd->outputStream, LCD4D_DRAW_TRIANGLE_COMMAND);

	appendWord(lcd->outputStream, x1);
	appendWord(lcd->outputStream, y1);
	appendWord(lcd->outputStream, x2);
	appendWord(lcd->outputStream, y2);
	appendWord(lcd->outputStream, x3);
	appendWord(lcd->outputStream, y3);

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
}

BOOL lcd4dDrawLine(Lcd4d* lcd, int x1, int y1, int x2, int y2) {
	append(lcd->outputStream, LCD4D_DRAW_LINE_COMMAND);

	appendWord(lcd->outputStream, x1);
	appendWord(lcd->outputStream, y1);
	appendWord(lcd->outputStream, x2);
	appendWord(lcd->outputStream, y2);
	lcd4dAppendColor(lcd);

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
}

BOOL lcd4dDrawRectangle(Lcd4d* lcd, int x1, int y1, int x2, int y2) {
	append(lcd->outputStream, LCD4D_DRAW_RECTANGLE_COMMAND);

	appendWord(lcd->outputStream, x1);
	appendWord(lcd->outputStream, y1);
	appendWord(lcd->outputStream, x2);
	appendWord(lcd->outputStream, y2);
	lcd4dAppendColor(lcd);

	/*
	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
	*/
	return TRUE;
}

BOOL lcd4dDrawEllipse(Lcd4d* lcd, int x, int y, int rx, int ry) {
	append(lcd->outputStream, LCD4D_DRAW_ELLIPSE_COMMAND);

	appendWord(lcd->outputStream, x);
	appendWord(lcd->outputStream, y);
	appendWord(lcd->outputStream, rx);
	appendWord(lcd->outputStream, ry);
	lcd4dAppendColor(lcd);

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
}

BOOL lcd4dDrawPixel(Lcd4d* lcd, int x, int y) {
	append(lcd->outputStream, LCD4D_DRAW_PIXEL_COMMAND);

	appendWord(lcd->outputStream, x);
	appendWord(lcd->outputStream, y);
	lcd4dAppendColor(lcd);

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
}

BOOL lcd4dSetPenType(Lcd4d* lcd, int penType) {
	append(lcd->outputStream, LCD4D_PEN_SIZE_COMMAND);

	appendByte(lcd->outputStream, penType);

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
}

// TEXT COMMANDS

BOOL lcd4dSetFont(Lcd4d* lcd, int fontSize) {
	append(lcd->outputStream, LCD4D_SET_FONT_COMMAND);

	appendByte(lcd->outputStream, fontSize);

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
}

BOOL lcd4dDrawChar(Lcd4d* lcd, char c, int column, int row) {
	append(lcd->outputStream, LCD4D_DRAW_TEXT_COMMAND);
	append(lcd->outputStream, c);

	appendByte(lcd->outputStream, column);
	appendByte(lcd->outputStream, row);

	lcd4dAppendColor(lcd);

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
}

BOOL lcd4dDrawGraphicChar(Lcd4d* lcd, char c, int x, int y, int width, int height) {
	append(lcd->outputStream, LCD4D_DRAW_TEXT_GRAPHIC_COMMAND);
	append(lcd->outputStream, c);

	appendWord(lcd->outputStream, x);
	appendWord(lcd->outputStream, y);

	lcd4dAppendColor(lcd);

	appendByte(lcd->outputStream, width);
	appendByte(lcd->outputStream, height);

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
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

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
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

	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
}

// TODO : Draw Buttons

// TOUCH SCREEN COMMANDS

void lcd4dWaitTouchAndGetTouchCoordinates(Lcd4d* lcd, int touchMode, Point* point) {
	append(lcd->outputStream, LCD4D_GET_TOUCH_COORDINATES_COMMAND);

	// TODO : Wait	
	waitLcdResponse();

	point->x = readHex4(lcd->inputStream);
	point->y = readHex4(lcd->inputStream);
}

BOOL lcd4dSetTouchRegion(Lcd4d* lcd, int x1, int y1, int x2, int y2) {
	append(lcd->outputStream, LCD4D_DETECT_TOUCH_REGION_COMMAND);

	appendByte(lcd->outputStream, x1);
	appendByte(lcd->outputStream, y1);
	appendByte(lcd->outputStream, x2);
	appendByte(lcd->outputStream, y2);
	
	// TODO : Wait	
	waitLcdResponse();
	int result = readHex2(lcd->inputStream);
	return (result == LCD4D_ACK);
}

// MEMORY CARD COMMAND

