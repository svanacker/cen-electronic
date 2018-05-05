#include "navigationDebug.h"

#include "navigation.h"
#include "locationListDebug.h"
#include "pathListDebug.h"

#include "../common/io/outputStream.h"

void printNavigationContext(Navigation* navigation, OutputStream* outputStream) {
    printLocationListTable(outputStream, navigation->locationList);
    printPathListTable(outputStream, navigation->paths);
}