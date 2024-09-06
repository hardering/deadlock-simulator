// DeadlockAvoidance.h

#pragma once
#include <vector>
#include "Process.h"
#include "Resource.h"

class DeadlockAvoidance {
public:
    // Strategie 1: Alle Ressourcen zu Beginn eines Prozesses anfordern (Eliminierung von Hold and Wait)
    bool requestAllResourcesAtOnce(Process& process, std::vector<Resource>& resources) {
        const std::vector<int>& neededResources = process.getNeededResources();

        // Prüfen, ob alle benötigten Ressourcen verfügbar sind
        for (size_t i = 0; i < neededResources.size(); ++i) {
            if (resources[i].getAvailableInstances() < neededResources[i]) {
                return false; // Nicht genug Ressourcen verfügbar
            }
        }

        // Wenn alle Ressourcen verfügbar sind, wird der Prozess gestartet
        process.requestResources(neededResources, resources);
        return true;
    }

    // Strategie 2: Ressourcen von Prozessen mit niedriger Priorität entziehen (Eliminierung von No Preemption)
    bool preemptResources(Process& requestingProcess, std::vector<Process>& processes, std::vector<Resource>& resources) {
        for (auto& process : processes) {
            if (process.getPriority() < requestingProcess.getPriority()) {
                std::cout << "Preempting resources from process " << process.getPID() << " for process " << requestingProcess.getPID() << "\n";
                process.releaseResources(resources);  // Ressourcen freigeben
            }
        }

        // Nach Preemption versuchen, die Ressourcen für den anfragenden Prozess anzufordern
        return requestingProcess.requestResources(requestingProcess.getNeededResources(), resources);
    }

    // Strategie 3: Ressourcen in einer festgelegten Reihenfolge anfordern (Eliminierung von Circular Wait)
    bool requestResourcesInOrder(Process& process, std::vector<Resource>& resources) {
        const std::vector<int>& neededResources = process.getNeededResources();

        // Ressourcen in aufsteigender Reihenfolge anfordern
        for (size_t i = 0; i < neededResources.size(); ++i) {
            if (resources[i].getAvailableInstances() < neededResources[i]) {
                return false; // Nicht genug Ressourcen verfügbar
            }
        }

        // Wenn die Ressourcen in der richtigen Reihenfolge verfügbar sind, den Prozess ausführen
        process.requestResources(neededResources, resources);
        return true;
    }
};
