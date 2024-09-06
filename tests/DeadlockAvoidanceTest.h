#ifndef DEADLOCK_AVOIDANCE_TEST_H
#define DEADLOCK_AVOIDANCE_TEST_H

#include <iostream>
#include "DeadlockAvoidance.h"

class DeadlockAvoidanceTest {
public:
    void runAllTests() {
        testRequestAllResourcesAtOnce();
        testPreemptResources();
        testRequestResourcesInOrder();
    }

private:
    void testRequestAllResourcesAtOnce();

    void testPreemptResources();

    void testRequestResourcesInOrder();
};

#endif
