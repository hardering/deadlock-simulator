#ifndef DEADLOCK_AVOIDANCE_TEST_H
#define DEADLOCK_AVOIDANCE_TEST_H

#include <iostream>
#include "DeadlockAvoidance.h"

/**
 * @class DeadlockAvoidanceTest
 * @brief Diese Klasse enthält Unit-Tests für die Deadlock-Vermeidungsstrategien, um die Ressourcenanforderung und Präemption zu testen.
 */
class DeadlockAvoidanceTest {
public:
    /**
     * @brief Führt alle Tests für die Deadlock-Vermeidungsstrategien aus, einschließlich der Anforderung aller Ressourcen auf einmal, der Präemption und der geordneten Anforderung von Ressourcen.
     */
    void runAllTests() {
        testRequestAllResourcesAtOnce();
        testPreemptResources();
        testRequestResourcesInOrder();
    }

private:
    /**
     * @brief Testet die Strategie, alle benötigten Ressourcen auf einmal anzufordern.
     */
    void testRequestAllResourcesAtOnce();

    /**
     * @brief Testet die Präemption von Ressourcen von anderen Prozessen.
     */
    void testPreemptResources();

    /**
     * @brief Testet die Strategie, Ressourcen in einer bestimmten Reihenfolge anzufordern.
     */
    void testRequestResourcesInOrder();
};

#endif
