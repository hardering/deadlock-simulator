#ifndef DEADLOCK_RECOVERY_TEST_H
#define DEADLOCK_RECOVERY_TEST_H

#include <iostream>
#include "DeadlockRecovery.h"

/**
 * @class DeadlockRecoveryTest
 * @brief Diese Klasse enthält Unit-Tests für die Deadlock-Wiederherstellungsstrategien, um die verschiedenen Methoden zur Behebung von Deadlocks zu testen.
 */
class DeadlockRecoveryTest {
public:
    /**
     * @brief Führt alle Tests für die Deadlock-Wiederherstellungsstrategien aus, einschließlich der Unterbrechungs-, Rücksetz- und Abbruchstrategien.
     */
    void runAllTests() {
        testInterruptStrategy();
        testRollbackStrategy();
        testAbortStrategy();
    }

private:
    /**
     * @brief Testet die Strategie zur Unterbrechung eines Prozesses, um Ressourcen freizugeben.
     */
    void testInterruptStrategy();

    /**
     * @brief Testet die Strategie, einen Prozess zurückzusetzen, um eine frühere sichere Ressourcenzuweisung wiederherzustellen.
     */
    void testRollbackStrategy();

    /**
     * @brief Testet die Strategie zum Abbrechen eines Prozesses, um einen Deadlock zu beheben.
     */
    void testAbortStrategy();
};

#endif
