#pragma once

#include <vector>
#include "Process.h"
#include "Resource.h"
#include "DeadlockRecovery.h"

class DeadlockRecovery;

class Process;

class Resource;

/**
 * @class DeadlockDetector
 * @brief Diese Klasse bietet Mechanismen zur Erkennung von Deadlocks und zur Bestimmung, ob das System sich in einem sicheren Zustand befindet.
 */
class DeadlockDetector {

public:
    /**
     * @brief Überprüft, ob das System in einem sicheren Zustand ist, indem die Verfügbarkeit von Ressourcen und der Status der Prozesse bewertet wird.
     * @param processes Die Liste der Prozesse im System.
     * @param resources Die Liste der Ressourcen im System.
     * @return 1, wenn das System in einem sicheren Zustand ist, 0, wenn das System unsicher ist (möglicher Deadlock).
     */
    int isSystemInSafeState(const std::vector<Process> &processes, const std::vector<Resource> &resources);

    /**
     * @brief Überprüft, ob ein Deadlock im System vorliegt, und löst ihn, falls nötig, mit einer angegebenen Wiederherstellungsstrategie.
     * @param recovery Ein Referenzobjekt zur Deadlock-Behebung.
     * @param processes Die Liste der Prozesse im System.
     * @param resources Die Liste der Ressourcen im System.
     */
    void
    checkForDeadlock(DeadlockRecovery &recovery, std::vector<Process> &processes, std::vector<Resource> &resources);

private:
    /**
     * @brief Überprüft, ob ein gegebener Prozess unter den aktuellen Bedingungen abgeschlossen werden kann.
     * @param process Der Prozess, der überprüft werden soll.
     * @param work Die derzeit verfügbaren Ressourcen.
     * @return true, wenn der Prozess abgeschlossen werden kann, false andernfalls.
     */
    bool canProcessComplete(const Process &process, const std::vector<int> &work) const;
};
