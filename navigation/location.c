#include <stdlib.h>
#include <string.h>

#include "location.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/string/cenString.h"

#include "location.h"

bool locationEquals(Location* location1, Location* location2) {
    return (strcmp(location1->name, location2->name) == 0);
}
