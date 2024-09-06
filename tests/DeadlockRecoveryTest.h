#ifndef DEADLOCK_RECOVERY_TEST_H
#define DEADLOCK_RECOVERY_TEST_H

#include <iostream>
#include "DeadlockRecovery.h"

class DeadlockRecoveryTest {
public:
    void runAllTests() {
        testInterruptStrategy();
        testRollbackStrategy();
        testAbortStrategy();
    }

private:
    void testInterruptStrategy();

    void testRollbackStrategy();

    void testAbortStrategy();
};

#endif
