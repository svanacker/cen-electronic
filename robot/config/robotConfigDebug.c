#include "robotConfigDebug.h"
#include <stdbool.h>

#include "../../common/io/binaryPrintWriter.h"
#include "../../common/io/outputStream.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define ROBOT_CONFIG_KEY_COLUMN_LENGTH				35
#define ROBOT_CONFIG_MASK_COLUMN_LENGTH             22
#define ROBOT_CONFIG_VALUE_COLUMN_LENGTH            15
#define ROBOT_CONFIG_LAST_COLUMN					35

/**
* Private.
*/
void printRobotConfiguDebugHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Config Key", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Binary Mask", ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Config Value", ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);
	appendTableHeaderSeparatorLine(outputStream);
}

void printRobotTableConfig(OutputStream* outputStream, RobotConfig* robotConfig) {
	printRobotConfiguDebugHeader(outputStream);

	unsigned int configValue = robotConfig->robotConfigReadInt(robotConfig);

	// Strategy Index
	appendStringTableData(outputStream, "Strategy Index", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBinary16TableData(outputStream, CONFIG_STRATEGY_MASK, 4, ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendDecTableData(outputStream, configValue & CONFIG_STRATEGY_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);

    // Start Match / End Match
	// Wait For Start
	appendStringTableData(outputStream, "Don't wait For Start", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBinary16TableData(outputStream, CONFIG_DONT_WAIT_FOR_START, 4, ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_DONT_WAIT_FOR_START, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	// Do not end
	appendStringTableData(outputStream, "Do not end", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBinary16TableData(outputStream, CONFIG_DO_NOT_END, 4, ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_DO_NOT_END, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);

	// Sonar FAR
	appendStringTableData(outputStream, "Sonar FAR", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBinary16TableData(outputStream, CONFIG_SONAR_FAR_MASK, 4, ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_SONAR_FAR_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

    // Sonar NEAR
	appendStringTableData(outputStream, "Sonar NEAR", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBinary16TableData(outputStream, CONFIG_SONAR_NEAR_MASK, 4, ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_SONAR_NEAR_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);
    
    appendTableHeaderSeparatorLine(outputStream);

	// Violet color
	appendStringTableData(outputStream, "Violet Color", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBinary16TableData(outputStream, CONFIG_COLOR_YELLOW_MASK, 4, ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_COLOR_YELLOW_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	appendTableHeaderSeparatorLine(outputStream);

	// Low Speed
	appendStringTableData(outputStream, "Low Speed", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBinary16TableData(outputStream, CONFIG_SPEED_LOW_MASK, 4, ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_SPEED_LOW_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	// Very Low Speed
	appendStringTableData(outputStream, "Very Low Speed", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBinary16TableData(outputStream, CONFIG_SPEED_VERY_LOW_MASK, 4, ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_SPEED_VERY_LOW_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	// Ultra Low Speed
	appendStringTableData(outputStream, "Ultra Low Speed", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBinary16TableData(outputStream, CONFIG_SPEED_ULTRA_LOW_MASK, 4, ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_SPEED_ULTRA_LOW_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	appendTableHeaderSeparatorLine(outputStream);

    // Undefined Conf
	appendStringTableData(outputStream, "Undefined Conf", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBinary16TableData(outputStream, CONFIG_UNDEFINED_1_MASK, 4, ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_UNDEFINED_1_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);

	appendTableHeaderSeparatorLine(outputStream);

    // Debug Config
	appendStringTableData(outputStream, "Log Level Debug", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBinary16TableData(outputStream, CONFIG_DEBUG, 4, ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_DEBUG, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);
    
	appendTableHeaderSeparatorLine(outputStream);
    
	// LCD Backlight
	appendStringTableData(outputStream, "LCD BackLight", ROBOT_CONFIG_KEY_COLUMN_LENGTH);
	appendBinary16TableData(outputStream, CONFIG_LCD_MASK, 4, ROBOT_CONFIG_MASK_COLUMN_LENGTH);
	appendBoolTableData(outputStream, configValue & CONFIG_LCD_MASK, ROBOT_CONFIG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, ROBOT_CONFIG_LAST_COLUMN);
    
	appendTableHeaderSeparatorLine(outputStream);
}