#include "lcd4d.h"

#include <stdlib.h>

#include "../../common/2d/2d.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/ioUtils.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/delay/cenDelay.h"

void initLcd4d(Lcd4d* lcd, OutputStream* outputStream, InputStream* inputStream, Buffer* inputBuffer) {
    lcd->outputStream = outputStream;
    lcd->inputStream = inputStream;    
    lcd->inputBuffer = inputBuffer;
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

#define LCD4D_STATIC_STANDARD_RESPONSE_DELAY            200
#define LCD4D_STATIC_LONG_RESPONSE_DELAY                1000


/**
 * Returns true if the response comes before the timeoutMilliSeconds, false else
 * @private
 */
bool waitLcdResponse(Lcd4d* lcd, int timeoutMilliSeconds, int charToReceive) {
    int counter = timeoutMilliSeconds;
    // while we don't get enough data
    while (getBufferElementsCount(lcd->inputBuffer) < charToReceive) {
        delaymSec(1);
        counter--;
        if (counter <= 0) {    
            appendString(getOutputStreamLogger(ERROR), "\nLCD TIME OUT:\n");
            return false;
        }
    }
    return true;
    /*
    appendStringAndDec(getOutputStreamLogger(ERROR), "\nELEMENT COUNT:", getBufferElementsCount(lcd->inputBuffer));
    appendStringAndDec(getOutputStreamLogger(ERROR), ", counter=", counter);    
    println(getOutputStreamLogger(ERROR));
    */
}

bool lcd4dIsAck(Lcd4d* lcd) {
    int result = readBinaryChar(lcd->inputStream);
    if (result == LCD4D_ACK) {
        copyInputToOutputStream(lcd->inputStream, getOutputStreamLogger(ERROR), NULL, COPY_ALL);
        return true;
    }
    appendString(getOutputStreamLogger(ERROR), "\nBAD ACK:");
    append(getOutputStreamLogger(ERROR), result);
    copyInputToOutputStream(lcd->inputStream, getOutputStreamLogger(ERROR), NULL, COPY_ALL);

    return false;
}

bool setAutoBaud(Lcd4d* lcd) {
    append(lcd->outputStream, LCD4D_AUTOBAUD_COMMAND);
    
    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    // Set AutoBaud don't return anything the first time
    return lcd4dIsAck(lcd);
}

bool setLcd4dBaudRate(Lcd4d* lcd, int baudRateType) {
    append(lcd->outputStream, LCD4D_NEW_BAUD_COMMAND);
    appendByte(lcd->outputStream, baudRateType);
    
    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

void getLcd4dVersionCommand(Lcd4d* lcd, Lcd4dVersion* version) {
    append(lcd->outputStream, LCD4D_VERSION_COMMAND);
    appendByte(lcd->outputStream, LCD4D_VERSION_OUTPUT_SERIAL_LCD);
    
    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 5);
    
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
    
    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 4);
    
    point->x = readBinaryWord(lcd->inputStream);    
    point->y = readBinaryWord(lcd->inputStream);
}


bool lcd4dClearScreen(Lcd4d* lcd) {
    append(lcd->outputStream, LCD4D_CLEAR_SCREEN_COMMAND);
    
    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dBacklight(Lcd4d* lcd, bool backlight) {
    append(lcd->outputStream, LCD4D_CONTROL_COMMAND);
    append(lcd->outputStream, LCD4D_BACKLIGHT_CONTROL);
    if (backlight) {
        append(lcd->outputStream, LCD4D_BACKLIGHT_ON);
    }
    else {
        append(lcd->outputStream, LCD4D_BACKLIGHT_OFF);
    }

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dDisplay(Lcd4d* lcd, bool display) {
    append(lcd->outputStream, LCD4D_CONTROL_COMMAND);
    append(lcd->outputStream, LCD4D_DISPLAY_CONTROL);
    if (display) {
        append(lcd->outputStream, LCD4D_DISPLAY_ON);
    }
    else {
        append(lcd->outputStream, LCD4D_DISPLAY_OFF);
    }

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dSetDisplayResolution(Lcd4d* lcd, unsigned int displayOrientation) {
    append(lcd->outputStream, LCD4D_CONTROL_COMMAND);
    append(lcd->outputStream, LCD4D_DISPLAY_ORIENTATION);

    append(lcd->outputStream, displayOrientation);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dTouchControl(Lcd4d* lcd, bool touchControl) {
    append(lcd->outputStream, LCD4D_CONTROL_COMMAND);
    append(lcd->outputStream, LCD4D_TOUCH_CONTROL);
    if (touchControl) {
        append(lcd->outputStream, LCD4D_TOUCH_ENABLE);
    }
    else {
        append(lcd->outputStream, LCD4D_TOUCH_DISABLE);
    }

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dVolume(Lcd4d* lcd, int volume) {
    append(lcd->outputStream, LCD4D_SET_VOLUME_COMMAND);
    append(lcd->outputStream, volume);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

// DRAW Functions

bool lcd4dDrawCircle(Lcd4d* lcd, int x, int y, int radius) {
    append(lcd->outputStream, LCD4D_DRAW_CIRCLE_COMMAND);

    appendWord(lcd->outputStream, x);
    appendWord(lcd->outputStream, y);
    appendWord(lcd->outputStream, radius);
    lcd4dAppendColor(lcd);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dDrawTriangle(Lcd4d* lcd, int x1, int y1, int x2, int y2, int x3, int y3) {
    append(lcd->outputStream, LCD4D_DRAW_TRIANGLE_COMMAND);

    appendWord(lcd->outputStream, x1);
    appendWord(lcd->outputStream, y1);
    appendWord(lcd->outputStream, x2);
    appendWord(lcd->outputStream, y2);
    appendWord(lcd->outputStream, x3);
    appendWord(lcd->outputStream, y3);

    lcd4dAppendColor(lcd);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dDrawLine(Lcd4d* lcd, int x1, int y1, int x2, int y2) {
    append(lcd->outputStream, LCD4D_DRAW_LINE_COMMAND);

    appendWord(lcd->outputStream, x1);
    appendWord(lcd->outputStream, y1);
    appendWord(lcd->outputStream, x2);
    appendWord(lcd->outputStream, y2);

    lcd4dAppendColor(lcd);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dDrawRectangle(Lcd4d* lcd, int x1, int y1, int x2, int y2) {
    append(lcd->outputStream, LCD4D_DRAW_RECTANGLE_COMMAND);

    appendWord(lcd->outputStream, x1);
    appendWord(lcd->outputStream, y1);
    appendWord(lcd->outputStream, x2);
    appendWord(lcd->outputStream, y2);

    lcd4dAppendColor(lcd);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dDrawEllipse(Lcd4d* lcd, int x, int y, int rx, int ry) {
    append(lcd->outputStream, LCD4D_DRAW_ELLIPSE_COMMAND);

    appendWord(lcd->outputStream, x);
    appendWord(lcd->outputStream, y);
    appendWord(lcd->outputStream, rx);
    appendWord(lcd->outputStream, ry);

    lcd4dAppendColor(lcd);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dDrawPixel(Lcd4d* lcd, int x, int y) {
    append(lcd->outputStream, LCD4D_DRAW_PIXEL_COMMAND);

    appendWord(lcd->outputStream, x);
    appendWord(lcd->outputStream, y);
    lcd4dAppendColor(lcd);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dSetPenType(Lcd4d* lcd, int penType) {
    append(lcd->outputStream, LCD4D_PEN_SIZE_COMMAND);

    appendByte(lcd->outputStream, penType);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

// TEXT COMMANDS

bool lcd4dSetFont(Lcd4d* lcd, int fontSize) {
    append(lcd->outputStream, LCD4D_SET_FONT_COMMAND);

    appendByte(lcd->outputStream, fontSize);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dDrawChar(Lcd4d* lcd, char c, int column, int row) {
    append(lcd->outputStream, LCD4D_DRAW_TEXT_COMMAND);
    append(lcd->outputStream, c);

    appendByte(lcd->outputStream, column);
    appendByte(lcd->outputStream, row);

    lcd4dAppendColor(lcd);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dDrawGraphicChar(Lcd4d* lcd, char c, int x, int y, int width, int height) {
    append(lcd->outputStream, LCD4D_DRAW_TEXT_GRAPHIC_COMMAND);
    append(lcd->outputStream, c);

    appendWord(lcd->outputStream, x);
    appendWord(lcd->outputStream, y);

    lcd4dAppendColor(lcd);

    appendByte(lcd->outputStream, width);
    appendByte(lcd->outputStream, height);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dDrawString(Lcd4d* lcd, int column, int row, int fontSize, char* text) {
    append(lcd->outputStream, LCD4D_DRAW_STRING_COMMAND);

    appendByte(lcd->outputStream, column);
    appendByte(lcd->outputStream, row);

    appendByte(lcd->outputStream, fontSize);
    lcd4dAppendColor(lcd);

    while (*text != '\0') {
        append(lcd->outputStream, *text++);
    }
    append(lcd->outputStream, '\0');

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dDrawGraphicString(Lcd4d* lcd, int x, int y, int fontSize, int width, int height, char* text) {
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

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

// TODO : Draw Buttons

// TOUCH SCREEN COMMANDS

void lcd4dWaitTouchAndGetTouchCoordinates(Lcd4d* lcd, int touchMode, Point* point) {
    append(lcd->outputStream, LCD4D_GET_TOUCH_COORDINATES_COMMAND);
    appendByte(lcd->outputStream, touchMode);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 4);

    point->x = readBinaryWord(lcd->inputStream);
    point->y = readBinaryWord(lcd->inputStream);
    copyInputToOutputStream(lcd->inputStream, getOutputStreamLogger(ERROR), NULL, COPY_ALL);
}

bool lcd4dSetTouchRegion(Lcd4d* lcd, int x1, int y1, int x2, int y2) {
    append(lcd->outputStream, LCD4D_DETECT_TOUCH_REGION_COMMAND);

    appendWord(lcd->outputStream, x1);
    appendWord(lcd->outputStream, y1);
    appendWord(lcd->outputStream, x2);
    appendWord(lcd->outputStream, y2);
    
    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dWaitUntilTouch(Lcd4d* lcd, unsigned int delayMilliSeconds) {
    append(lcd->outputStream, LCD4D_WAIT_UNTIL_TOUCH_COMMAND);

    appendWord(lcd->outputStream, delayMilliSeconds);

    bool touch = waitLcdResponse(lcd, delayMilliSeconds, 1);
    lcd4dIsAck(lcd);
    return touch;
}

// MEMORY CARD COMMAND

// -> Raw Mode


// -> Fat Mode

bool lcd4dInitializeMemoryCardFAT(Lcd4d* lcd) {
    append(lcd->outputStream, LCD4D_MEMORY_EXTENDED_COMMAND);
    // cmd
    append(lcd->outputStream, LCD4D_INITIALIZE_MEMORY_CARD_FAT_COMMAND);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dListDirectoryOfCardFAT(Lcd4d* lcd, char* fileNameToMatch, OutputStream* outputStream) {
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
            return true;
        }
        if (result == LCD4D_NACK) {
            return false;
        }
        append(outputStream, result);
    }        
    return true;
}

bool lcd4dEraseFileFromCardFAT(Lcd4d* lcd, char* fileName) {
    append(lcd->outputStream, LCD4D_MEMORY_EXTENDED_COMMAND);
    // cmd
    append(lcd->outputStream, LCD4D_ERASE_FILE_FAT_COMMAND);
    // fileName
    appendString(lcd->outputStream, fileName);
    // Terminator
    append(lcd->outputStream, 0);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dWriteFileToCardFAT(Lcd4d* lcd, int handshakingMode, int appendMode, int performanceMode, char* fileName, unsigned long fileSize, Buffer* buffer) {
    append(lcd->outputStream, LCD4D_MEMORY_EXTENDED_COMMAND);
    // cmd
    append(lcd->outputStream, LCD4D_WRITE_FILE_TO_CARD_FAT_COMMAND);
    
    append(lcd->outputStream, handshakingMode | appendMode | performanceMode);

    // fileName
    appendString(lcd->outputStream, fileName);
    // Terminator
    append(lcd->outputStream, 0);
    
    // Send size file : after sending size file, there is an ACK to manage
    appendDoubleWord(lcd->outputStream, fileSize);
    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    bool result = lcd4dIsAck(lcd);
    if (!result) {
        // if no ack, we do not send buffer content
        return false;
    }

    // Send data
    // TODO : Manage HandShaking Mode !!!
    unsigned long count = fileSize;
    while (count > 0) {
        char c = bufferReadChar(buffer);
        append(lcd->outputStream, c);
        count--;
    }

}

bool lcd4dScreenCopySaveToCardFAT(Lcd4d* lcd, int x, int y, int width, int height, char* fileName) {
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

    waitLcdResponse(lcd, LCD4D_STATIC_LONG_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dDisplayImageIconFromCardFAT(Lcd4d* lcd, int x, int y, char* fileName, unsigned long imagePos) {
    append(lcd->outputStream, LCD4D_MEMORY_EXTENDED_COMMAND);
    // cmd
    append(lcd->outputStream, LCD4D_DISPLAY_IMAGE_FAT_COMMAND);

    // fileName
    appendString(lcd->outputStream, fileName);
    // Terminator
    append(lcd->outputStream, 0);

    appendWord(lcd->outputStream, x);
    appendWord(lcd->outputStream, y);

    appendDoubleWord(lcd->outputStream, imagePos);

    waitLcdResponse(lcd, LCD4D_STATIC_LONG_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

bool lcd4dPlayAudioWAVFileFromCardFAT(Lcd4d* lcd, unsigned int option, char* fileName) {
    append(lcd->outputStream, LCD4D_MEMORY_EXTENDED_COMMAND);
    // cmd
    append(lcd->outputStream, LCD4D_PLAY_AUDIO_WAV_FROM_CARD_COMMAND);
    // option
    append(lcd->outputStream, option);
    // fileName
    appendString(lcd->outputStream, fileName);
    // Terminator
    append(lcd->outputStream, 0);

    waitLcdResponse(lcd, LCD4D_STATIC_STANDARD_RESPONSE_DELAY, 1);
    return lcd4dIsAck(lcd);
}

