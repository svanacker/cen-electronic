#include "adcutils.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define ANX_COUNT                               6

#define ADC_DEBUG_IDX_COLUMN_LENGTH	            5
#define ADC_DEBUG_HEX_VALUE_COLUMN_LENGTH	    10
#define ADC_DEBUG_VALUE_COLUMN_LENGTH	        10

int getANXCount() {
    return ANX_COUNT;
}

/**
* Private.
*/
void printAdcListHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "idx", ADC_DEBUG_IDX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Hex Value", ADC_DEBUG_HEX_VALUE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Value (mV)", ADC_DEBUG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
	appendTableHeaderSeparatorLine(outputStream);
}

void printAdc(OutputStream* outputStream, int index, int value) {
	appendDecTableData(outputStream, index, ADC_DEBUG_IDX_COLUMN_LENGTH);
	appendHex4TableData(outputStream, value, ADC_DEBUG_HEX_VALUE_COLUMN_LENGTH);
	appendDecTableData(outputStream, value, ADC_DEBUG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
}

void printAdcList(OutputStream* outputStream) {
	printAdcListHeader(outputStream);
    int i;
    int anxCount = getANXCount();
    for (i = 1; i <= anxCount; i++) {
        int value = getANX(i);
        printAdc(outputStream, i, value);
    }
	appendTableHeaderSeparatorLine(outputStream);
}
