#include <BankersAlgorithm.h>

BankersAlgorithm::BankersAlgorithm(const std::vector<Process> &process, const std::vector<Resource> &resource)
        : processes(process), resources(resource) {}

bool BankersAlgorithm::requestResources(int pid, const std::vector<int> &request) {
    Process &process = processes[pid];
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

void BankersAlgorithm::releaseResources(int pid) {
    processes[pid].releaseResources(resources);
}