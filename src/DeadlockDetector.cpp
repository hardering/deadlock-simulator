#include "DeadlockDetector.h"

bool DeadlockDetector::isSystemInSafeState(std::vector<Process> &processes, std::vector<Resource> &resources) {
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
                    work[j] += processes[i].getNeededResources()[j];
                }
            }
        }
    } while (progressMade);

    return std::all_of(finish.begin(), finish.end(), [](bool f) { return f; });
}

bool DeadlockDetector::canProcessComplete(const Process &process, const std::vector<int> &work) const {
    const std::vector<int> &neededResources = process.getNeededResources();
    return std::all_of(neededResources.begin(), neededResources.end(),
                       [&work, &neededResources, idx = 0](int need) mutable {
                           return need <= work[idx++];
                       });
}