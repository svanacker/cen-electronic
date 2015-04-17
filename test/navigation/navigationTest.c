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

// Path Finding 1

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
static Location* tmpLocation;

static PathData* pathAB;
static PathData* pathBF;
static PathData* pathFI;
static PathData* pathIJ;
static PathData* pathAC;
static PathData* pathCG;
static PathData* pathCH;
static PathData* pathHD;
static PathData* pathHJ;
static PathData* pathEJ;
static PathData* pathAE;

// Path Finding 2
static Location* locationS;
static Location* locationU;
static Location* locationX;
static Location* locationV;
static Location* locationY;

static PathData* pathSU;
static PathData* pathUV;
static PathData* pathVY;
static PathData* pathYV;
static PathData* pathXY;
static PathData* pathXU;
static PathData* pathUX;
static PathData* pathSX;
static PathData* pathXV;
static PathData* pathYS;

#define NAVIGATION_LOCATION_LIST_TEST_ARRAY_LENGTH        30
#define NAVIGATION_PATH_LIST_TEST_ARRAY_LENGTH        15
#define BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH             10

static LocationList locationList;
static Location locationListArray[NAVIGATION_LOCATION_LIST_TEST_ARRAY_LENGTH];

static PathList pathList;
static PathData pathListArray[NAVIGATION_PATH_LIST_TEST_ARRAY_LENGTH];

static BitList outgoingPathBitList;
static unsigned int outgoingPathBitArray[BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH];
static BitList availablePathBitList;
static unsigned int availablePathBitArray[BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH];

// FORWARD DECLARATION
void checkNavigationPathFinding1(void);
void checkNavigationPathFinding2(void);
void addStrategyPaths(void);

void navigationTestSuite(void) {
    RUN_TEST(checkNavigationPathFinding1);
    RUN_TEST(checkNavigationPathFinding2);
}

void initNavigationTest() {
    initLocationList(&locationList, (Location(*)[]) &locationListArray, NAVIGATION_LOCATION_LIST_TEST_ARRAY_LENGTH);
    initPathList(&pathList, (PathData(*)[]) &pathListArray, NAVIGATION_PATH_LIST_TEST_ARRAY_LENGTH);
    initBitList(&outgoingPathBitList, (unsigned int(*)[]) &outgoingPathBitArray, BIT_LIST_NAVIGATION_ARRAY_LENGTH);
    initBitList(&availablePathBitList, (unsigned int(*)[]) &availablePathBitArray, BIT_LIST_NAVIGATION_ARRAY_LENGTH);

    initNavigation(&locationList, &pathList, &outgoingPathBitList, &availablePathBitList);
}

void checkNavigationPathFinding1(void) {
    initNavigationTest();

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

    pathAB = addNavigationPath(locationA, locationB, 85, 0, 0, 0, 0, 0, 0);
    pathBF = addNavigationPath(locationB, locationF, 80, 0, 0, 0, 0, 0, 0);
    pathFI = addNavigationPath(locationF, locationI, 250, 0, 0, 0, 0, 0, 0);
    pathIJ = addNavigationPath(locationI, locationJ, 84, 0, 0, 0, 0, 0, 0);
    pathAC = addNavigationPath(locationA, locationC, 217, 0, 0, 0, 0, 0, 0);
    pathCG = addNavigationPath(locationC, locationG, 186, 0, 0, 0, 0, 0, 0);
    pathCH = addNavigationPath(locationC, locationH, 103, 0, 0, 0, 0, 0, 0);
    pathHD = addNavigationPath(locationH, locationD, 183, 0, 0, 0, 0, 0, 0);
    pathHJ = addNavigationPath(locationH, locationJ, 167, 0, 0, 0, 0, 0, 0);
    pathEJ = addNavigationPath(locationE, locationJ, 502, 0, 0, 0, 0, 0, 0);
    pathAE = addNavigationPath(locationA, locationE, 173, 0, 0, 0, 0, 0, 0);

    // printPathList(getInfoOutputStreamLogger(), "Paths definition", getNavigationPathList());

    int actual = computeBestPath(locationA, locationJ);

    // The shortest distance in this example is 487 (A-E-J)
    TEST_ASSERT_EQUAL(487, actual);

    // TEST IF WE GO TO J !
    tmpLocation = locationA->resultNextLocation;
    TEST_ASSERT_EQUAL(locationE, tmpLocation);

    tmpLocation = tmpLocation->resultNextLocation;
    TEST_ASSERT_EQUAL(locationJ, tmpLocation);

    tmpLocation = tmpLocation->resultNextLocation;
    TEST_ASSERT_NULL(tmpLocation);

    // Renew Computation to be sure that it's reentrant
    actual = computeBestPath(locationA, locationJ);

    // The shortest distance in this example is 487 (A-E-J)
    TEST_ASSERT_EQUAL(487, actual);
}

void checkNavigationPathFinding2(void) {
    initNavigationTest();

    // locations
    locationS = addNavigationLocation("S", 0, 0);
    locationU = addNavigationLocation("U", 0, 0);
    locationX = addNavigationLocation("X", 0, 0);
    locationV = addNavigationLocation("V", 0, 0);
    locationY = addNavigationLocation("Y", 0, 0);

    // paths
    pathSU = addNavigationPath(locationS, locationU, 10, 0, 0, 0, 0, 0, 0);
    pathUV = addNavigationPath(locationU, locationV, 1, 0, 0, 0, 0, 0, 0);
    pathVY = addNavigationPath(locationV, locationY, 4, 0, 0, 0, 0, 0, 0);
    pathYV = addNavigationPath(locationY, locationV, 6, 0, 0, 0, 0, 0, 0);
    pathXY = addNavigationPath(locationX, locationY, 2, 0, 0, 0, 0, 0, 0);
    pathXU = addNavigationPath(locationX, locationU, 3, 0, 0, 0, 0, 0, 0);
    pathUX = addNavigationPath(locationU, locationX, 2, 0, 0, 0, 0, 0, 0);
    pathSX = addNavigationPath(locationS, locationX, 5, 0, 0, 0, 0, 0, 0);
    pathXV = addNavigationPath(locationX, locationV, 9, 0, 0, 0, 0, 0, 0);
    pathYS = addNavigationPath(locationY, locationS, 7, 0, 0, 0, 0, 0, 0);

    // First test
    int actual = computeBestPath(locationS, locationS);
    TEST_ASSERT_EQUAL(0, actual);

    // Second test : ignore in implementation the sens of location (we find the min cost between A->B or B->A
    actual = computeBestPath(locationS, locationY);
    TEST_ASSERT_EQUAL(7, actual);

    // Third test : ignore in implementation the sens of location (we find the min cost between A->B or B->A
    actual = computeBestPath(locationY, locationS);
    TEST_ASSERT_EQUAL(7, actual);

    // Last Test : S->Y->V : problem !!!
    actual = computeBestPath(locationS, locationV);
    TEST_ASSERT_EQUAL(8, actual);

}