#include <stdlib.h>
#include "jennic5139Driver.h"
#include "jennic5139EventParser.h"

#include "../../common/commons.h"
#include "../../common/delay/cenDelay.h"

#include "../../common/io/buffer.h"
#include "../../common/io/filter.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/hexUtils.h"

#include "../../main/beaconBoard/beaconBoard.h"

/** Status. */
static unsigned char jennicNetworkStatus;

/** Indicates if we are in startup Phase. */
static bool jennicStartup;

/** Indicates if there is an error during startup. */
static bool hasErrorDuringStartup;

/** There is an error during last command. */
static bool jennicError;

/** There is a data during last command. */
static bool jennicData;

/** Indicates if we are in ledCommand => if there is an error during this command, does nothing, else it will go to recursive error. */
static bool ledCommand;

/** Led status. */
static bool ledYellowOn;
static bool ledBlueOn;

void toggleLedYellow() {
	jennic5139LocalLight(JENNIC_LED_YELLOW, ledYellowOn);
	ledYellowOn = !ledYellowOn;
}

void toggleLedBlue() {
	jennic5139LocalLight(JENNIC_LED_BLUE, ledBlueOn);
	ledBlueOn = !ledBlueOn;	
}


void clearLedStatus() {
	jennic5139SetAllPinOutput();
	ledYellowOn = false;
	ledBlueOn = false;
	jennic5139LocalLight(JENNIC_LED_ALL, true);
	delaymSec(300);
	jennic5139LocalLight(JENNIC_LED_ALL, false);

}

void onJennicError() {
	jennicError = true;
}

void onJennicData() {
	jennicData = true;
}

void showJennicError() {
	if (!jennicError) {
		return;
	}
	// for next instruction
	jennicError = false;

	// blind if several errors
	toggleLedYellow();
	if (jennicStartup) {
		hasErrorDuringStartup = true;
	}
}

void showJennicData() {
	if (!jennicData) {
		return;
	}
	// for next instruction
	jennicData = false;

	// blind if several datas
	toggleLedBlue();
}

void showStartupStatus() {
	// if error
	if (hasErrorDuringStartup) {
		// startup error
		jennic5139LocalLight(JENNIC_LED_RED, true);
	}
	else {
		// green led
		jennic5139LocalLight(JENNIC_LED_GREEN, true);
	}
}

#define NUMBER_OF_READ_BETWEEN_INSTRUCTION 10

static InputStream* zigbeeInputStream;
static OutputStream* zigbeeOutputStream;
static OutputStream* debugOutputStream;

/** Contains the buffer used to build command to the jennic. */
static char commandBufferArray[JENNIC_DRIVER_COMMAND_BUFFER_LENGTH];
static Buffer commandBuffer;



bool internalCopyFromZigbeeToDebugRetainingData(bool handleZigbeeStream) {
	bool result = false;
    // while data are available on inputStream
    while (zigbeeInputStream->availableData(zigbeeInputStream)) {
		unsigned char c = zigbeeInputStream->readChar(zigbeeInputStream);
		debugOutputStream->writeChar(debugOutputStream, c);

	    // Flush of debug Data
    	debugOutputStream->flush(debugOutputStream);

		if (handleZigbeeStream) {
			handleJennicNextChar(c);
		}
		result = true;
    }
	return result;
}

bool copyFromZigbeeToDebugRetainingData() {
	return internalCopyFromZigbeeToDebugRetainingData(true);
}

void waitAndCopyFromZigbeeToDebug(int loopCount, int mSecDelay, bool handleZigbeeStream) {
    // use delay to be sure that the connection is OK
    long i;
    for (i = 0; i < loopCount; i++) {
        internalCopyFromZigbeeToDebugRetainingData(handleZigbeeStream);
		delaymSec(mSecDelay);
    }
}

/**
 * @private
 * Write the buffer to debug OutputStream (to know which command are sent) and to the 
 * zigbeeCommand buffer.
 */
void printBufferToDebugAndZigbee() {
	while(!isBufferEmpty(&commandBuffer)) {
        unsigned char c = bufferReadChar(&commandBuffer);
        append(debugOutputStream, c);
		append(zigbeeOutputStream, c);
    }
}

/**
 * 1. Show to the debug OutputStream that a command is sending
 * 2. Send the command to the zigbee and to debug stream
 * 3. wait a delay to ensure the command was handled by the system
 */
void sendJennic5139CommandFromBuffer() {
	// to ensure that the jennic is ready
	delaymSec(20);
	appendString(debugOutputStream, "\nSENDING CMD : "); 
	printBufferToDebugAndZigbee();
	appendString(debugOutputStream, "WAIT ... : ");
	if (ledCommand) {
		waitAndCopyFromZigbeeToDebug(1, 10, false);
	}
	else {
    	waitAndCopyFromZigbeeToDebug(NUMBER_OF_READ_BETWEEN_INSTRUCTION, 10, true);
	}
	showJennicError();
	showJennicData();
}

/**
 * @private
 */
OutputStream* getCommandOutputStream() {
	return &(commandBuffer.outputStream);
}

/**
* @private
* Append a command string to the command buffer
*/
void appendCmdString(char* text) {
	appendString(&(commandBuffer.outputStream), text);
}

void appendCmdDec(long value) {
	appendDec(&(commandBuffer.outputStream), value);
}

void appendCmdHex2(int value) {
	appendHex2(&(commandBuffer.outputStream), value);
}

void appendComma() {
	appendString(&(commandBuffer.outputStream), ",");
}

void appendCmdEnd() {
	appendString(&(commandBuffer.outputStream), "\n");
}

void jennic5139SetAllPinOutput() {
	// All digital pins to output
	appendCmdString(JENNIC_PIN_CONFIGURE_IO);
	appendCmdString(",0,xFFFF");
	appendCmdEnd();
	sendJennic5139CommandFromBuffer();
}

void initJennic5139Streams(InputStream* aZigbeeInputStream,
        OutputStream* aZigbeeOutputStream,
        OutputStream* aDebugOutputStream) {
    zigbeeInputStream = aZigbeeInputStream;
    zigbeeOutputStream = aZigbeeOutputStream;
    debugOutputStream = aDebugOutputStream;

	initBuffer(&commandBuffer, &commandBufferArray, JENNIC_DRIVER_COMMAND_BUFFER_LENGTH, "jennicCmdBuffer", "CMD");
}

/**
 * See header documentation
 * looks like : SND,0006066005650518898,0102AA,3,0
 */
void sendJennic5139DataBuffer(InputStream* inputStream, char* macAddress, int flags) {
	appendCmdString("SND,");
	appendCmdString(macAddress);
	appendComma();

	// ASCII : documentation say that we can send ASCII data too by preceding
	// data with ", and suffixing by "
	appendCmdString("\"");

	// Copy the content of data buffer into command Buffer
	int size = copyInputToOutputStream(inputStream, &(commandBuffer.outputStream), NULL, COPY_ALL);

	appendCmdString("\"");

	appendComma();
    appendCmdDec(size);

	appendComma();
    appendCmdDec(flags);

	appendCmdEnd();
	
	sendJennic5139CommandFromBuffer();
}

// POWER

/**
 * RDP,-12,0 <LF>
 */
void changeJennic5139Power(signed int powerDB, unsigned int moduleType) {
	appendCmdString(JENNIC_CHANGE_POWER_DECIBEL);
	appendComma();

	appendCmdDec(powerDB);
	appendComma();

	appendCmdDec(moduleType);
	appendCmdEnd();

	sendJennic5139CommandFromBuffer();
}

/**
 * Send a command of configuration which looks like : 
 * CFG,x07FFF800,10,8,2,0\n
 */
void initJennic5139Configuration(char* channelMask,
								 int childrenCount,
								 int maxEndDeviceChildrenCount,
								 int maxFailureBeforeOrphaning,
								 int timeOutPeriod) {
	appendCmdString(JENNIC_CMD_CFG);
	appendComma();

	appendCmdString(channelMask);
	appendComma();

	appendCmdDec(childrenCount);
	appendComma();

	appendCmdDec(maxEndDeviceChildrenCount);
	appendComma();

	appendCmdDec(maxFailureBeforeOrphaning);
	appendComma();

	appendCmdDec(timeOutPeriod);
	appendCmdEnd();

	sendJennic5139CommandFromBuffer();
}

/**
 * @param pingPeriod : Router ping period (R)
 * 0: Pings disabled (default)
 * 1-6553 seconds
 *
 * @param sleepCycleBetweenPings : Sleep cycles between pings (E)
 * 0: Pings disabled
 * 1-255 (default: 1)
 * 
 * @param scanSleep : Scan sleep (E)
 * 200-4294967275 (default: 10000),
 * in milliseconds Values less than 1000 are not
 * recommended for a large network 
 * 
 * @param pollPeriod : Poll period (E)
 * 32-bit value, in 100-ms periods
 * Set to 0 to disable auto-polling 
 *
 * @param maxNumberOfHopsForBroadcast : Max. number of hops for broadcast
 * 0-255
 */
void configureNetworkParameters(unsigned int pingPeriod,
								unsigned char sleepCycleBetweenPings,
								unsigned long scanSleep,
								unsigned long pollPeriod,
								unsigned char maxNumberOfHopsForBroadcast
) {
	appendCmdString(JENNIC_CMD_CONFIGURE_NETWORK_PARAMETERS);
	appendComma();

	appendCmdDec(pingPeriod);
	appendComma();

	appendCmdDec(sleepCycleBetweenPings);
	appendComma();

	appendCmdDec(scanSleep);
	appendComma();

	appendCmdDec(pollPeriod);
	appendComma();

	appendCmdDec(maxNumberOfHopsForBroadcast);
	appendCmdEnd();

	sendJennic5139CommandFromBuffer();
}

/**
 * Configure Network parameters with default parameters.
 */
void configureDefaultNetworkParameters() {
	configureNetworkParameters(PING_PERIOD_SECONDS,
								SLEEP_CYCLES_BETWEEN_PINGS,
								SCAN_SLEEP,
								POLL_PERIOD,
								MAX_NUMBER_HOPS_FOR_BROADCAST);
}



/**
 * @private
 * Init the Jennic 5139, with a command which looks like : 
 * "INI,xABCD,0,x12345678,0,1\n"
 */
void initJennic5139Init(char* panId, int channelId, char* applicationId, int restoreContext, int routing) {
	appendCmdString(JENNIC_CMD_INI);
	appendComma();
	
	appendCmdString(panId);
	appendComma();

	appendCmdDec(channelId);
	appendComma();

	appendCmdString(applicationId);
	appendComma();

	appendCmdDec(restoreContext);
	appendComma();

	appendCmdDec(routing);
	appendCmdEnd();

	sendJennic5139CommandFromBuffer();
}

/**
 * Configure Network parameters
 * @param pingPeriod : Router ping period (R)
 * 0: Pings disabled (default)
 * 1-6553 seconds
 * 
 * @param sleepCyclesBetweenPings : Sleep cycles between pings (E)
 * 0: Pings disabled
 * 1-255 (default: 1)
 *
 * @param scan : Scan sleep (E) 200-4294967275 (default: 10000), in milliseconds
 * Values less than 1000 are not ecommended for a large network

 * @param pollPeriod : Poll period (E) 32-bit value, in 100-ms periods
 * Set to 0 to disable auto-polling
 *
 * @param maxNumberOfHopsForBroadcast : Max. number of hops for broadcast 0-255
 */ 
void jennic5139ConfigureNetworkParameters(unsigned int pingPeriod, 
											unsigned char sleepCyclesBetweenPings,
											unsigned long scanSleep,
											unsigned long pollPeriod,
											unsigned char maxNumberOfHopsForBroadcast);

/**
 * @private
 * Send a command of start with the role of the device which looks like:
 * "STR,0\n"
 * @param nodeType NOTE_TYPE_COORDINATER / NOTE_TYPE_ROUTER
 */
void initJennic5139Start(int nodeType) {
	setJennicNetworkStatus(JENNIC_NOT_INITIALIZED);
	appendCmdString(JENNIC_CMD_START);
	appendComma();
	appendCmdDec(nodeType);
	appendCmdEnd();

	sendJennic5139CommandFromBuffer();
}

void jennic5139CommonStartupBegin() {
	hasErrorDuringStartup = false;
	jennicStartup = true;
	clearLedStatus();	
}

void jennic5139CommonStartupEnd() {
	jennicStartup = false;
	showStartupStatus();
}

void initJennic5139Coordinater() {
	jennic5139CommonStartupBegin();

	initJennic5139Configuration(
			CHANNEL_MASK_AUTO_SELECTION,
			NUMBER_OF_CHILDREN,
			MAX_END_DEVICE_CHILDREN,
			MAX_FAILURE_BEFORE_ORPHANING,
			TIME_OUT_PERIOD);
	
	configureDefaultNetworkParameters();

	initJennic5139Init(DEFAULT_PAN_ID,
					   CHANNEL_ID_AUTO,
					   DEFAULT_APPLICATION_ID,
					   RESTORE_CONTEXT_DISABLED, 
					   ROUTING_ON);


 	initJennic5139Start(NODE_TYPE_COORDINATER);

	// Change power to max
	changeJennic5139Power(JENNIC_CHANGE_POWER_DECIBEL_MAX, JENNIC_CHANGE_POWER_HIGH_POWER_MODULE);

	jennic5139CommonStartupEnd();
}

void initJennic5139Router() {
	jennic5139CommonStartupBegin();

	initJennic5139Configuration(
			CHANNEL_MASK_AUTO_SELECTION,
			NUMBER_OF_CHILDREN,
			MAX_END_DEVICE_CHILDREN,
			MAX_FAILURE_BEFORE_ORPHANING,
			TIME_OUT_PERIOD);

	configureDefaultNetworkParameters();

	initJennic5139Init(NO_PAN_ID_TO_DEFINED, // because coordinater defined it !
					   CHANNEL_ID_AUTO,
					   DEFAULT_APPLICATION_ID,
					   RESTORE_CONTEXT_DISABLED, 
					   ROUTING_ON);

	initJennic5139Start(NODE_TYPE_ROUTER);

	// Change power to Max
	changeJennic5139Power(JENNIC_CHANGE_POWER_DECIBEL_MAX, JENNIC_CHANGE_POWER_HIGH_POWER_MODULE);

	jennic5139CommonStartupEnd();
}

void jennic5139Reset() {
	appendCmdString(JENNIC_CMD_RESET);
	appendCmdEnd();
	sendJennic5139CommandFromBuffer();
}

void jennic5139LocalLight(char* pinMask, bool on) {
	ledCommand = true;
    appendCmdString(JENNIC_PIN_WRITE_PIN);
	if (on) {
		appendCmdString(",0,x");
		appendString(getCommandOutputStream(), pinMask);
		appendCmdEnd();
    } else {
		appendCmdString(",x");	
		appendString(getCommandOutputStream(), pinMask);
		appendCmdString(",0");
		appendCmdEnd();
    }
	sendJennic5139CommandFromBuffer();
	ledCommand = false;
}

void jennic5139RemoteLight(char* jennicAddress, char* pinMask, bool on) {
	// Establish a tunnel for transmit remote command
    appendCmdString(JENNIC_TUNNEL_CONNECTION);
	appendCmdString(",3,");
	appendCmdString(jennicAddress);
	appendComma();
	appendCmdString("32");
	appendCmdEnd();
	sendJennic5139CommandFromBuffer();
	
	// Opens a communication channel in a tunnel set up using TCN. The TOP command must
	// be executed on the remote node, and sent to the node as a tunnelled command using TCM
    appendCmdString(JENNIC_TUNNEL_SEND_COMMAND);
	appendCmdString(",\"");
	appendCmdString(JENNIC_TUNNEL_OPEN);
	appendCmdString("\"\n");
	sendJennic5139CommandFromBuffer();

	// Defines which DIO pins (DIO0-DIO20) are inputs and which are outputs. Note that the command has
	// no effect for a pin being used by an enabled on-chip peripheral.
	// The input and output pins are specified in separate 32-bit bitmaps, where each of bits 0 to 20 represents
	// the corresponding DIO pin (bits 21 to 31 are unused). The bit settings for the same DIO pin must
	// not conflict in the two bitmaps (for a conflict, the default is input).
    appendCmdString(JENNIC_TUNNEL_SEND_COMMAND);
	appendCmdString(",\"");
	appendCmdString(JENNIC_PIN_CONFIGURE_IO);
	appendCmdString(",0,xFFFF\"\n");
	sendJennic5139CommandFromBuffer();

	// On or off the outputs
	// Sets the output status (on or off) of the DIO pins (DIO0-DIO20). Note that the command has no
	// effect for a pin not configured as an output or being used by an enabled on-chip peripheral.
	// The pins that are on and off are specified in separate 32-bit bitmaps, where each of bits 0 to 20 represents
	// the corresponding DIO pin (bits 21 to 31 are unused). The bit settings for the same DIO pin must
	// not conflict in the two bitmaps (for a conflict, the default is off).
	// On : 
	// 32-bit bitmap: bit 0 set means DIO0 on, bit 1 set means DIO1 on, etc.
	// Off
	// 32-bit bitmap: bit 0 set means DIO0 off, bit 1 set means DIO1 off, etc.
	appendCmdString(JENNIC_TUNNEL_SEND_COMMAND);
	appendCmdString(",\"");
	appendCmdString(JENNIC_PIN_WRITE_PIN);

    if (on) {
        appendCmdString(",0,x");
		appendString(getCommandOutputStream(), pinMask);
		appendCmdString("\"\n");
    } else {
		appendCmdString(",x");
		appendString(getCommandOutputStream(), pinMask);
		appendCmdString(",0\"\n");
    }
	sendJennic5139CommandFromBuffer();

	// Close the tunnel
	appendCmdString(JENNIC_TUNNEL_SEND_COMMAND);
	appendCmdString(",\"");
	appendCmdString(JENNIC_TUNEL_CLOSE);
	appendCmdString("\"\n");
	sendJennic5139CommandFromBuffer();
}

// NETWORK STATUS

unsigned char getJennicNetworkStatus() {
	return jennicNetworkStatus;
}

void setJennicNetworkStatus(unsigned char aJennicNetworkStatus) {
	jennicNetworkStatus = aJennicNetworkStatus;
}

