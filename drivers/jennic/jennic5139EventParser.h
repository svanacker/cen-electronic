#ifndef JENNIC_5139_EVENT_PARSER_H
#define JENNIC_5139_EVENT_PARSER_H

#define JENNIC_SEARCH_DATA_RAW_INPUT_BUFFER_LENGTH		60
#define JENNIC_SEARCH_DATA_BUFFER_LENGTH				60
#define JENNIC_DATA_INPUT_BUFFER_LENGTH					30

// forward declaration
struct JennicEvent;
typedef struct JennicEvent JennicEvent;

/**
 * The function which must be called when a such event is found.
 * @param jennicEvent
 */
typedef void JennicEventFunction(JennicEvent* jennicEvent);

/**
 * Define the structure of an event which must be parse.
 */
struct JennicEvent {
	/** The event (3 characters) to find. */
	char eventCommand[LENGTH_OF_JENNIC_AT_COMMAND];
	/** String after address. */
	char* beforeAddress;
	/** The number of char before the address (eventCommand + length(beforeAddress)). */
	char charBeforeAddressCount;
	/** The address of the event (if needed). */
	char* jennicAddress;
	/** The arguments. */
	char* arguments;
    /** The function which must be called when a such event is found. */
    JennicEventFunction* onEvent;
	/** Indicates that we are in payload data if value >= 0. If value = -1, payload search is disabled. */
	unsigned char payLoadArgumentIndex;
};

#define NO_PAY_LOAD 	-1

/** The maximal number of event which can be parsed. */
#define MAX_JENNIC_EVENT 10

/**
 * The struct defining a list of jennic Event.
 */
typedef struct {
    /** An array of pointer on device Descriptor. */
    JennicEvent* events[MAX_JENNIC_EVENT];
	/** Current jennicEvent which currently match with the event. */
	JennicEvent* matchEvent;
	/** Contains the buffer used to search data sent by the other jennic. */
	Buffer searchDataBuffer;
	/** Contains the raw data sent by the jennic. */
	Buffer dataRawInputBuffer;
	/** Contains the "interesting data" sent by the jennic as raw. */
	Buffer dataInputBuffer;
	/** Retains the index of block which is correct. */
	unsigned int dataBlockBeginMatchIndex;
    /** the size of the list. */
    unsigned char size;
	/** Current Argument Index : argument are separated by comma. */
	char currentArgumentIndex;

} JennicEventList;

/**
 * Initialisation
 */
void initJennicEventList();

/**
 * Add a jennic Event parser to the list.
 * @param jennicEvent the event to add.
 */
void addJennicEvent(JennicEvent* jennicEvent,
					 char* eventCommand,
					 char* beforeAddress,
					 char* jennicAddress,
					 char* arguments,
					 char payLoadArgumentIndex,
					JennicEventFunction* onEvent);
/**
 * Handle the next Jennic char and try to detect some input (EVENT, DATA ...)
 */
void handleJennicNextChar(char c);

/**
* Get a buffer from the router arround in data. 
* The inData is a result of raw data parsing from the Jennic AT Commands.
*/
Buffer* getJennicInDataBuffer();

// DEBUG

/**
 * Print the eventList.
 */
void printJennicEventList(OutputStream* outputStream);

#endif
