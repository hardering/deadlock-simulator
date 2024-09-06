// BankersAlgorithm.h

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
    BankersAlgorithm(const std::vector<Process>& procs, const std::vector<Resource>& res)
            : processes(procs), resources(res) {}

    bool requestResources(int pid, const std::vector<int>& request) {
        Process& process = processes[pid];
        if (!process.requestResources(request, resources)) {
            return false;
        }

        if (detector.isSystemInSafeState(processes, resources)) {
            return true;
        } else {
            process.releaseResources(resources);
            return false;
        }
    }

    void releaseResources(int pid) {
        processes[pid].releaseResources(resources);
    }
};
