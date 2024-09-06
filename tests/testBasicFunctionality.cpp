#include "Simulation.h"
#include "Process.h"
#include "Resource.h"
#include <iostream>

void testBasicFunctionality() {
    /* Simulation simulator = new Simulation();
     Resource resource_01(1, 1); // Only 1 unit to force contention
     Resource resource_02(2, 1); // Only 1 unit to force contention
     Process process_01(1, &simulator, {{&resource_01, 1, 0}, {&resource_02, 1, 0}});
     Process process_02(2, &simulator, {{&resource_02, 1, 0}, {&resource_01, 1, 0}});

     simulator.addResource(&resource_01);
     simulator.addResource(&resource_02);
     simulator.addProcess(&process_01);
     simulator.addProcess(&process_02);

     // ====== Test 1: Resource request ======
     process_01.requestResources(); // Use requestResources method
     if (process_01.holdsResource(&resource_01)) {
         std::cout << "Test 1 Passed: Process 1 successfully acquired Resource 1." << std::endl;
     } else {
         std::cout << "Test 1 Failed: Process 1 could not acquire Resource 1." << std::endl;
     }

     // Reset state
     process_01.releaseResources();
     process_02.releaseResources();

     // ====== Test 2: Resource already held by another process ======
     process_02.requestResources(); // Use requestResources method
     if (!process_02.holdsResource(&resource_01)) {
         std::cout << "Test 2 Passed: Process 2 could not acquire Resource 1 because it's already held by process 1." << std::endl;
     } else {
         std::cout << "Test 2 Failed: Process 2 acquired Resource 1 (error)." << std::endl;
     }

     // Reset state
     process_01.releaseResources();
     process_02.releaseResources();

     // ====== Test 3: Request resource after release ======
     process_01.requestResources(); // Use requestResources method
     process_01.releaseResources();
     process_02.requestResources(); // Use requestResources method

     if (process_02.holdsResource(&resource_01)) {
         std::cout << "Test 3 Passed: Process 2 successfully acquired Resource 1 after release." << std::endl;
     } else {
         std::cout << "Test 3 Failed: Process 2 could not acquire Resource 1 after release." << std::endl;
     }

     // Reset state
     process_01.releaseResources();
     process_02.releaseResources();

     // ====== Test 4: Process gets resource from its waiting queue ======
     process_01.requestResources(); // Use requestResources method
     process_02.requestResources(); // Use requestResources method

     process_01.releaseResources();

     if (process_02.holdsResource(&resource_01)) {
         std::cout << "Test 4 Passed: Process 1 from the waiting queue got acquired by Process 2 after its release." << std::endl;
     }

     // Reset state
     process_01.releaseResources();
     process_02.releaseResources();

     // ====== Test 5: No Deadlock ======
     std::cout << "Starting Test 5: No Deadlock" << std::endl;
     process_01.requestResources(); // Process 1 requests resources
     process_01.releaseResources(); // Process 1 releases resources
     process_02.requestResources(); // Process 2 requests resources

     if (!simulator.detectDeadlock()) {
         std::cout << "Test 5 Passed: No deadlock detected." << std::endl;
     } else {
         std::cout << "Test 5 Failed: Deadlock incorrectly detected." << std::endl;
     }

     // Reset state
     process_01.releaseResources();
     process_02.releaseResources();

     // ====== Test 6: Deadlock ======
     std::cout << "Starting Test 6: Deadlock" << std::endl;
     process_01.requestResources(); // Process 1 requests Resource 1
     std::cout << "Process 1 requested Resource 1." << std::endl;
     process_02.requestResources(); // Process 2 requests Resource 2
     std::cout << "Process 2 requested Resource 2." << std::endl;

     // Process 1 now requests Resource 2, which is held by Process 2
     process_01.requestResources();
     std::cout << "Process 1 requested Resource 2, which is held by Process 2." << std::endl;

     // Process 2 now requests Resource 1, which is held by Process 1
     process_02.requestResources();
     std::cout << "Process 2 requested Resource 1, which is held by Process 1." << std::endl;

     if (simulator.detectDeadlock()) {
         std::cout << "Test 6 Passed: Deadlock detected." << std::endl;
     } else {
         std::cout << "Test 6 Failed: Deadlock not detected." << std::endl;
     }

     // Reset state
     process_01.releaseResources();
     process_02.releaseResources();*/
}