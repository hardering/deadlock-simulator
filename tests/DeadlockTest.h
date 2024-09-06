// DeadlockTest.h

#include "../src/BankersAlgorithm.h"
#include <cassert>

class DeadlockTest {
public:
    void testDeadlockDetection() {
        std::vector<Resource> resources = { Resource(10), Resource(5), Resource(7) };
        std::vector<Process> processes = {
                Process(0, {7, 5, 3}, 1),
                Process(1, {3, 2, 2}, 2),
                Process(2, {9, 0, 2}, 3),
                Process(3, {2, 2, 2}, 1),
                Process(4, {4, 3, 3}, 2)
        };

        BankersAlgorithm bankers(processes, resources);
        std::vector<int> request = {1, 0, 2};
        assert(bankers.requestResources(0, request) && "Process 0 should allocate resources.");
    }
};
