#include "robotConfig.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define ROBOT_CONFIG_KEY_COLUMN_LENGTH				30
#define ROBOT_CONFIG_VALUE_COLUMN_LENGTH            20
#define ROBOT_CONFIG_LAST_COLUMN					24


void initRobotConfig(RobotConfig* robotConfig,
                robotConfigReadIntFunction* robotConfigReadInt, robotConfigWriteIntFunction* robotConfigWriteInt){
    robotConfig->robotConfigReadInt = robotConfigReadInt;
    robotConfig->robotConfigWriteInt = robotConfigWriteInt;
}

/**
* Private.
*/
void printRobotConfiguDebugHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Config Key", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Config Value", ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);
	appendTableHeaderSeparatorLine(outputStream);
}

void printRobotTableConfig(OutputStream* outputStream, RobotConfig* robotConfig) {
	printRobotConfiguDebugHeader(outputStream);

	unsigned int configValue = robotConfig->robotConfigReadInt(robotConfig);

	// Strategy Index
	appendStringTableData(outputStream, "Strategy Index", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendDecTableData(outputStream, configValue & CONFIG_STRATEGY_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	// Wait For Start
	appendStringTableData(outputStream, "Don't wait For Start", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_DONT_WAIT_FOR_START, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	appendTableHeaderSeparatorLine(outputStream);

	// Do not end
	appendStringTableData(outputStream, "Do not end", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_DO_NOT_END, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	// rolling test
	appendStringTableData(outputStream, "Rolling Test", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_ROLLING_TEST_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	// Don't use Beacon
	appendStringTableData(outputStream, "Don't use Beacon", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_DONT_USE_BEACON_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	// Green color
	appendStringTableData(outputStream, "Green Color", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_COLOR_GREEN_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	appendTableHeaderSeparatorLine(outputStream);

	// Low Speed
	appendStringTableData(outputStream, "Low Speed", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_SPEED_LOW_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	// Very Low Speed
	appendStringTableData(outputStream, "Very Low Speed", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_SPEED_VERY_LOW_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	// Ultra Low Speed
	appendStringTableData(outputStream, "Ultra Low Speed", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_SPEED_ULTRA_LOW_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	appendTableHeaderSeparatorLine(outputStream);

}