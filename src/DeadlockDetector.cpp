#include "DeadlockDetector.h"
#include "DeadlockRecovery.h"

int
DeadlockDetector::isSystemInSafeState(const std::vector<Process> &processes, const std::vector<Resource> &resources) {
    std::vector<int> work(resources.size());
    std::vector<bool> finish(processes.size(), false);

    for (size_t i = 0; i < resources.size(); ++i) {
        work[i] = resources[i].getAvailableInstances();
    }

    bool progressMade;
    do {
        progressMade = false;
        for (size_t i = 0; i < processes.size(); ++i) {
            if (!finish[i] && canProcessComplete(processes[i], work)) {
                finish[i] = true;
                progressMade = true;

                for (size_t j = 0; j < work.size(); ++j) {
                    work[j] += processes[i].getAllocatedResources()[j];
                }
            }
        }
    } while (progressMade);

    for (size_t i = 0; i < finish.size(); ++i) {
        if (!finish[i]) {
            return processes[i].getPID();
        }
    }
    return -1;
}

bool DeadlockDetector::canProcessComplete(const Process &process, const std::vector<int> &work) const {
    const std::vector<int> &neededResources = process.getNeededResources();
    for (size_t i = 0; i < neededResources.size(); ++i) {
        if (neededResources[i] > work[i]) {
            return false;
        }
    }
    return true;
}

void DeadlockDetector::checkForDeadlock(DeadlockRecovery &recovery, std::vector<Process> &processes,
                                        std::vector<Resource> &resources) {
    int deadlockProcess = isSystemInSafeState(processes, resources);
    if (deadlockProcess != -1) {
        std::cout << "Deadlock detected. Deadlocked process ID: " << deadlockProcess << std::endl;
    } else {
        std::cout << "No deadlock detected." << std::endl;
    }
}