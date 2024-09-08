#pragma once

#include <vector>
#include "Process.h"
#include "Resource.h"

/**
 * @class DeadlockAvoidance
 * @brief Diese Klasse implementiert Strategien zur Vermeidung von Deadlocks, indem sie Ressourcenanforderungen kontrolliert.
 */
class DeadlockAvoidance {
public:
    /**
     * @brief Versucht einen Prozess alle benötigten Ressourcen auf einmal zuzuweisen.
     * @param process Der Prozess, der die Ressourcen anfordert.
     * @param resources Die Liste der im System verfügbaren Ressourcen.
     * @return true, wenn alle Ressourcen erfolgreich zugewiesen wurden, false, wenn nicht genügend Ressourcen vorhanden sind.
     */
    bool requestAllResourcesAtOnce(Process &process, std::vector<Resource> &resources);

    /**
     * @brief Präemptiert Ressourcen von anderen Prozessen, um dem anfordernden Prozess die benötigten Ressourcen zuzuweisen.
     * @param requestingProcess Der Prozess, der die Ressourcen anfordert.
     * @param processes Die Liste der Prozesse im System.
     * @param resources Die Liste der im System verfügbaren Ressourcen.
     * @return true, wenn Ressourcen erfolgreich präemptiert wurden, false, wenn Präemption nicht möglich ist.
     */
    bool
    preemptResources(Process &requestingProcess, std::vector<Process> &processes, std::vector<Resource> &resources);

    /**
     * @brief Versucht einen Prozess Ressourcen in einer bestimmten Reihenfolge anzufordern.
     * @param process Der Prozess, der die Ressourcen anfordert.
     * @param resources Die Liste der im System verfügbaren Ressourcen.
     * @return true, wenn die Ressourcen erfolgreich zugewiesen wurden, false, wenn nicht genügend Ressourcen vorhanden sind.
     */
    bool requestResourcesInOrder(Process &process, std::vector<Resource> &resources);
};
