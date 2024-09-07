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
    QString status;
    DeadlockDetector *deadlock;
public:
    Process(int id, const std::vector<int> &maxResources, int priority);

    bool requestResources(const std::vector<int> &request, std::vector<Resource> &resources);

    void releaseResources(std::vector<Resource> &resources);

    bool isFinished() const;

    int getPID() const;

    int getPriority() const;

    const std::vector<int> &getNeededResources() const;

    const std::vector<int> &getMaxResources() const;

    const std::vector<int> &getAllocatedResources() const;

    QString getAllocatedResourcesAsString() const;

    QString getState(std::vector<Process> &processes, std::vector<Resource> &resources);
    

};
