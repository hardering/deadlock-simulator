// Process.h

#pragma once
#include <iostream>
#include <vector>
#include "Resource.h"

class Process {
private:
    int pid;
    int priority;  // Priorität des Prozesses
    std::vector<int> maxResources;
    std::vector<int> allocatedResources;
    std::vector<int> neededResources;

public:
    // Konstruktor für den Prozess mit Priorität
    Process(int id, const std::vector<int>& maxRes, int prio)
    : pid(id), priority(prio), maxResources(maxRes), allocatedResources(maxRes.size(), 0), neededResources(maxRes) {}

    // Ressourcenanforderungen stellen
    bool requestResources(const std::vector<int>& request, std::vector<Resource>& resources) {
        for (size_t i = 0; i < request.size(); ++i) {
            if (request[i] > neededResources[i] || !resources[i].allocate(request[i])) {
                return false;
            }
        }
        for (size_t i = 0; i < request.size(); ++i) {
            allocatedResources[i] += request[i];
            neededResources[i] -= request[i];
        }
        return true;
    }

    // Ressourcen freigeben
    void releaseResources(std::vector<Resource>& resources) {
        for (size_t i = 0; i < allocatedResources.size(); ++i) {
            resources[i].release(allocatedResources[i]);
            neededResources[i] += allocatedResources[i];
            allocatedResources[i] = 0;
        }
    }

    // Überprüfen, ob der Prozess fertig ist
    bool isFinished() const {
        for (int need : neededResources) {
            if (need > 0) return false;
        }
        return true;
    }

    // Zugriff auf die Prozess-ID
    int getPID() const {
        return pid;
    }

    // Zugriff auf die Priorität des Prozesses
    int getPriority() const {
        return priority;
    }

    // Zugriff auf die benötigten Ressourcen
    const std::vector<int>& getNeededResources() const {
        return neededResources;
    }
};
