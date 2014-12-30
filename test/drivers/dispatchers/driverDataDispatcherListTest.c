#include <stdlib.h>

#include "../../../test/unity/unity.h"
#include "../../../common/error/error.h"

#include "../../../device/transmitMode.h"

#include "../../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../../drivers/dispatcher/localDriverDataDispatcher.h"

#include "driverDataDispatcherListTest.h"

#define DRIVER_DATA_DISPATCHER_LIST_TEST_ARRAY_LENGTH    2
static DriverDataDispatcher driverDataDispatcherListArray[DRIVER_DATA_DISPATCHER_LIST_TEST_ARRAY_LENGTH];

void driverDataDispatcherListTestSuite(void) {
    RUN_TEST(test_initDriverDataDispatcherList_should_fail_if_null_provided);
    RUN_TEST(test_initDriverDataDispatcherList_add_too_much_dispatchers);
    RUN_TEST(test_initDriverDataDispatcherList_find_dispatcher_by_transmit_mode);
}

void init_driverDataDispatcherList(void) {
    initDriverDataDispatcherList((DriverDataDispatcher(*)[]) &driverDataDispatcherListArray, DRIVER_DATA_DISPATCHER_LIST_TEST_ARRAY_LENGTH);
}

void test_initDriverDataDispatcherList_should_fail_if_null_provided(void) {
    initDriverDataDispatcherList(NULL, DRIVER_DATA_DISPATCHER_LIST_TEST_ARRAY_LENGTH);
    TEST_ASSERT_EQUAL(DISPATCHERS_LIST_NOT_INITIALIZED, getLastError());

    clearLastError();
    
    addLocalDriverDataDispatcher();
    TEST_ASSERT_EQUAL(DISPATCHERS_LIST_NOT_INITIALIZED, getLastError());
}

void test_initDriverDataDispatcherList_add_too_much_dispatchers(void) {
    init_driverDataDispatcherList();
    TEST_ASSERT_FALSE(isThereAnyError());
    TEST_ASSERT_EQUAL(0, getDriverDataDispatcherCount());

    // Add a first dispatcher
    DriverDataDispatcher* dispacher = addLocalDriverDataDispatcher();
    TEST_ASSERT_FALSE(isThereAnyError());
    TEST_ASSERT_EQUAL(1, getDriverDataDispatcherCount());
    // TEST_ASSERT_EQUAL(dispacher, getDriverDataDispatcherByIndex(0));
    
    // Add a second dispatcher
    dispacher = addLocalDriverDataDispatcher();
    TEST_ASSERT_FALSE(isThereAnyError());
    TEST_ASSERT_EQUAL(2, getDriverDataDispatcherCount());
    TEST_ASSERT_EQUAL(dispacher, getDriverDataDispatcherByIndex(1));

    dispacher = addLocalDriverDataDispatcher();
    TEST_ASSERT_EQUAL(TOO_MUCH_DRIVER_DATA_DISPATCHER, getLastError());
}

void test_initDriverDataDispatcherList_find_dispatcher_by_transmit_mode(void) {
    init_driverDataDispatcherList();

    // Must find the added Local Driver Data Dispatcher
    DriverDataDispatcher* dispacher = addLocalDriverDataDispatcher();
    DriverDataDispatcher* localDispatcher = getDriverDataDispatcherByTransmitMode(TRANSMIT_LOCAL, 0);
    TEST_ASSERT_EQUAL(localDispatcher, localDispatcher);

    // Must not find
    localDispatcher = getDriverDataDispatcherByTransmitMode(TRANSMIT_I2C, 0);
    TEST_ASSERT_EQUAL(NULL, localDispatcher);

    // Must not find
    localDispatcher = getDriverDataDispatcherByTransmitMode(TRANSMIT_LOCAL, -1);
    TEST_ASSERT_EQUAL(NULL, localDispatcher);
}