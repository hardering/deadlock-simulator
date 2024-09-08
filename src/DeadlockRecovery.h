#pragma once

#include <iostream>
#include <vector>
#include "Process.h"
#include "Resource.h"
#include "DeadlockDetector.h"

class DeadlockDetector;

class Process;

class Resource;

/**
 * @class DeadlockRecovery
 * @brief Diese Klasse bietet Mechanismen zur Behebung von Deadlock-Situationen in einem System, wie das Unterbrechen, Zurücksetzen und Abbrechen von Prozessen.
 */
class DeadlockRecovery {

public:
    DeadlockDetector *detector; /**< Zeiger auf den Deadlock-Detektor, der zur Deadlockerkennung verwendet wird */

    /**
     * @brief Unterbricht den angegebenen Prozess, um Ressourcen freizugeben.
     * @param pid Die Prozess-ID des zu unterbrechenden Prozesses.
     * @param processes Referenz auf die Liste der Prozesse im System.
     * @param resources Referenz auf die Liste der Ressourcen im System.
     */
    void interruptProcess(int pid, std::vector<Process> &processes, std::vector<Resource> &resources);

    /**
     * @brief Setzt den angegebenen Prozess zurück, um eine frühere sichere Ressourcenzuweisung wiederherzustellen.
     * @param pid Die Prozess-ID des zurückzunehmenden Prozesses.
     * @param processes Referenz auf die Liste der Prozesse im System.
     * @param resources Referenz auf die Liste der Ressourcen im System.
     */
    void rollbackProcess(int pid, std::vector<Process> &processes, std::vector<Resource> &resources);

    /**
     * @brief Bricht den angegebenen Prozess ab, um Ressourcen freizugeben und den Deadlock zu lösen.
     * @param pid Die Prozess-ID des abzubrechenden Prozesses.
     * @param processes Referenz auf die Liste der Prozesse im System.
     * @param resources Referenz auf die Liste der Ressourcen im System.
     */
    void abortProcess(int pid, std::vector<Process> &processes, std::vector<Resource> &resources);

    /**
     * @brief Löst den Deadlock durch die angegebene Strategie (z.B. Unterbrechen, Zurücksetzen oder Abbrechen von Prozessen).
     * @param processes Referenz auf die Liste der Prozesse im System.
     * @param resources Referenz auf die Liste der Ressourcen im System.
     * @param strategy Die Strategie zur Deadlock-Behebung (z.B. "interrupt", "rollback", "abort").
     */
    void
    resolveDeadlock(std::vector<Process> &processes, std::vector<Resource> &resources, const std::string &strategy);

    /**
     * @brief Erkennt, ob ein Deadlock vorliegt, basierend auf den aktuellen Zuständen von Prozessen und Ressourcen.
     * @param processes Die Liste der Prozesse im System.
     * @param resources Die Liste der Ressourcen im System.
     * @return true, wenn ein Deadlock erkannt wird, false ansonsten.
     */
    bool detectDeadlock(const std::vector<Process> &processes, const std::vector<Resource> &resources);
};
