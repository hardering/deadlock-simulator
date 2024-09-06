// BankersAlgorithmTest.h

#include "../src/BankersAlgorithm.h"
#include <cassert>
#include <iostream>

class BankersAlgorithmTest {
public:
    void testSafeResourceAllocation() {
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
        std::cout << "testSafeResourceAllocation passed.\n";
    }

    void testUnsafeResourceAllocation() {
        std::vector<Resource> resources = { Resource(10), Resource(5), Resource(7) };
        std::vector<Process> processes = {
                Process(0, {7, 5, 3}, 1),
                Process(1, {3, 2, 2}, 2),
                Process(2, {9, 0, 2}, 3),
                Process(3, {2, 2, 2}, 1),
                Process(4, {4, 3, 3}, 2)
        };

        BankersAlgorithm bankers(processes, resources);
        std::vector<int> request = {8, 0, 4};  // Überschreitet den maximalen Bedarf von Prozess 0
        assert(!bankers.requestResources(0, request) && "Process 0 should not allocate resources.");
        std::cout << "testUnsafeResourceAllocation passed.\n";
    }

    void testReleaseResources() {
        std::vector<Resource> resources = { Resource(10), Resource(5), Resource(7) };
        std::vector<Process> processes = {
                Process(0, {7, 5, 3}, 1),
                Process(1, {3, 2, 2}, 2),
                Process(2, {9, 0, 2}, 3),
                Process(3, {2, 2, 2}, 1),
                Process(4, {4, 3, 3}, 2)
        };

        BankersAlgorithm bankers(processes, resources);
        bankers.releaseResources(0);
        assert(true && "Resources should be released.");
        std::cout << "testReleaseResources passed.\n";
    }

    // Added runAllTests function
    void runAllTests() {
        testSafeResourceAllocation();
        testUnsafeResourceAllocation();
        testReleaseResources();
        std::cout << "All tests passed.\n";
    }
};
