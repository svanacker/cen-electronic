#include "pathListTest.h"

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"

#include "../../test/unity/unity.h"

static PathList pathList;
#define PATH_LIST_ARRAY_TEST        10
static PathData pathDataListArray[PATH_LIST_ARRAY_TEST];

// Forward Declaration
void pathListTest(void);

void pathListTestSuite(void) {
    RUN_TEST(pathListTest);
}

void pathListTest(void) {
    initPathList(&pathList, (PathData(*)[]) &pathDataListArray, PATH_LIST_ARRAY_TEST);

    Location locationA;
    Location locationB;
    Location locationC;
    Location locationD;
    Location locationE;

    PathData* pathDataAB;
    PathData* pathDataAC;
    PathData* pathDataBD;
    PathData* tmpPathData;

    initLocation(&locationA, LOCATION_USAGE_TYPE_PERMANENT, "A", "A", 0, 0);
    initLocation(&locationB, LOCATION_USAGE_TYPE_PERMANENT, "B", "B", 0, 0);
    initLocation(&locationC, LOCATION_USAGE_TYPE_PERMANENT, "C", "C", 0, 0);
    initLocation(&locationD, LOCATION_USAGE_TYPE_PERMANENT, "D", "D", 0, 0);
    initLocation(&locationE, LOCATION_USAGE_TYPE_PERMANENT, "E", "E", 0, 0);

    pathDataAB = addPath(&pathList);
    initPathData(pathDataAB, PATH_DATA_USAGE_TYPE_PERMANENT, &locationA, &locationB, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    pathDataAC = addPath(&pathList);
    initPathData(pathDataAC, PATH_DATA_USAGE_TYPE_PERMANENT, &locationA, &locationC, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    pathDataBD = addPath(&pathList);
    initPathData(pathDataBD, PATH_DATA_USAGE_TYPE_PERMANENT, &locationB, &locationD, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    // getPath
    tmpPathData = getPath(&pathList, 2);
    TEST_ASSERT_EQUAL(pathDataBD, tmpPathData);
    
    // getPathCount
    unsigned pathCount = getPathCount(&pathList);
    TEST_ASSERT_EQUAL(3, pathCount);

    // getPathOfLocations
    tmpPathData = getPathOfLocations(&pathList, &locationB, &locationE);
    TEST_ASSERT_EQUAL(NULL, tmpPathData);
    
    tmpPathData = getPathOfLocations(&pathList, &locationA, &locationC);
    TEST_ASSERT_EQUAL(pathDataAC, tmpPathData);
}
