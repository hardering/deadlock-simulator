#include "DeadlockAvoidance.h"

bool DeadlockAvoidance::requestAllResourcesAtOnce(Process &process, std::vector<Resource> &resources) {
    const std::vector<int> &neededResources = process.getNeededResources();

    for (size_t i = 0; i < neededResources.size(); ++i) {
        if (resources[i].getAvailableInstances() < neededResources[i]) {
            return false;
        }
    }


    process.requestResources(neededResources, resources);
    return true;
}

bool DeadlockAvoidance::preemptResources(Process &requestingProcess, std::vector<Process> &processes,
                                         std::vector<Resource> &resources) {
    for (auto &process: processes) {
        if (process.getPriority() < requestingProcess.getPriority()) {
            std::cout << "Preempting resources from process " << process.getPID() << " for process "
                      << requestingProcess.getPID() << "\n";
            process.releaseResources(resources);
        }
    }

    return requestingProcess.requestResources(requestingProcess.getNeededResources(), resources);
}

bool DeadlockAvoidance::requestResourcesInOrder(Process &process, std::vector<Resource> &resources) {
    const std::vector<int> &neededResources = process.getNeededResources();

    for (size_t i = 0; i < neededResources.size(); ++i) {
        if (resources[i].getAvailableInstances() < neededResources[i]) {
            return false;
        }
    }

    process.requestResources(neededResources, resources);
    return true;
}