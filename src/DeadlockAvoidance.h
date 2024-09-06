#pragma once

#include <vector>
#include "Process.h"
#include "Resource.h"

class DeadlockAvoidance {
public:
    bool requestAllResourcesAtOnce(Process &process, std::vector<Resource> &resources);

    bool
    preemptResources(Process &requestingProcess, std::vector<Process> &processes, std::vector<Resource> &resources);

    bool requestResourcesInOrder(Process &process, std::vector<Resource> &resources);
};
