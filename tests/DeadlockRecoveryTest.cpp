#include "DeadlockRecoveryTest.h"
#include "DeadlockRecovery.h"
#include <vector>

void DeadlockRecoveryTest::testInterruptStrategy() {
    std::vector<Resource> resources = {Resource(6), Resource(4), Resource(7)};
    std::vector<Process> processes = {
            Process(0, {3, 2, 2}, 1),
            Process(1, {2, 2, 2}, 2)
    };

    DeadlockRecovery recovery;
    recovery.resolveDeadlock(processes, resources, "interrupt");
    std::cout << "Interrupt strategy applied.\n";
}

void DeadlockRecoveryTest::testRollbackStrategy() {
    std::vector<Resource> resources = {Resource(6), Resource(4), Resource(7)};
    std::vector<Process> processes = {
            Process(0, {3, 2, 2}, 1),
            Process(1, {2, 2, 2}, 2)
    };

    DeadlockRecovery recovery;
    recovery.resolveDeadlock(processes, resources, "rollback");
    std::cout << "Rollback strategy applied.\n";
}

void DeadlockRecoveryTest::testAbortStrategy() {
    std::vector<Resource> resources = {Resource(6), Resource(4), Resource(7)};
    std::vector<Process> processes = {
            Process(0, {3, 2, 2}, 1),
            Process(1, {2, 2, 2}, 2)
    };

    DeadlockRecovery recovery;
    recovery.resolveDeadlock(processes, resources, "abort");
    std::cout << "Abort strategy applied.\n";
}
