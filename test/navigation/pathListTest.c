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

    initLocation(&locationA, "A", 0, 0);
    initLocation(&locationB, "B", 0, 0);
    initLocation(&locationC, "C", 0, 0);
    initLocation(&locationD, "D", 0, 0);
    initLocation(&locationE, "E", 0, 0);

    pathDataAB = addPath(&pathList);
    initPathData(pathDataAB, &locationA, &locationB, 0, 0, 0, 0, 0, 0, 0);

    pathDataAC = addPath(&pathList);
    initPathData(pathDataAC, &locationA, &locationC, 0, 0, 0, 0, 0, 0, 0);

    pathDataBD = addPath(&pathList);
    initPathData(pathDataBD, &locationB, &locationD, 0, 0, 0, 0, 0, 0, 0);

    // getPath
    tmpPathData = getPath(&pathList, 2);
    TEST_ASSERT_EQUAL(pathDataBD, tmpPathData);
    
    // getPathCount
    unsigned pathCount = getPathCount(&pathList);
    TEST_ASSERT_EQUAL(3, pathCount);

    // getPathOfLocations
    bool reversed;
    tmpPathData = getPathOfLocations(&pathList, &locationB, &locationE, &reversed);
    TEST_ASSERT_EQUAL(NULL, tmpPathData);
    TEST_ASSERT_FALSE(reversed);
    
    tmpPathData = getPathOfLocations(&pathList, &locationA, &locationC, &reversed);
    TEST_ASSERT_EQUAL(pathDataAC, tmpPathData);
    TEST_ASSERT_FALSE(reversed);

    tmpPathData = getPathOfLocations(&pathList, &locationB, &locationA, &reversed);
    TEST_ASSERT_EQUAL(pathDataAB, tmpPathData);
    TEST_ASSERT_TRUE(reversed);
}
