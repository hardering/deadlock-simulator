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

const std::vector<int> &Process::getNeededResources() const {
    return neededResources;
}