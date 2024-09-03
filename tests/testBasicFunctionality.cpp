#include "Simulation.h"
#include "Process.h"
#include "Resource.h"
#include <iostream>

/*void testBasicFunctionality() {
    Simulation simulator;
    Resource resource_01(1);
    Resource resource_02(2);
    Process process_01(1, &simulator);
    Process process_02(2, &simulator);

    // ====== Test 1: Resource request ======
    if (process_01.requestResource(&resource_01)) {
        std::cout << "Test 1 Passed: Process 1 successfully acquired Resource 1." << std::endl;
    } else {
        std::cout << "Test 1 Failed: Process 1 could not acquire Resource 1." << std::endl;
    }

    // ====== Test 2: Resource already held by another process ======
    if (!process_02.requestResource(&resource_01)) {
        std::cout << "Test 2 Passed: Process 2 could not acquire Resource 1 because its already held by process 1." << std::endl;
    } else {
        std::cout << "Test 2 Failed: Process 2 acquired Resource 1 (error)." << std::endl;
    }

    // ====== Test 3: Request resource after release ======
    process_01.releaseResources();
    process_02.releaseResources();

    process_01.requestResource(&resource_01);
    process_01.releaseResources();
    process_02.requestResource(&resource_01);

    if (process_02.holdsResource(&resource_01)) {
        std::cout << "Test 3 Passed: Process 2 successfully acquired Resource 1 after release." << std::endl;
    } else {
        std::cout << "Test 3 Failed: Process 2 could not acquire Resource 1 after release." << std::endl;
    }

    // ====== Test 4: Process gets resource from its waiting queue ======
    process_01.releaseResources();
    process_02.releaseResources();

    process_01.requestResource(&resource_01);
    process_02.requestResource(&resource_01);

    process_01.releaseResources();

    if (process_02.holdsResource(&resource_01)) {
        std::cout << "Test 4 Passed: Process 1 from the waiting queue got acquired by Process 2 after its release." << std::endl;
    }

    process_01.releaseResources();
    process_02.releaseResources();
}*/
