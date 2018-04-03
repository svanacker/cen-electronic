#include "colorSensorDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "colorSensor.h"

#define COLOR_SENSOR_R_COLUMN_LENGTH             10
#define COLOR_SENSOR_G_COLUMN_LENGTH             10
#define COLOR_SENSOR_B_COLUMN_LENGTH             10
#define COLOR_SENSOR_LAST_COLUMN		         60

/**
* Private.
*/
void printColorSensorDebugTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "R", COLOR_SENSOR_R_COLUMN_LENGTH);
    appendStringHeader(outputStream, "G", COLOR_SENSOR_G_COLUMN_LENGTH);
    appendStringHeader(outputStream, "B", COLOR_SENSOR_B_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, COLOR_SENSOR_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);
}


void printColorSensorTable(OutputStream* outputStream, ColorSensor* colorSensor) {
    printColorSensorDebugTableHeader(outputStream);
    Color* color = colorSensor->colorSensorReadValue(colorSensor);
    appendDecTableData(outputStream, color->R, COLOR_SENSOR_R_COLUMN_LENGTH);
    appendDecTableData(outputStream, color->G, COLOR_SENSOR_R_COLUMN_LENGTH);
    appendDecTableData(outputStream, color->B, COLOR_SENSOR_R_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, COLOR_SENSOR_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
}
