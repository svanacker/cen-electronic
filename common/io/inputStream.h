#ifndef INPUT_STREAM_H
#define INPUT_STREAM_H

/**
 * Encapsulates a Stream to read data from heterogeneous
 * Streams which can be encapsulated :
 * UART, I2C, Zigbee ...
 * @author svanacker
 */

#include "../../common/commons.h"

/** Define the command to clear the inputStream. */
#define HEADER_CLEAR_INPUT_STREAM 'z'

/**
* Defines the constant indicating that data is not corrected (connection is not established).
* Only for I2C
*/
#define INCORRECT_DATA 0xFF

// forward declaration
struct InputStream;
typedef struct InputStream InputStream;

/**
* the function which opens the input stream.
* @param param1 a param passed to configure the stream
*/
typedef void OpenInputStreamFunction(InputStream* inputStream, int param1);

/**
* The function which closes the input stream.
*/
typedef void CloseInputStreamFunction(InputStream* inputStream);

/**
* Function which is able to get a character from the stream.
*/
typedef char ReadCharFunction(InputStream* inputStream);

/**
* Function which is able to return if there is character to read.
*/
typedef BOOL AvailableDataFunction(InputStream* inputStream);

/**
* Defines the contract for an input stream (SERIAL, I2C ...)
*/
struct InputStream{
	/** The address of the stream (Ex : address for I2C, serialPortIndex ...). */
	unsigned char address;
	/** The function which must be called to open the stream. */
	OpenInputStreamFunction* openInputStream;
	/** The function which must be called to close the stream. */
	CloseInputStreamFunction* closeInputStream;
	/** The function which must be called to read a char from the input Stream.*/
	ReadCharFunction* readChar;
	/** The function which must be called to detects if there is a character to read. */
	AvailableDataFunction* availableData;
	/** pointer on other object (useful for buffer for example) .*/
	int* object;
};

/**
* Initialize the input stream
* @param openStream The function which must be called to open the stream.
* @param closeStream The function which must be called to close the stream.
* @param readChar The function which must be called to read a char from the input Stream.
* @param The function which must be called to detects if there is a character to read.
*/
void initInputStream(InputStream* stream,
				OpenInputStreamFunction* openInputStream,
				CloseInputStreamFunction* closeInputStream,
				ReadCharFunction* readChar,
				AvailableDataFunction* availableData,
				int* object
);

/**
* Clear an input Stream.
* @param inputStream the stream for which we want to clear (by pulling data)
*/
void clearInputStream(InputStream* inputStream);


#endif

