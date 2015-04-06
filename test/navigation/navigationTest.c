#include "navigationTest.h"

/**
 * Navigation Location and Path tests from wikipedia
 * http://fr.wikipedia.org/wiki/Algorithme_de_Dijkstra
 */

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"
#include "../../navigation/navigation.h"

#include "../../common/string/cenString.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../test/unity/unity.h"

static Location* locationA;
static Location* locationB;
static Location* locationC;
static Location* locationD;
static Location* locationE;
static Location* locationF;
static Location* locationG;
static Location* locationH;
static Location* locationI;
static Location* locationJ;

static PathData pathAB;
static PathData pathBF;
static PathData pathFI;
static PathData pathIJ;
static PathData pathAC;
static PathData pathCG;
static PathData pathCH;
static PathData pathHD;
static PathData pathHJ;
static PathData pathEJ;
static PathData pathAE;

static LocationList resultLocationList;

// FORWARD DECLARATION
void addNavigationLocations(void);
void addStrategyPaths(void);

void navigationTestSuite(void) {
    RUN_TEST(addNavigationLocations);
}

void addNavigationLocations(void) {
    initNavigation();

    // locations
    locationA = addNavigationLocation("A", 0, 0);
    locationB = addNavigationLocation("B", 0, 0);
    locationC = addNavigationLocation("C", 0, 0);
    locationD = addNavigationLocation("D", 0, 0);
    locationE = addNavigationLocation("E", 0, 0);
    locationF = addNavigationLocation("F", 0, 0);
    locationG = addNavigationLocation("G", 0, 0);
    locationH = addNavigationLocation("H", 0, 0);
    locationI = addNavigationLocation("I", 0, 0);
    locationJ = addNavigationLocation("J", 0, 0);

    addStrategyPaths();

    printPathList(getInfoOutputStreamLogger(), "Paths definition", getNavigationPathList());

    int actual = computeBestPath(locationA, locationJ);

    printLocationList(getInfoOutputStreamLogger(), "Result=", &resultLocationList);

    // The shortest distance in this example is 487 (A-E-J)
    TEST_ASSERT_EQUAL(487, actual);
}

// paths
    
void addStrategyPaths(void) {
    addNavigationPath(&pathAB, locationA, locationB, 85, 0, 0, 0, 0, 0, 0);
    addNavigationPath(&pathBF, locationB, locationF, 80, 0, 0, 0, 0, 0, 0);

    addNavigationPath(&pathFI, locationF, locationI, 250, 0, 0, 0, 0, 0, 0);

    addNavigationPath(&pathIJ, locationI, locationJ, 84, 0, 0, 0, 0, 0, 0);

    addNavigationPath(&pathAC, locationA, locationC, 217, 0, 0, 0, 0, 0, 0);

    addNavigationPath(&pathCG, locationC, locationG, 186, 0, 0, 0, 0, 0, 0);


    addNavigationPath(&pathCH, locationC, locationH, 103, 0, 0, 0, 0, 0, 0);

    addNavigationPath(&pathHD, locationH, locationD, 183, 0, 0, 0, 0, 0, 0);

    addNavigationPath(&pathHJ, locationH, locationJ, 167, 0, 0, 0, 0, 0, 0);


    addNavigationPath(&pathEJ, locationE, locationJ, 502, 0, 0, 0, 0, 0, 0);

    addNavigationPath(&pathAE, locationA, locationE, 173, 0, 0, 0, 0, 0, 0);
}
