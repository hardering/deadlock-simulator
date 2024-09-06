#pragma once

#include <vector>
#include "Process.h"
#include "Resource.h"

class DeadlockDetector {
public:
    bool isSystemInSafeState(std::vector<Process> &processes, std::vector<Resource> &resources);

private:
    bool canProcessComplete(const Process &process, const std::vector<int> &work) const;
};