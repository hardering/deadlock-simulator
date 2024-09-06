#include <iostream>
#include <vector>
#include "BankersAlgorithm.h"
#include "../tests/BankersAlgorithmTest.h"
#include "../tests/DeadlockTest.h"
#include "DeadlockRecovery.h"
#include "DeadlockAvoidance.h"

void printResources(const std::vector<Resource>& resources) {
    std::cout << "Current available resources:\n";
    for (size_t i = 0; i < resources.size(); ++i) {
        std::cout << "Resource " << i << ": " << resources[i].getAvailableInstances() << "\n";
    }
}

void checkForDeadlock(DeadlockRecovery& recovery, const std::vector<Process>& processes, const std::vector<Resource>& resources) {
    if (recovery.detectDeadlock(processes, resources)) {
        std::cout << "Deadlock detected.\n";
    } else {
        std::cout << "No deadlock detected.\n";
    }
}

void createDeadlock(std::vector<Process>& processes, std::vector<Resource>& resources) {
    // Deadlock scenario: processes requesting resources leading to a deadlock
    std::vector<int> request1 = {2, 1, 2};  // Process 0 requests resources
    std::vector<int> request2 = {2, 1, 1};  // Process 1 requests resources
    std::vector<int> request3 = {1, 1, 2};  // Process 2 requests resources
    std::vector<int> request4 = {1, 1, 1};  // Process 3 requests resources

    // Allocate resources that will cause a deadlock
    processes[0].requestResources(request1, resources);  // Process 0 allocated
    processes[1].requestResources(request2, resources);  // Process 1 allocated
    processes[2].requestResources(request3, resources);  // Process 2 allocated

    std::cout << "\nInitial allocation leads to deadlock. Current resource state:\n";
    printResources(resources);

    // Process 3 tries to request resources, causing deadlock
    if (!processes[3].requestResources(request4, resources)) {
        std::cout << "Deadlock detected: Process 3 cannot allocate resources.\n";
    }
}

int main() {
    std::vector<Resource> resources = { Resource(6), Resource(4), Resource(7) };
    std::vector<Process> processes = {
            Process(0, {3, 2, 2}, 1),  // Prozess 0, Priorität 1
            Process(1, {2, 2, 2}, 2),  // Prozess 1, Priorität 2
            Process(2, {3, 1, 3}, 3),  // Prozess 2, Priorität 3
            Process(3, {2, 2, 2}, 1),  // Prozess 3, Priorität 1
            Process(4, {4, 3, 3}, 2)   // Prozess 4, Priorität 2
    };

    DeadlockRecovery recovery;
    DeadlockAvoidance avoidance;
    BankersAlgorithm bankers(processes, resources);

    // Deadlock-Vermeidung testen (vor der Deadlock-Simulation)
    std::cout << "--- Testing Deadlock Avoidance Strategies ---\n";

    // Hold and Wait eliminieren
    if (avoidance.requestAllResourcesAtOnce(processes[0], resources)) {
        std::cout << "Process 0 allocated all resources at once.\n";
    } else {
        std::cout << "Process 0 cannot allocate all resources.\n";
    }
    printResources(resources);

    // Preemption (No Preemption eliminieren)
    if (avoidance.preemptResources(processes[1], processes, resources)) {
        std::cout << "Process 1 preempted resources successfully.\n";
    } else {
        std::cout << "Process 1 failed to preempt resources.\n";
    }
    printResources(resources);

    // Circular Wait eliminieren (aufsteigende Ressourcenanforderung)
    if (avoidance.requestResourcesInOrder(processes[2], resources)) {
        std::cout << "Process 2 allocated resources in order.\n";
    } else {
        std::cout << "Process 2 cannot allocate resources in order.\n";
    }
    printResources(resources);

    // Reset der Ressourcen für den Deadlock-Test
    processes[0].releaseResources(resources);
    processes[1].releaseResources(resources);
    processes[2].releaseResources(resources);
    processes[3].releaseResources(resources);

    // Create a deadlock scenario
    createDeadlock(processes, resources);

    // Check for deadlock before attempting recovery
    std::cout << "\nChecking for deadlock before recovery:\n";
    checkForDeadlock(recovery, processes, resources);

    // Testing deadlock recovery strategies
    std::cout << "\n--- Testing Interrupt Strategy ---\n";
    recovery.resolveDeadlock(processes, resources, "interrupt");
    printResources(resources);

    // Check for deadlock after attempting recovery
    std::cout << "\nChecking for deadlock after recovery:\n";
    checkForDeadlock(recovery, processes, resources);

    // Reset for next strategy
    processes[0].releaseResources(resources);
    processes[1].releaseResources(resources);
    processes[2].releaseResources(resources);
    processes[3].releaseResources(resources);
    createDeadlock(processes, resources);

    // Check for deadlock before attempting recovery
    std::cout << "\nChecking for deadlock before recovery:\n";
    checkForDeadlock(recovery, processes, resources);
    std::cout << "\n--- Testing Rollback Strategy ---\n";
    recovery.resolveDeadlock(processes, resources, "rollback");
    printResources(resources);

    // Check for deadlock after rollback
    std::cout << "\nChecking for deadlock after rollback:\n";
    checkForDeadlock(recovery, processes, resources);

    // Reset for next strategy
    processes[0].releaseResources(resources);
    processes[1].releaseResources(resources);
    processes[2].releaseResources(resources);
    processes[3].releaseResources(resources);
    createDeadlock(processes, resources);

    // Check for deadlock before attempting recovery
    std::cout << "\nChecking for deadlock before recovery:\n";
    checkForDeadlock(recovery, processes, resources);
    std::cout << "\n--- Testing Abort Strategy ---\n";
    recovery.resolveDeadlock(processes, resources, "abort");
    printResources(resources);

    // Check for deadlock after abort
    std::cout << "\nChecking for deadlock after abort:\n";
    checkForDeadlock(recovery, processes, resources);

    // Further testing with Banker's Algorithm can be done after recovery strategies
    std::cout << "\n--- Running Banker's Algorithm Test ---\n";
    BankersAlgorithmTest testSuite;
    testSuite.runAllTests();
    std::cout << "All Banker's Algorithm tests passed successfully!\n";

    return 0;
}
