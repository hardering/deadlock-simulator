#pragma once

#include <iostream>
#include <vector>
#include <QString>
#include "Resource.h"
#include "DeadlockDetector.h"
#include "DeadlockRecovery.h"

class Process {
private:
    int pid;
    int priority;
    std::vector<int> maxResources;
    std::vector<int> allocatedResources;
    std::vector<int> neededResources;
    std::vector<int> currentRequest;
    std::vector<int> initialNeededResources;
    std::vector<int> initialAllocatedResources;
    std::string status;
    DeadlockDetector *deadlockDetector;
    bool isInterrupted = false;


public:
    Process(int id, const std::vector<int> &maxResources, int priority);

    bool requestResources(const std::vector<int> &request, std::vector<Resource> &resources);

    void releaseResources(std::vector<Resource> &resources);

    bool isFinished() const;

    int getPID() const;

    int getPriority() const;

    const std::vector<int> &getAllocatedResources() const { return allocatedResources; }

    std::vector<int> &getNeededResources() { return neededResources; }

    const std::vector<int> &getNeededResources() const { return neededResources; }

    QString getState(const std::vector<Process> &processes, const std::vector<Resource> &resources);

    void allocateResources(const std::vector<int> &request);

    void releaseResources(const std::vector<int> &request);

    void interrupt();

    void reset();

    void clearInterruption();

    const std::vector<int> &getMaxResources() const;

    const std::vector<int> &getCurrentRequest() const;
};
