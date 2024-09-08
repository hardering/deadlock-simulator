#include "BankersAlgorithm.h"
#include <iostream>
#include <vector>

BankersAlgorithm::BankersAlgorithm(const std::vector<Process> &p, const std::vector<Resource> &r)
        : processes(p), resources(r) {}

bool BankersAlgorithm::requestResources(int pid, const std::vector<int> &request) {
    Process &proc = processes.at(pid);

    std::cout << "Available Resources before request: ";
    for (auto &res: resources) {
        std::cout << res.getAvailableInstances() << " ";
    }
    std::cout << std::endl;

    if (!canAllocateResources(proc, request)) {
        std::cout << "Request exceeds currently available resources or initial claim." << std::endl;
        return false;
    }

    proc.allocateResources(request);

    if (isSystemInSafeState()) {
        std::cout << "System remains in a safe state after request." << std::endl;
        return true;
    } else {
        std::cout << "System would enter an unsafe state, rolling back." << std::endl;
        proc.releaseResources(request);
        return false;
    }
}

bool BankersAlgorithm::canAllocateResources(const Process &proc, const std::vector<int> &request) {
    for (size_t i = 0; i < request.size(); ++i) {
        if (request[i] > resources[i].getAvailableInstances()) {
            return false;
        }
    }
    return true;
}

bool BankersAlgorithm::isSystemInSafeState() {
    std::vector<int> work(resources.size());
    std::vector<bool> finish(processes.size(), false);

    for (size_t i = 0; i < resources.size(); ++i) {
        work[i] = resources[i].getAvailableInstances();
    }

    bool progress;
    do {
        progress = false;
        for (size_t i = 0; i < processes.size(); ++i) {
            if (!finish[i] && canProcessComplete(processes[i], work)) {
                for (size_t j = 0; j < resources.size(); ++j) {
                    work[j] += processes[i].getAllocatedResources()[j];
                }
                finish[i] = true;
                progress = true;
            }
        }
    } while (progress);

    return std::all_of(finish.begin(), finish.end(), [](bool f) { return f; });
}

bool BankersAlgorithm::canProcessComplete(const Process &proc, const std::vector<int> &work) {
    for (size_t i = 0; i < proc.getNeededResources().size(); ++i) {
        if (proc.getNeededResources()[i] > work[i]) {
            return false;
        }
    }
    return true;
}

void BankersAlgorithm::releaseResources(int pid) {
    Process &proc = processes.at(pid);
    std::vector<int> toRelease(proc.getAllocatedResources());
    proc.releaseResources(toRelease);

    std::cout << "Resources released for process " << pid << std::endl;
}