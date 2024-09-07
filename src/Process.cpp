#include <QString>
#include "Process.h"

Process::Process(int pid, const std::vector<int> &maxResources, int priority) : pid(pid), priority(priority),
                                                                                maxResources(maxResources),
                                                                                allocatedResources(maxResources.size(),
                                                                                                   0),
                                                                                neededResources(maxResources) {}

bool Process::requestResources(const std::vector<int> &request, std::vector<Resource> &resources) {
    for (size_t i = 0; i < request.size(); ++i) {
        if (request[i] > neededResources[i] || !resources[i].allocate(request[i])) {
            return false;
        }
    }
    for (size_t i = 0; i < request.size(); ++i) {
        allocatedResources[i] += request[i];
        neededResources[i] -= request[i];
    }
    return true;
}

void Process::releaseResources(std::vector<Resource> &resources) {
    for (size_t i = 0; i < allocatedResources.size(); ++i) {
        resources[i].release(allocatedResources[i]);
        neededResources[i] += allocatedResources[i];
        allocatedResources[i] = 0;
    }
}

bool Process::isFinished() const {
    return std::all_of(neededResources.begin(), neededResources.end(), [](int needed) { return needed == 0; });
}

int Process::getPID() const {
    return pid;
}

int Process::getPriority() const {
    return priority;
}

const std::vector<int> &Process::getMaxResources() const {
    return maxResources;
}

const std::vector<int> &Process::getAllocatedResources() const {
    return allocatedResources;
}

QString Process::getAllocatedResourcesAsString() const {
    for (int resource: allocatedResources) {
        if (resource > 0) {
            return "yes";
        }
    }
    return "no";
}

QString Process::getState(std::vector<Process> &processes, std::vector<Resource> &resources) {
    if (isFinished()) {
        status = "Completed";
    } else if (getPID() == deadlock->isSystemInSafeState(processes, resources)) {
        status = "Deadlock";
    } else if (std::any_of(neededResources.begin(), neededResources.end(), [](int needed) { return needed > 0; })) {
        status = "Waiting";
    }
    return status;
}

const std::vector<int> &Process::getNeededResources() const {
    return neededResources;
}