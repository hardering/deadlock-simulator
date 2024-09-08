#pragma once

#include "Process.h"
#include "Resource.h"
#include "DeadlockDetector.h"

/**
 * @class BankersAlgorithm
 * @brief Implementiert den Banker's Algorithmus zur Vermeidung von Deadlocks durch Prüfung der Ressourcenzuweisung und des Systemzustands.
 */
class BankersAlgorithm {
private:
    std::vector<Process> processes;   /**< Liste der Prozesse im System. */
    std::vector<Resource> resources;  /**< Liste der Ressourcen im System. */
    DeadlockDetector detector;        /**< Instanz des Deadlock-Detektors zur Prüfung auf Deadlocks. */

public:
    /**
     * @brief Konstruktor, der den Banker's Algorithmus mit einer Liste von Prozessen und Ressourcen initialisiert.
     * @param process Die Liste der Prozesse.
     * @param resource Die Liste der Ressourcen.
     */
    BankersAlgorithm(const std::vector<Process> &process, const std::vector<Resource> &resource);

    /**
     * @brief Verarbeitet eine Ressourcenanforderung für einen bestimmten Prozess.
     * @param pid Die Prozess-ID des anfordernden Prozesses.
     * @param request Die Liste der angeforderten Ressourcenmengen.
     * @return true, wenn die Anforderung erfüllt werden kann und das System sicher bleibt, false andernfalls.
     */
    bool requestResources(int pid, const std::vector<int> &request);

    /**
     * @brief Gibt die Ressourcen eines bestimmten Prozesses frei.
     * @param pid Die Prozess-ID des Prozesses, der Ressourcen freigibt.
     */
    void releaseResources(int pid);

    /**
     * @brief Überprüft, ob die angeforderten Ressourcen für einen Prozess zugewiesen werden können, ohne das System in einen unsicheren Zustand zu versetzen.
     * @param proc Der Prozess, der die Ressourcen anfordert.
     * @param request Die Liste der angeforderten Ressourcenmengen.
     * @return true, wenn die Ressourcen zugewiesen werden können, false andernfalls.
     */
    bool canAllocateResources(const Process &proc, const std::vector<int> &request);

    /**
     * @brief Prüft, ob das System in einem sicheren Zustand ist.
     * @return true, wenn das System in einem sicheren Zustand ist, false andernfalls.
     */
    bool isSystemInSafeState();

    /**
     * @brief Überprüft, ob ein gegebener Prozess abgeschlossen werden kann, basierend auf den verfügbaren Ressourcen.
     * @param proc Der Prozess, der überprüft wird.
     * @param work Die Liste der verfügbaren Ressourcen.
     * @return true, wenn der Prozess abgeschlossen werden kann, false andernfalls.
     */
    bool canProcessComplete(const Process &proc, const std::vector<int> &work);
};
