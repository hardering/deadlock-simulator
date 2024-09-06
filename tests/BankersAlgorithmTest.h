#include "../src/BankersAlgorithm.h"
#include <cassert>
#include <iostream>

class BankersAlgorithmTest {
public:
    void testSafeResourceAllocation();

    void testUnsafeResourceAllocation();

    void testReleaseResources();

    void runAllTests();
};
