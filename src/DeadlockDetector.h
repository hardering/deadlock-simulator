#pragma once

#include <vector>
#include "Process.h"
#include "Resource.h"
#include "DeadlockRecovery.h"

class DeadlockRecovery;

class Process;

class Resource;

class DeadlockDetector {

public:
    int isSystemInSafeState(const std::vector<Process> &processes, const std::vector<Resource> &resources);

    void checkForDeadlock(DeadlockRecovery &recovery, std::vector<Process> &processes,
                          std::vector<Resource> &resources);

private:
    bool canProcessComplete(const Process &process, const std::vector<int> &work) const;
};