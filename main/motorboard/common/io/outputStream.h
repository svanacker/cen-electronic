#ifndef OUTPUT_STREAM_H
#define OUTPUT_STREAM_H

/**
 * Encapsulates a Stream to output data
 * Streams which can be encapsulated :
 * UART, I2C, Zigbee ...
 * @author svanacker
 */

// forward declaration
struct OutputStream;
typedef struct OutputStream OutputStream;

/**
 * The function which opens the output stream.
 * @param param1 a param passed to configure the stream
 */
typedef void OpenOutputStreamFunction(OutputStream* outputStream, int param1);

/**
 * The function which closes the output stream.
 */
typedef void CloseOutputStreamFunction(OutputStream* outputStream);

/**
 * Function which is able to write a character.
 * Be careful that this operation can be bufferized.
 * Use flush to ensure that data are sent
 */
typedef void WriteCharFunction(OutputStream* outputStream, char c);

/**
 * Flush the stream because char written via WriteCharFunction can be bufferized.
 */
typedef void FlushFunction(OutputStream* outputStream);

/**
 * Defines the contract for an output stream (SERIAL, I2C ...)
 */
struct OutputStream {
    /** The address of the stream (Ex : address for I2C, serialPortIndex ...). */
    unsigned char address;
    /** The function which must be called to open the stream. */
    OpenOutputStreamFunction* openOutputStream;
    /** The function which must be called to close the stream. */
    CloseOutputStreamFunction* closeOutputStream;
    /** The function which must be callend to write a char into the stream. */
    WriteCharFunction* writeChar;
    /** Flush the stream. */
    FlushFunction* flush;
    /** pointer on other object (useful for buffer for example) .*/
    int* object;
};

/**
 * Initialize an outputStream.
 */
void initOutputStream(OutputStream* outputStream,
        OpenOutputStreamFunction* openOutputStream,
        CloseOutputStreamFunction* closeOutputStream,
        WriteCharFunction* writeChar,
        FlushFunction* flush,
        int* object);


#endif

