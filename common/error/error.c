#include "error.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

// Liste of error Code

void writeError(int errorCode) {
    OutputStream* outputStream = getErrorOutputStreamLogger();
    appendString(outputStream, "ERR CODE:");
	appendHex4(outputStream, errorCode);
    println(outputStream);
}

