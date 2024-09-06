#pragma once

#include <vector>
#include "Process.h"
#include "Resource.h"
#include "DeadlockRecovery.h"

class DeadlockRecovery;

class DeadlockDetector {
public:
    bool isSystemInSafeState(std::vector<Process> &processes, std::vector<Resource> &resources);

    void checkForDeadlock(DeadlockRecovery &recovery, const std::vector<Process> &processes,
                          const std::vector<Resource> &resources);

private:
    bool canProcessComplete(const Process &process, const std::vector<int> &work) const;
};