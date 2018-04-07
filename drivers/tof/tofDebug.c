#include "tofDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "tof.h"
#include "tofList.h"

#define TOF_SENSOR_INDEX_COLUMN_LENGTH		      10
#define TOF_SENSOR_VALUE_DEC_COLUMN_LENGTH        20
#define TOF_SENSOR_VALUE_HEX_COLUMN_LENGTH        20
#define TOF_SENSOR_LAST_COLUMN		              40

/**
* Private.
*/
void printTofSensorDebugTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Index", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dist (mm)", TOF_SENSOR_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dist (mm) / Hex", TOF_SENSOR_VALUE_HEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);
}

void printTofSensorTable(OutputStream* outputStream, TofSensorList* tofSensorList) {
    printTofSensorDebugTableHeader(outputStream);
    unsigned int index;
    for (index = 0; index < tofSensorList->size; index++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);
        unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);

        appendDecTableData(outputStream, index, TOF_SENSOR_INDEX_COLUMN_LENGTH);
        appendDecTableData(outputStream, distance, TOF_SENSOR_VALUE_DEC_COLUMN_LENGTH);
        appendHex4TableData(outputStream, distance, TOF_SENSOR_VALUE_HEX_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    }

    appendTableHeaderSeparatorLine(outputStream);
}
