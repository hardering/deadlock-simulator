// DeadlockRecovery.h

#pragma once
#include <iostream>
#include <vector>
#include "Process.h"
#include "Resource.h"
#include "DeadlockDetector.h"

class DeadlockRecovery {
public:
    DeadlockDetector detector;

    // Unterbricht den Prozess und gibt dessen Ressourcen frei
    void interruptProcess(int pid, std::vector<Process>& processes, std::vector<Resource>& resources) {
        std::cout << "Interrupting process " << pid << " to resolve deadlock...\n";
        processes[pid].releaseResources(resources);
    }

    // Führt ein Rollback für einen Prozess durch (gibt die Ressourcen zurück)
    void rollbackProcess(int pid, std::vector<Process>& processes, std::vector<Resource>& resources) {
        std::cout << "Rolling back process " << pid << " to its initial state...\n";
        processes[pid].releaseResources(resources);
    }

    // Bricht den Prozess vollständig ab und gibt die Ressourcen frei
    void abortProcess(int pid, std::vector<Process>& processes, std::vector<Resource>& resources) {
        std::cout << "Aborting process " << pid << " to resolve deadlock...\n";
        processes[pid].releaseResources(resources);
        processes.erase(processes.begin() + pid);  // Entfernt den Prozess
    }

    // Deadlock-Auflösung basierend auf einer gewählten Strategie
    void resolveDeadlock(std::vector<Process>& processes, std::vector<Resource>& resources, const std::string& strategy) {
        if (strategy == "interrupt") {
            for (size_t i = 0; i < processes.size(); ++i) {
                if (!processes[i].isFinished()) {
                    interruptProcess(i, processes, resources);
                    break;
                }
            }
        } else if (strategy == "rollback") {
            for (size_t i = 0; i < processes.size(); ++i) {
                if (!processes[i].isFinished()) {
                    rollbackProcess(i, processes, resources);
                    break;
                }
            }
        } else if (strategy == "abort") {
            for (size_t i = 0; i < processes.size(); ++i) {
                if (!processes[i].isFinished()) {
                    abortProcess(i, processes, resources);
                    break;
                }
            }
        }
    }

    // Überprüft, ob das System sich in einem Deadlock befindet
    bool detectDeadlock(const std::vector<Process>& processes, const std::vector<Resource>& resources) {
        return !detector.isSystemInSafeState(const_cast<std::vector<Process>&>(processes), const_cast<std::vector<Resource>&>(resources));
    }
};
