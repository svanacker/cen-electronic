#ifndef JENNIC_5139_DRIVER_H
#define JENNIC_5139_DRIVER_H

#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"

// BUFFER LENGTH

#define JENNIC_DRIVER_COMMAND_BUFFER_LENGTH		45

// NETWORK STATE for Coordinater - Router

/** The jennic is not initialized. */
#define JENNIC_NOT_INITIALIZED					0

/** The jennic is not started (NTU not send). */
#define JENNIC_WAITING_FOR_NODE					1

/**
 * The jennic is connected (CHILD JOINED, but no CHILD LEAVE).
 * If CHILD_LEAVE, GO BACK to JENNIC_WAITING_FOR_NODE
 */
#define JENNIC_LINK_CONNECTED					2

/**
 * State of the jennic connection.
 */
unsigned char getJennicNetworkStatus();

/**
 * Change the state of the NETWORK STATUS
 */
void setJennicNetworkStatus(unsigned char aNetworkStatus);



// Configuration - CFG Commands

/**
* Define the mask defining which channel can be search.
* In this case, we authorize search from channel 11 to 26
* In binary, the following value equals to :
* 0b111111111111111100000000000
* Channels to be included by Router or End
* Device in the scan for auto-channel
* selection. Only applicable to Co-ordinator if
* auto-channel selection enabled using INI
*/
#define CHANNEL_MASK_AUTO_SELECTION			"x07FFF800"

/**
 * Maximum permissible number of child nodes.
 * 0-16 (default: 10)
 */
#define NUMBER_OF_CHILDREN					10

/**
 * Maximum number of End Device children
 * (nodes that are capable of sleeping). The remaining child slots are reserved
 * exclusively for Routers, although any number of children can be Routers
 * 0-8 (default: 8)
 */
#define MAX_END_DEVICE_CHILDREN				8

/**
 * Number of failed communications before parent or child considered to be lost
 * 1-255 (default: 5). Must be set to 2 or higher on a parent (R or C) with Router children
 */
#define MAX_FAILURE_BEFORE_ORPHANING		2

/**
 * Timeout period for communication (excluding data polling) from an End Device
 * child. If no message is received from the End Device within this period, the child is
 * assumed lost.
 * End Device activity timeout (C,R). 32-bit value, in 100-ms periods. (default: 0 - timeout disabled)
 */
#define TIME_OUT_PERIOD						0

// Initialization

/** 
 * Define the Personnal Area Network which must be used (2 bytes)
 * We try to use a different PAN_ID than the classical HOW TO to avoid problems with other teams
 */
#define DEFAULT_PAN_ID 						"xBBBB"

/**
 * The PAN_ID need only to be defined by the coordinater. So, for other device (router, endDevice), this parameter
 * must be defined to "0"
 */
#define NO_PAN_ID_TO_DEFINED 					"0"

/**
 * Radio channel to adopt for network or auto-channel select (configured using CFG)
 * 2400-MHz radio channel (C)
 * 0: Auto-channel selection (default)
 * 11-26: Specific channel
 */
#define CHANNEL_ID_AUTO						0

/** 
 * Define the Application_ID which must be used (4 bytes)
 * We try to use a different PAN_ID than the classical HOW TO to avoid problems with other teams
 * Network Application ID of the network to be created (C) or of the network to be found
 * (R,E)
 */
#define DEFAULT_APPLICATION_ID			"x01020304"

// Network particular parameters

/**
 * Router ping period (R).
 * 0: Pings disabled (default)
 * 1-6553 seconds
 */
#define PING_PERIOD_SECONDS				1

/**
 * Sleep cycles between pings (E)
 * 0: Pings disabled
 * 1-255 (default: 1)
 */
#define SLEEP_CYCLES_BETWEEN_PINGS		1

/**
 * Scan sleep (E)
 * 200-4294967275 (default: 10000), in milliseconds
 * Values less than 1000 are not
 * recommended for a large network
 */
#define SCAN_SLEEP						1000

/**
 * Poll period (E)
 * 32-bit value, in 100-ms periods
 * Set to 0 to disable auto-polling
 */
#define POLL_PERIOD						10

/** 
 * Max. number of hops for broadcast
 * 0-255
 */
#define MAX_NUMBER_HOPS_FOR_BROADCAST	10

/**
 * The option to automatically restore application and network context data from
 * external non-volatile memory (previously saved with SCN), following power loss
 */
#define RESTORE_CONTEXT_DISABLED		0
#define RESTORE_CONTEXT_ENABLE			1

/**
 * The routing option of the node (Co-ordinator or Router). Always disable for End Device
 * 0: Disable
 * 1: Enable
 */
#define ROUTING_OFF							0
#define ROUTING_ON							1

/**
 * Define the role of the module as a coordinater.
*/
#define NODE_TYPE_COORDINATER				0

/**
 * Define the role of the module as a router.
 */
#define NODE_TYPE_ROUTER					1

/**
 * Define the role of the module as an end device.
 */
#define NODE_TYPE_END_DEVICE				2

// FLAGS MASK (used for transmission)

/** Confirmation of receipt required from target node. */
#define DATA_TRANSMISSION_FLAG_MASK_ACK			1

/** Message content to be encrypted using security key (set with KEY). */
#define DATA_TRANSMISSION_FLAG_MASK_SECURITY	2

/** Message to be sent to all Router nodes in the network. */
#define DATA_TRANSMISSION_FLAG_MASK_BROADCAST	4

/** Message to be sent with deferred responses PKS and PKF disabled. */
#define DATA_TRANSMISSION_FLAG_MASK_SILENT		8

// List of Jennic Command

/** Each command or event of jennic AT has a length of 3. */
#define LENGTH_OF_JENNIC_AT_COMMAND				3

// -> Init

/** Configures general network parameters on node. */
#define JENNIC_CMD_CFG							"CFG"

/** Configures certain network parameters on node. */
#define JENNIC_CMD_CONFIGURE_NETWORK_PARAMETERS "CFP"

/** Configures and initialises the device. */
#define JENNIC_CMD_INI							"INI"

/** Starts the device as the specified node type. */
#define JENNIC_CMD_START						"STR"

/** Reset the jennic device. */
#define JENNIC_CMD_RESET						"RST"

// -> Command

/** Sends message to the specified target node. */
#define JENNIC_CMD_SEND_DATA					"SND"


// -> Event

/**
 * Network has started or been joined successfully.
 * This response is received on the joining node.
 */
#define JENNIC_NETWORK_STARTED					"NTU"

/** A stack reset has occurred. */
#define JENNIC_RESET							"RST"

/** 
 * Event when data is received.
 * Documentated at page 69 : AT-Jenie 1.7
 */
#define JENNIC_RECEIVE_DATA						"DAT"

/** 
 * A node has joined this Co-ordinator or Router. 
 * This response is received on the parent node
 */
#define JENNIC_CHILD_JOINED						"CHJ"

/**
 * A child node has left this Co-ordinator or Router.
 */
#define JENNIC_CHILD_LEAVE						"CHL"

// -> Tunneling

/**
 * Connects a tunnel from the specified local service to the tunnelling service (Service 32)
 * on the specified remote node. Note that these services do not need to be bound. */
#define JENNIC_TUNNEL_CONNECTION				"TCN"

/**
 * Opens a communication channel in a tunnel set up using TCN. The TOP command must
 * be executed on the remote node, and sent to the node as a tunnelled command using TCM.
 */
#define JENNIC_TUNNEL_OPEN						"TOP"

/**
 * Sends an AT-Jenie command string through a tunnel to a remote node, where the tunnel has
 * been previously set up using TCN. 
 */
#define JENNIC_TUNNEL_SEND_COMMAND				"TCM"

/**
 * Closes a communication channel in a tunnel previously opened using TOP. The TCL command
 * must be executed on the remote node, and sent to the node as a tunnelled command using TCM.
 */
#define JENNIC_TUNEL_CLOSE						"TCL"

// -> Pins

/**
 * Defines which DIO pins (DIO0-DIO20) are inputs and which are outputs. Note that the command has
 * no effect for a pin being used by an enabled on-chip peripheral.
 */
#define JENNIC_PIN_CONFIGURE_IO					"PDD"

/** 
 * Sets the output status (on or off) of the DIO pins (DIO0-DIO20). Note that the command has no
 * effect for a pin not configured as an output or being used by an enabled on-chip peripheral.
 */
#define JENNIC_PIN_WRITE_PIN					"PDO"

// INIT

/**
* Init the streams used by Jennic
*/
void initJennic5139Streams( InputStream* aZigbeeInputStream,
							OutputStream* aZigbeeOutputStream,
							OutputStream* aDebugOutputStream);

/**
* Initialize a Jennic 1539 as a role of coordinater.
*/
void initJennic5139Coordinater();

/**
* Initialize a Jennic 1539 as a role of router.
*/
void initJennic5139Router();

// WAIT FOR DATA 

void waitAndCopyFromZigbeeToDebug(int delayMilliSecond);

/**
* Search after the beginning of DAT,0006066005651610211,0,3,
* Data will be for example 0102AA (size of 3)
* followed by \n
*/
BOOL copyFromZigbeeToDebugRetainingData();

/**
* Contains the outputStream used to build data which will be included in the commandBuffer.
*/
OutputStream* getAsciiDataOutputStream();

// COMMAND

/**
 * Show to the debug OutputStream that a command is sending
 * send the command to the zigbee and to debug stream
 * wait a delay to ensure the command was handled by the system
 */
void sendJennic5139CommandFromBuffer();

/**
* Send a data to the remote Jennic. The function will
* wrap as a command the data
* Ex : SND,0006066005650518898,0102AA,3,0
* @param inputStream the inputStream from which we copy the data to broadcast
* @param macAddress 64-bit IEEE/MAC address (set to 0 for a broadcast, when enabled
using flag, or to send to Co-ordinator)
* @param flags 
*/
void sendJennic5138DataBuffer(InputStream* inputStream, char* macAddress, int flags);

// RESET

/**
 * Send a reset Command to Jennic.
 */
void jennic5139Reset();

// LIGHT

/**
* off or on the light of the local zigbee.
*/
void jennic5139LocalLight(int pinMask, BOOL on) ;

/**
* off or on the light of the remote node.
*/
void jennic5139RemoteLight(char* jennicAddress, int pinMask, BOOL light);

#endif
