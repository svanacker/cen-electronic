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
	// Buffer (for input)
	Buffer* inputBuffer;
	// Color with 2 bytes
	int color;
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
// RAW COMMANDS

#define		LCD4D_MEMORY_EXTENDED_COMMAND			'@'
#define		LCD4D_MEMORY_INIT_CARD					'i'
#define		LCD4D_MEMORY_SCREEN_COPY				'C'
//TODO

// SD FAT COMMAND
#define		LCD4D_INITIALIZE_MEMORY_CARD_FAT_COMMAND	'i'
#define		LCD4D_READ_FILE_COMMAND						'a'
#define		LCD4D_SCREEN_COPY_FAT_COMMAND				'c'
#define 	LCD4D_DISPLAY_IMAGE_FAT_COMMAND				'm'
#define		LCD4D_LIST_DIRECTORY_OF_CARD				'd'
#define		LCD4D_ERASE_FILE_FAT_COMMAND				'e'
#define		LCD4D_WRITE_FILE_TO_CARD_FAT_COMMAND		't'
#define		LCD4D_HANDSHAKING_NO						0
#define		LCD4D_HANDSHAKING_EACH_BYTE					1
#define		LCD4D_HANDSHAKING_EACH_50_BYTE				50
// No Append, file will be created (or overwritten if it exists).
#define		LCD4D_APPEND_MODE_NO						0
// Append mode, file will be appended to (or created if it doesn’t exist).
#define		LCD4D_APPEND_MODE_YES						80
// High performance. Two ACKS will be sent after the filesize. This
// keeps transmission running at a high speed, as no time is spent waiting for
// the return ACK. The same total number of ACKs doesn’t change (i.e the
// last ACK is missing). For simple un-buffered serial ports this may lead to
// loss of the second ACK.
#define		LCD4D_PERFORMANCE_MODE_HIGH_PERFORMANCE		0
// Low performance. Only a single ACK is sent at a time. This is for
// un-buffered serial port controllers.
#define		LCD4D_PERFORMANCE_MODE_LOW_PERFORMANCE		40

#define		LCD4D_PLAY_AUDIO_WAV_FROM_CARD_COMMAND		'l'
#define 	LCD4D_PLAY_WAV_OPTION_RETURN_WHEN_PLAYING_COMPLETE	0x00
#define 	LCD4D_PLAY_WAV_OPTION_RETURN_IMMEDIATELY				0x01
#define 	LCD4D_PLAY_WAV_OPTION_STOP_CURRENTLY_PLAYING			0x02
#define 	LCD4D_PLAY_WAV_OPTION_PAUSE_CURRENTLY_PLAYING			0x04
#define 	LCD4D_PLAY_WAV_OPTION_RESUME_CURRENTLY_PLAYING		0x05
#define 	LCD4D_PLAY_WAV_OPTION_LOOP_CURRENTLY_PLAYING			0x06

/**
 * Init the Lcd4d structure with his properties.
 */
void initLcd4d(Lcd4d* lcd, OutputStream* outputStream, InputStream* inputStream, Buffer* inputBuffer);
 
// COLOR MANAGEMENT

void setLcd4dColor(Lcd4d* lcd, unsigned char r, unsigned char g, unsigned char b);

/**
 * Set the autobaud to the lcd.
 */
bool setAutoBaud(Lcd4d* lcd);

/**
 * Change the rate of the uart.
 */
bool setLcd4dBaudRate(Lcd4d* lcd, int baudRateType);

/**
 * Get the version of the Lcd into the version structure.
 */
void getLcd4dVersionCommand(Lcd4d* lcd, Lcd4dVersion* version);

/**
 * Print the content of the Lcd4dVersion.
 * @param version
 */
void lcd4dPrintVersion(OutputStream* outputStream, Lcd4dVersion* version);

/**
 * Get the display resolution and set it to the point parameter.
 */
void getLcd4dDisplayResolution(Lcd4d* lcd, Point* point);

/** 
 * Clear Screen.
 */
bool lcd4dClearScreen(Lcd4d* lcd);

/**
 * Enable or disable the backlight.
 */
bool lcd4dBacklight(Lcd4d* lcd, bool backlight);

/**
 * Enable or not the display.
 */
bool lcd4dDisplay(Lcd4d* lcd, bool display);

/**
 * Change the display orientation.
 * @param displayOrientation LCD4D_ORIENTATION_90, LCD4D_ORIENTATION_270, LCD4D_NATIVE_ORIENTATION,	LCD4D_ORIENTATION_180
 */
bool lcd4dSetDisplayResolution(Lcd4d* lcd, unsigned int displayOrientation);

/**
 * Enable or not the touch control.
 */
bool lcd4dTouchControl(Lcd4d* lcd, bool touchControl);

/** 
 * Set the volume of the lcd.
 */
bool lcd4dVolume(Lcd4d* lcd, int volume);

// DRAW Functions

/**
 * Draw a circle.
 */
bool lcd4dDrawCircle(Lcd4d* lcd, int x, int y, int radius);

/**
 * Draw a triangle.
 */
bool lcd4dDrawTriangle(Lcd4d* lcd, int x1, int y1, int x2, int y2, int x3, int y3);

/**
 * Draw a line.
 */
bool lcd4dDrawLine(Lcd4d* lcd, int x1, int y1, int x2, int y2);

/**
 * Draw a rectangle.
 */
bool lcd4dDrawRectangle(Lcd4d* lcd, int x1, int y1, int x2, int y2);

/**
 * Draw an ellipse.
 */
bool lcd4dDrawEllipse(Lcd4d* lcd, int x, int y, int rx, int ry);

/**
 * Draw a pixel.
 */
bool lcd4dDrawPixel(Lcd4d* lcd, int x, int y);

/**
 * set the pen to be solid or line style.
 */
bool lcd4dSetPenType(Lcd4d* lcd, int penType);

// TEXT COMMANDS

/**
 * Change the font size.
 * @param fontSize LCD4D_FONT_SMALL, LCD4D_FONT_NORMAL ...
 */
bool lcd4dSetFont(Lcd4d* lcd, int fontSize);

/**
 * Draw a char at the char grid
 */
bool lcd4dDrawChar(Lcd4d* lcd, char c, int column, int row);

/**
 * Draw a char but using graphic mode.
 */
bool lcd4dDrawGraphicChar(Lcd4d* lcd, char c, int x, int y, int width, int height);

/**
 * Draw a string in text mode.
 */
bool lcd4dDrawString(Lcd4d* lcd, int column, int row, int fontSize, char* text);

/**
 * Draw a string in graphic mode.
 */
bool lcd4dDrawGraphicString(Lcd4d* lcd, int x, int y, int fontSize, int width, int height, char* text);

// TODO : Draw Buttons

// TOUCH SCREEN COMMANDS

void lcd4dWaitTouchAndGetTouchCoordinates(Lcd4d* lcd, int touchMode, Point* point);

/**
 * Set the region for touch.
 */
bool lcd4dSetTouchRegion(Lcd4d* lcd, int x1, int y1, int x2, int y2);

/**
 * When objects from the memory card such as images are displayed sequentially, a delay can
 * be inserted between subsequent objects. A delay basically has the same effect as a NOP
 * (No Operation) which can be used to determine how long the object stays on the screen
 * before the next object is displayed. If the user touches the display during the delay period,
 * the delay will end immediately. The touch region, if used, is taken into account.
 */
bool lcd4dWaitUntilTouch(Lcd4d* lcd, unsigned int delayMilliSeconds);

// MEMORY CARDS

// -> RAW Level

/**
 * Initialize the memory Card of a LCD 4D.
 */
bool lcd4dInitializeMemoryCardRaw(Lcd4d* lcd);

/**
 * Set the pointer address of the memory card.
 */
bool lcd4dSetAddressPointerOfCardRaw(Lcd4d* lcd, unsigned long address);

/**
 * Read byte data from the card (RAW).
 */
unsigned char lcd4dReadByteDataFromCardRaw(Lcd4d* lcd, unsigned long address);

/**
 * Writes data byte to the card (RAW).
 */
bool lcd4dWriteByteDataToCardRaw(Lcd4d* lcd, unsigned char data);

/**
 * Read Sector Block Data from Card (RAW).
 * @param sectorIndex 3 bytes (big endian) sector address. Sector address range from 16,777,215 depending on the capacity of the card. 
 * Each sector is 512 in size. There are 2048 sectors per every 1Mb of card memory.
 */
char* lcd4dReadSectorBlockDataFromCardRaw(Lcd4d* lcd, unsigned long sectorIndex);

/**
 * This command allows downloading and writing blocks of sector data to the card. The data
 * block must always be 512 bytes in length. For large volumes of data such as images, the
 * data must be broken up into multiple sectors (chunks of 512 bytes) and this command then
 * maybe used many times until all of the data is written. If the data block to be written is less
 * than 512 bytes in length, then make sure the rest of the remaining data are padded with
 * 00hex or FFhex (it can be anything).
 * 
 * Once this command is sent, the device will take a few milliseconds to write the data into its
 * memory card and at the end of which it will respond.
 * Only data(1..512) are written to the sector. Other bytes in the command message do not
 * get written.
 */
bool lcd4dWriteSectorBlockDataToCardRaw(Lcd4d* lcd, unsigned long sectorIndex, char data[]);

/**
 * This command copies an area of the screen of specified size. The start location of the block
 * to be copied is represented by x, y (top left corner) and the size of the area to be copied is
 * represented by width and height parameters. This is similar the “Screen Copy-Paste”
 * command but instead of the copied screen area being pasted to another location on the
 * screen it is stored into the memory card. The stored screen image can then be later
 * recalled from the memory card and redisplayed onto the screen at the same or different
 * location by using the “Display Image-Icon from Card” command.
 * This is a very powerful feature for animating objects, smooth scrolling, or implementing a
 * windowing system.
 */
bool lcd4dScreenCopySaveToCardRaw(Lcd4d* lcd, int x, int y, int width, int height, unsigned long sectorIndex);

/**
 * This command displays an image on the screen that has been previously stored at a
 * particular sector address in the memory card. Position of the image to be displayed is
 * specified by (x, y). Other parameters can be extracted from the text file(.Txt) created in the
 * Graphics Composer 3 after writing the slide show on the SD card.
 * Display Control Function (Syntax: c m d , m o d e, value ) should be used to set “Image Format”
 * to “New format” i.e mode = 06hex. Value = 00hex. Refer to Sec 2.1.6.
 * Image format is “Old Format” by default.
 * Note: The image parameters such as width, height and colour-mode are built into the image
 * header file and do not need to be specified by the host.
 */
bool lcd4dDisplayImageIconFromCardRaw(Lcd4d* lcd, int x, int y, unsigned long sectorIndex);

/**
 * This command displays a video/Animation on the screen that has been previously stored at
 * a particular sector address in the memory card. Position of the image to be displayed is
 * specified by (x, y). Other parameters can be extracted from the text file(.Txt) created in the
 * Graphics Composer 3 after writing the slide show on the SD card.
 * Display Control Function (Syntax: c m d , m o d e , value ) should be used to set “Image Format”
 * to
 * “New format” i.e mode = 06hex. Value = 00hex. Refer to Sec 2.1.6.
 * Image format is “Old Format” by default.
 * Note: The Video/Animation parameters such as width, height and colour-mode are built
 * into the image header file and do not need to be specified by the host.
 */
bool lcd4dDisplayVideoFromCardRaw(Lcd4d* lcd, int x, int y, int delay, unsigned long sectorIndex);

// -> FAT Level

/**
 * This command initialises the memory card. The memory card is always initialised upon
 * Power-Up or Reset cycle, if the card is present. If the card is inserted after the power up or
 * a reset then this command must be used to initialise the card.
 * Note! There is no card insert/remove auto detect facility.
 */
bool lcd4dInitializeMemoryCardFAT(Lcd4d* lcd);

/**
 * Using this command, the host can read a DOS compatible (FAT) file from the memory card.
 * Because the time taken to process the read bytes varies, a technique is required to ensure
 * that the host communications buffer does not overflow and data is not lost. This is
 * implemented by a simple handshaking protocol where the PICASO-SGC will break up the
 * file into smaller data blocks. When the host receives a block, it sends an ACK(06hex) to
 * request the next block of data. The size of the data block is initially set by the host in the
 * command packet, specified by the value in the “handshaking” byte. The larger the value
 * the better, as long as the host system can buffer the incoming block size. Setting this value
 * too low will slow the transfer.
 */
bool lcd4dReadFileFromCardFAT(Lcd4d* lcd, int handshakingMode, char* fileName);

/**
 * This command allows the host to write a DOS compatible (FAT) file to the memory card. The
 * PICASO-SGC device serial port (UART), has a buffer size of 100 bytes for capturing incoming
 * data from the host. If this buffer fills up and overflows, data will be lost. Therefore the host
 * must allow the device enough time to write its buffer to the memory card so it can then
 * receive further file data from the host. For small files (less than 100 bytes in the append
 * mode) the host can send the complete file data in one attempt. However, for larger files a
 * simple handshaking protocol is implemented where the host sends the file data in small
 * blocks. Using this handshaking method, the host always waits for an ACK from the device
 * before sending the next block of data. The size of the data block is initially set by the host in
 * the command packet, specified by the handshaking value in the “options” byte. The larger
 * the value the better. Setting it too low will slow the transfer. The first ACK is always sent by
 * the device, after the filesize parameter is transmitted by the host, or this could also be a
 * NAK in which case one of the parameters is invalid or a file system error occurred.
 * Note: Do not set handshaking to zero if the file size is larger than 100 bytes.
 * @param handshakingMode Controls handshaking (how often the device sends an ACK to request more
 * data from the host) and whether an existing file is appended to.
 * @param appendMode append or not (overwrite) the file
 * @param performanceMode high or low performance
 */
bool lcd4dWriteFileToCardFAT(Lcd4d* lcd, int handshakingMode, int appendMode, int performanceMode, char* fileName, unsigned long fileSize, Buffer* buffer);

/**
 * Erases the file specified in the “file_name”.
 */
bool lcd4dEraseFileFromCardFAT(Lcd4d* lcd, char* fileName);

/**
 * Returns a directory listing (stream of characters) consisting of the files names matching the
 * “file_name” delimited by a Newline(0Ahex) character. Always responds with an ACK at the
 * completion of a listing. Responds with a NAK if a file error occurs.
 * An empty directory with no files or the result of an unsuccessful file name or wild card
 * search will only return an ACK.
 * @param fileNameToMatch The filename is 1-12 chars long with an assumed '.' between chars 8 and 9, if
 * there is not one specified the filename. Wild cards such as '*' and '?' are
 * allowed.
 * @param outputStream the stream in which we write the data
 */
bool lcd4dListDirectoryOfCardFAT(Lcd4d* lcd, char* fileNameToMatch, OutputStream* outputStream);

/**
 * This command copies an area of the screen of specified size. The start location of the block
 * to be copied is represented by x, y (top left corner) and the size of the area to be copied is
 * represented by width and height parameters. This is similar the “Screen Copy-Paste”
 * command but instead of the copied screen area being pasted to another location on the
 * screen it is stored into the memory card in FAT format with the specified filename. The
 * stored screen image can then be later recalled from the memory card and redisplayed onto
 * the screen at the same or different location by using the “Display Image-Icon from Card
 * (FAT)” command.
 * This is a very powerful feature for animating objects, smooth scrolling, or implementing a
 * windowing system.
 * Note: This command always stores that part of the screen as a 16 bit image, i.e. 2 bytes per
 * pixel.
 */
bool lcd4dScreenCopySaveToCardFAT(Lcd4d* lcd, int x, int y, int width, int height, char* fileName);

/**
 * This command displays a bitmap image or an icon on to the screen that has been
 * previously stored in the FAT file (specified by “ filename”) on the memory card. The screen
 * position of the image to be displayed is specified by (x, y).
 * Note: The “Screen Copy-Save to Card (FAT)” command always stores that part of the
 * screen as a 16 bit image, i.e. 2 bytes per pixel.
 * This command can also be used to display multimedia objects in the GCI file, created from
 * the Graphics Composer 3 by using “4DGL, SGC Picaso - GCI - FAT Selected Folder”. The
 * image parameters such as width, height and colour-mode are built into the GCI file; they
 * don’t need to be specified by the host controller. All you need is GCI filename which is
 * loaded to the SD card, and the pointer to the multimedia object which can be found from
 * the .DAT file created by the Graphics Composer along with the GCI file.
 * @param imagePos 4 bytes (big endian) sector address of a previously stored Image-Icon that is
 * about to be displayed. All you need is GCI filename which is
 * loaded to the SD card, and the pointer to the multimedia object which can be found from
 * the .DAT file created by the Graphics Composer along with the GCI file.
 */
bool lcd4dDisplayImageIconFromCardFAT(Lcd4d* lcd, int x, int y, char* fileName, unsigned long imagePos);

/**
 * This command plays a WAV file from the memory card. Wave files should be mono to keep
 * data bandwidth to a minimum, and should be 'canonic' format. Lots of windows formats
 * wont work. Use something like ‘Cool Edit’ or similar to tailor the wav files to a suitable
 * format.
 * The ideal sample rate of the WAV file is 16Khz-Mono and the maximum should be 22Khz.
 * Any higher sample rate will extremely slow down the system. Sample rates below 12Khz,
 * the PWM will cause aliasing (filtering is a bare minimum).
 * If you only hear noise or random snippets of sound remember, the Speed and Capacity of
 * the memory card are important, most 2Gb cards should be fine, 64mb cards fail all but the
 * most simple sounds.
 * @param option see PLAY_WAV_OPTION_XXX options
 */
bool lcd4dPlayAudioWAVFileFromCardFAT(Lcd4d* lcd, unsigned int option, char* fileName);
