#include <iostream>
#include <utility>
#include "Process.h"
#include "Simulation.h"

Process::Process(int processId, Simulation *sim, std::vector<std::tuple<Resource *, int, int>> resRequirements)
        : id(processId), simulation(sim), resources(std::move(resRequirements)) {}

void Process::requestResources() {
    for (auto &resTuple: resources) {
        Resource *resource = std::get<0>(resTuple);
        int need = std::get<1>(resTuple) - std::get<2>(resTuple); // maxDemand minus alreadyHeld

        if (need > 0) {
            if (!resource->requestResource(this, need)) {
                if (std::find(waitingResourceIds.begin(), waitingResourceIds.end(), resource->getId()) ==
                    waitingResourceIds.end()) {
                    waitingResourceIds.push_back(resource->getId());
                }
            } else {
                auto it = std::find(waitingResourceIds.begin(), waitingResourceIds.end(), resource->getId());
                if (it != waitingResourceIds.end()) {
                    waitingResourceIds.erase(it);
                }
            }
        }
    }
}


void Process::releaseResources() {
    for (auto &res: allocatedResources) {
        res->releaseResources(id);
    }
    allocatedResources.clear();
    for (auto &resTuple: resources) {
        std::get<2>(resTuple) = 0;
    }
}


void Process::performRollback() {
    if (!allocatedResources.empty()) {
        allocatedResources.back()->releaseResources(id);
        allocatedResources.pop_back();
    }
}

void Process::terminate() {
    releaseResources();
    simulation->removeProcess(this);
}

bool Process::holdsResource(Resource *res) {
    return std::find(allocatedResources.begin(), allocatedResources.end(), res) != allocatedResources.end();
}

void Process::addResource(Resource *res) {
    if (std::find(allocatedResources.begin(), allocatedResources.end(), res) == allocatedResources.end()) {
        allocatedResources.push_back(res);
    }
}

void Process::printStatus() const {
    std::cout << "Process ID: " << id << " holds: ";
    for (const auto &res: allocatedResources) {
        std::cout << res->getId() << " ";
    }
    std::cout << std::endl;
}

const std::vector<std::tuple<Resource*, int, int>>& Process::getResourceRequirements() const {
    return resources;
}
QString Process::getAllHeldResourceIds() const {
    QString heldResourceIds;
    for (auto &res: allocatedResources) {
        if (!heldResourceIds.isEmpty()) {
            heldResourceIds += ", ";
        }
        heldResourceIds += QString::number(res->getId());
    }
    return heldResourceIds;
}

QString Process::getWaitingResourceIdsAsString() const {
    QString ids;
    for (int i: waitingResourceIds) {
        if (!ids.isEmpty()) {
            ids += ", ";
        }
        ids += QString::number(i);
    }
    return ids;
}




