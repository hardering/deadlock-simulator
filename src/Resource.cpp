#include <iostream>
#include "Resource.h"
#include "Process.h"

Resource::Resource(int id, int units) : id(id), units(units), owner(nullptr) {}

bool Resource::requestResource(Process *requestor, int requestedUnits) {
    if (units >= requestedUnits) {
        units -= requestedUnits;
        owner = requestor;
        for (int i = 0; i < requestedUnits; i++) {
            requestor->addResource(this);
        }
        return true;
    } else {
        addToWaitingList(requestor, requestedUnits);
        return false;
    }
}

void Resource::addToWaitingList(Process *process, int neededUnits) {
    waitingList.emplace_back(process, neededUnits);
}

void Resource::releaseResources(int releasedUnits) {
    units += releasedUnits;

    auto it = waitingList.begin();
    while (it != waitingList.end() && units >= it->second) {
        Process *proc = it->first;
        int need = it->second;
        if (requestResource(proc, need)) {
            it = waitingList.erase(it);
        } else {
            ++it;
        }
    }
}

void Resource::printStatus() const {
    std::cout << "Resource ID: " << id << ", Units: " << units << ", Owner: ";
    if (owner) {
        std::cout << owner->getId();
    } else {
        std::cout << "None";
    }
    std::cout << ", Waiting Queue: ";
    for (const auto &pair: waitingList) {
        std::cout << pair.first->getId() << " ";
    }
    std::cout << std::endl;
}


Process *Resource::getOwner() const {
    return owner;
}

int Resource::getUnits() const {
    return units;
}
