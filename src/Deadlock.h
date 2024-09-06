#pragma once

#include "Process.h"
#include "Resource.h"
#include "DeadlockRecovery.h"

class Deadlock {
public:
    Deadlock();

    void createDeadlock(std::vector<Process> &processes, std::vector<Resource> &resources);
};