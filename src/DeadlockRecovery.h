#pragma once

#include <iostream>
#include <vector>
#include "Process.h"
#include "Resource.h"
#include "DeadlockDetector.h"

class DeadlockDetector;

class Process;

class Resource;

class DeadlockRecovery {

public:
    DeadlockDetector *detector;

    void interruptProcess(int pid, std::vector<Process> &processes, std::vector<Resource> &resources);

    void rollbackProcess(int pid, std::vector<Process> &processes, std::vector<Resource> &resources);

    void abortProcess(int pid, std::vector<Process> &processes, std::vector<Resource> &resources);

    void
    resolveDeadlock(std::vector<Process> &processes, std::vector<Resource> &resources, const std::string &strategy);

    bool detectDeadlock(const std::vector<Process> &processes, const std::vector<Resource> &resources);
};
