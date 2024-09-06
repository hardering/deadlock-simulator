#pragma once

#include "Process.h"
#include "Resource.h"
#include "DeadlockDetector.h"

class BankersAlgorithm {
private:
    std::vector<Process> processes;
    std::vector<Resource> resources;
    DeadlockDetector detector;

public:
    BankersAlgorithm(const std::vector<Process> &process, const std::vector<Resource> &resource);

    bool requestResources(int pid, const std::vector<int> &request);

    void releaseResources(int pid);
};
