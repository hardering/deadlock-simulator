#include <iostream>
#include "Resource.h"
#include "Process.h"

Resource::Resource(int id) : id(id), owner(nullptr) {}

bool Resource::requestResource(Process* requestor) {
    if (!owner) {
        owner = requestor;
        return true;
    } else {
        addToWaitingList(requestor);
        return false;
    }
}

// Resource.cpp
void Resource::releaseResource() {
    if (!waitingList.empty()) {
        auto it = waitingList.begin();
        Process* nextOwner = *it;
        waitingList.erase(it);

        owner = nextOwner;
        owner->addResource(this);
    } else {
        owner = nullptr;
    }
}

void Resource::addToWaitingList(Process* process) {
    waitingList.insert(process);
}

bool Resource::isAvailable() const {
    return owner == nullptr;
}

Process* Resource::getOwner() const {
    return owner;
}

void Resource::printWaitingQueue() const {
    std::cout << "Waiting Queue for Resource " << id << ": ";
    for (const auto& proc : waitingList) {
        std::cout << proc->getId() << " ";
    }
    std::cout << std::endl;
}
