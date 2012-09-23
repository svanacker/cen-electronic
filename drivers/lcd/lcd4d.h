/**
 * Encapsulation of PICASA SGC Command
 */

#include "../../common/2d/2d.h"
#include "../../common/commons.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"

/**
 * Define all datas relating to a Lcd 4d SGC Object.
 */
typedef struct {
	// OutputStream (serial) used to send command
	OutputStream* outputStream;
	// InputStream (serial) used to read data
	InputStream* inputStream;
} Lcd4d;

/**
 * Define the structure of LCD version.
 */
typedef struct Lcd4dVersion {
	int deviceType;
	int hardwareRevision;
	int firmwareRevision;
	int horizontalResolution;
	int verticalResolution;
} Lcd4dVersion;

// ALL COMMANDS

#define		LCD4D_ACK								0x06
#define		LCD4D_NACK								0x15


// GENERAL COMMANDS

#define 	LCD4D_AUTOBAUD_COMMAND					'U'


#define 	LCD4D_NEW_BAUD_COMMAND					'Q'
#define 	LCD4D_NEW_BAUD_9600						0x06
#define		LCD4D_NEW_BAUD_115200					0x0D

#define		LCD4D_VERSION_COMMAND					'V'
#define		LCD4D_VERSION_OUTPUT_SERIAL_ONLY		0x00
#define		LCD4D_VERSION_OUTPUT_SERIAL_LCD			0x01
// TODO : Response of V

#define		LCD4D_SET_DISPLAY_RESOLUTION_COMMAND	'd'

#define		LCD4D_CLEAR_SCREEN_COMMAND				'E'

// Control
#define		LCD4D_CONTROL_COMMAND					'Y'

#define		LCD4D_BACKLIGHT_CONTROL					0x00
#define		LCD4D_BACKLIGHT_OFF						0x00
#define		LCD4D_BACKLIGHT_ON						0x01

#define		LCD4D_DISPLAY_CONTROL					0x01
#define		LCD4D_DISPLAY_OFF						0x00
#define		LCD4D_DISPLAY_ON						0x01

#define		LCD4D_CONTRAST_ADJUST					0x02

#define		LCD4D_POWER_UP_SHUTDOWN					0x03
#define		LCD4D_DISPLAY_SHUTDOWN					0x00
#define		LCD4D_DISPLAY_POWER_UP					0x01

#define		LCD4D_DISPLAY_ORIENTATION				0x04
#define		LCD4D_ORIENTATION_90					0x01
#define		LCD4D_ORIENTATION_270					0x02
#define		LCD4D_NATIVE_ORIENTATION				0x03
#define		LCD4D_ORIENTATION_180					0x04

#define		LCD4D_TOUCH_CONTROL						0x05
#define		LCD4D_TOUCH_ENABLE						0x00
#define		LCD4D_TOUCH_DISABLE						0x01
#define		LCD4D_TOUCH_RESET_ACTIVE_REGION			0x02

#define		LCD4D_IMAGE_FORMAT						0x06
// TODO

#define		LCD4D_PROTECT_FAT						0x08
#define		LCD4D_PROTECT_ON						0x00
#define		LCD4D_PROTECT_OFF						0x01

#define		LCD4D_DISPLAY_PAGE_SELECT				0x09

#define		LCD4D_READ_PAGE_SELECT					0x0A

#define		LCD4D_WRITE_PAGE_SELECT					0x0B

#define		LCD4D_SCREEN_RESOLUTION					0x0C
#define		LCD4D_RESOLUTION_320_240				0x00
#define		LCD4D_RESOLUTION_640_480				0x01
//#define		LCD4D_RESOLUTION_CUSTOM					0x02

#define		LCD4D_SCREEN_SAVER_STARTUP_DELAY		0x0D

#define		LCD4D_SCREEN_SAVER_NEXT_LINE_DELAY		0x0E


#define		LCD4D_SET_VOLUME_COMMAND				'v'
#define		LCD4D_VOLUME_MUTE						0x00
#define		LCD4D_VOLUME_DOWN_8						0x01
#define		LCD4D_VOLUME_DOWN						0x03


#define		LCD4D_VOLUME_MINIMUM					0x08
#define		LCD4D_VOLUME_MAXIMUM					0x7F
#define		LCD4D_VOLUME_UP							0xFD
#define		LCD4D_VOLUME_UP_8						0xFE
#define		LCD4D_VOLUME_MUTE_OFF					0xFF

// GRAPHICS COMMAND

#define		LCD4D_DRAW_CIRCLE_COMMAND				'C'
#define		LCD4D_DRAW_TRIANGLE_COMMAND				'G'
#define		LCD4D_DRAW_LINE_COMMAND					'L'
#define		LCD4D_DRAW_POLYGON_COMMAND				'g'
#define		LCD4D_DRAW_RECTANGLE_COMMAND			'r'
#define		LCD4D_DRAW_ELLIPSE_COMMAND				'e'

#define		LCD4D_DRAW_PIXEL_COMMAND				'P'

#define		LCD4D_PEN_SIZE_COMMAND					'p'
#define		LCD4D_PEN_SIZE_DRAW_SOLID				0x00
#define		LCD4D_PEN_SIZE_DRAW_WIRE_FRAME			0x01

// TEXT COMMAND

#define 	LCD4D_SET_FONT_COMMAND					'F'
#define		LCD4D_FONT_SMALL						0x00
#define		LCD4D_FONT_MEDIUM						0x01
#define		LCD4D_FONT_LARGE						0x02
#define		LCD4D_FONT_LARGEST						0x03

#define 	LCD4D_SET_TRANSPARENT_OPAQUE_COMMAND	'O'
#define		LCD4D_TEXT_TRANSPARENT					0x00
#define		LCD4D_TEXT_OPAQUE						0x01

#define		LCD4D_DRAW_TEXT_COMMAND					'T'

#define		LCD4D_DRAW_TEXT_GRAPHIC_COMMAND			't'

#define		LCD4D_DRAW_STRING_COMMAND				's'
#define		LCD4D_DRAW_STRING_GRAPHIC_COMMAND		'S'

#define		LCD4D_DRAW_TEXT_BUTTON_COMMAND			'b'
#define		LCD4D_BUTTON_DOWN						0x00
#define		LCD4D_BUTTON_UP							0x01

// TOUCH SCREEN COMMAND
#define		LCD4D_GET_TOUCH_COORDINATES_COMMAND		'o'
#define		LCD4D_TOUCH_WAIT_UNTIL_ANY_TOUCH		0x00
#define		LCD4D_TOUCH_WAIT_PRESS					0x01
#define		LCD4D_TOUCH_WAIT_RELEASE				0x02
#define		LCD4D_TOUCH_WAIT_MOVING					0x03
#define		LCD4D_TOUCH_GET_STATUS					0x04
#define		LCD4D_TOUCH_GET_COORDINATES				0x05

#define		LCD4D_TOUCH_RESPONSE_NO_TOUCH			0x00
#define		LCD4D_TOUCH_RESPONSE_TOUCH_PRESS		0x01
#define		LCD4D_TOUCH_RESPONSE_TOUCH_RELEASE		0x02
#define		LCD4D_TOUCH_RESPONSE_TOUCH_MOVING		0x03

#define		LCD4D_WAIT_UNTIL_TOUCH_COMMAND			'w'

#define		LCD4D_DETECT_TOUCH_REGION_COMMAND		'u'

// SD MEMORY CARD COMMANDS
#define		LCD4D_MEMORY_EXTENDED_COMMAND			'@'

#define		LCD4D_MEMORY_INIT_CARD					'i'

#define		LCD4D_MEMORY_SCREEN_COPY				'C'
//TODO

// SD FAT COMMAND
#define		LCD4D_READ_FILE_COMMAND					'a'

/**
 * Init the Lcd4d structure with his properties.
 */
void initLcd4d(Lcd4d* lcd, OutputStream* outputStream, InputStream* inputStream);
 
/**
 * Set the autobaud to the lcd.
 */
BOOL setAutoBaud(Lcd4d* lcd);

/**
 * Change the rate of the uart.
 */
BOOL setLcd4dBaudRate(Lcd4d* lcd, int baudRateType);

/**
 * Get the version of the Lcd into the version structure.
 */
void getLcd4dVersionCommand(Lcd4d* lcd, Lcd4dVersion* version);

/**
 * Get the display resolution and set it to the point parameter.
 */
void getLcd4dDisplayResolution(Lcd4d* lcd, Point* point);

/** 
 * Clear Screen.
 */
BOOL lcd4dClearScreen(Lcd4d* lcd);

/**
 * Enable or disable the backlight.
 */
BOOL lcd4dBacklight(Lcd4d* lcd, BOOL backlight);

/**
 * Enable or not the display.
 */
BOOL lcd4dDisplay(Lcd4d* lcd, BOOL display);

/**
 * Enable or not the touch control.
 */
BOOL lcd4dTouchControl(Lcd4d* lcd, BOOL touchControl);

/** 
 * Set the volume of the lcd.
 */
BOOL lcd4dVolume(Lcd4d* lcd, int volume);

// DRAW Functions

/**
 * Draw a circle.
 */
BOOL lcd4dDrawCircle(Lcd4d* lcd, int x, int y, int radius, int color);

/**
 * Draw a triangle.
 */
BOOL lcd4dDrawTriangle(Lcd4d* lcd, int x1, int y1, int x2, int y2, int x3, int y3);

/**
 * Draw a line.
 */
BOOL lcd4dDrawLine(Lcd4d* lcd, int x1, int y1, int x2, int y2, int color);

/**
 * Draw a rectangle.
 */
BOOL lcd4dDrawRectangle(Lcd4d* lcd, int x1, int y1, int x2, int y2, int color);

/**
 * Draw an ellipse.
 */
BOOL lcd4dDrawEllipse(Lcd4d* lcd, int x, int y, int rx, int ry, int color);

/**
 * Draw a pixel.
 */
BOOL lcd4dDrawPixel(Lcd4d* lcd, int x, int y, int color);

/**
 * set the pen to be solid or line style.
 */
BOOL lcd4dSetPenType(Lcd4d* lcd, int penType);

// TEXT COMMANDS

/**
 * Change the font size.
 * @param fontSize LCD4D_FONT_SMALL, LCD4D_FONT_NORMAL ...
 */
BOOL lcd4dSetFont(Lcd4d* lcd, int fontSize);

/**
 * Draw a char at the char grid
 */
BOOL lcd4dDrawChar(Lcd4d* lcd, char c, int column, int row, int color);

/**
 * Draw a char but using graphic mode.
 */
BOOL lcd4dDrawGraphicChar(Lcd4d* lcd, char c, int x, int y, int color, int width, int height);

/**
 * Draw a string in text mode.
 */
BOOL lcd4dDrawString(Lcd4d* lcd, int column, int row, int fontSize, int color, char* text);

/**
 * Draw a string in graphic mode.
 */
BOOL lcd4dDrawGraphicString(Lcd4d* lcd, int x, int y, int fontSize, int color, int width, int height, char* text);

// TODO : Draw Buttons

// TOUCH SCREEN COMMANDS

void lcd4dWaitTouchAndGetTouchCoordinates(Lcd4d* lcd, int touchMode, Point* point);

/**
 * Set the region for touch.
 */
BOOL lcd4dSetTouchRegion(Lcd4d* lcd, int x1, int y1, int x2, int y2);
