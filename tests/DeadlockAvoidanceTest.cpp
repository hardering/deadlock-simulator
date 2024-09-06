#include "DeadlockAvoidanceTest.h"
#include "DeadlockAvoidance.h"
#include <vector>

void DeadlockAvoidanceTest::testRequestAllResourcesAtOnce() {
    std::vector<Resource> resources = {Resource(6), Resource(4), Resource(7)};
    std::vector<Process> processes = {
            Process(0, {3, 2, 2}, 1)
    };

    DeadlockAvoidance avoidance;
    bool result = avoidance.requestAllResourcesAtOnce(processes[0], resources);
    if (result) {
        std::cout << "Process 0 allocated all resources at once.\n";
    } else {
        std::cout << "Process 0 cannot allocate all resources.\n";
    }
}

void DeadlockAvoidanceTest::testPreemptResources() {
    std::vector<Resource> resources = {Resource(6), Resource(4), Resource(7)};
    std::vector<Process> processes = {
            Process(0, {3, 2, 2}, 1),
            Process(1, {2, 2, 2}, 2)
    };

    DeadlockAvoidance avoidance;
    bool result = avoidance.preemptResources(processes[1], processes, resources);
    if (result) {
        std::cout << "Process 1 preempted resources successfully.\n";
    } else {
        std::cout << "Process 1 failed to preempt resources.\n";
    }
}

void DeadlockAvoidanceTest::testRequestResourcesInOrder() {
    std::vector<Resource> resources = {Resource(6), Resource(4), Resource(7)};
    std::vector<Process> processes = {
            Process(2, {3, 1, 3}, 3)
    };

    DeadlockAvoidance avoidance;
    bool result = avoidance.requestResourcesInOrder(processes[0], resources);
    if (result) {
        std::cout << "Process 2 allocated resources in order.\n";
    } else {
        std::cout << "Process 2 cannot allocate resources in order.\n";
    }
}
