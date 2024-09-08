#include "../src/BankersAlgorithm.h"
#include <cassert>
#include <iostream>

/**
 * @class BankersAlgorithmTest
 * @brief Diese Klasse enthält Unit-Tests für den Banker's Algorithmus, um die sichere und unsichere Ressourcenzuweisung sowie das Freigeben von Ressourcen zu testen.
 */
class BankersAlgorithmTest {
public:
    /**
     * @brief Testet die sichere Ressourcenzuweisung durch den Banker's Algorithmus.
     */
    void testSafeResourceAllocation();

    /**
     * @brief Testet die unsichere Ressourcenzuweisung, bei der das System in einen Deadlock geraten könnte.
     */
    void testUnsafeResourceAllocation();

    /**
     * @brief Testet das Freigeben von Ressourcen durch einen Prozess und die Aktualisierung des Systemzustands.
     */
    void testReleaseResources();

    /**
     * @brief Führt alle Tests für den Banker's Algorithmus aus.
     */
    void runAllTests();
};
