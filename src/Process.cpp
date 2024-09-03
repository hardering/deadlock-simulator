#include <iostream>
#include <utility>
#include "Process.h"
#include "Simulation.h"

Process::Process(int processId, Simulation* sim, std::vector<std::tuple<Resource*, int, int>> resRequirements)
        : id(processId), simulation(sim), resources(std::move(resRequirements)) {}

/*void Process::requestResources() {
    for (auto& resTuple : resources) {
        Resource* resource = std::get<0>(resTuple);
        int maxDemand = std::get<1>(resTuple);
        int alreadyHeld = std::get<2>(resTuple);
        int need = maxDemand - alreadyHeld;

        while (need > 0) {
            if (resource->requestResource(this)) {
                alreadyHeld++;
                need--;
            } else {
                break;
            }
        }
    }
}*/

void Process::requestResources() {
    for (auto& resTuple : resources) {
        Resource* resource = std::get<0>(resTuple);
        int need = std::get<1>(resTuple) - std::get<2>(resTuple); // maxDemand minus alreadyHeld

        if (need > 0) {
            if (!resource->requestResource(this, need)) {
                std::cout << "Process " << id << " added to waiting list for resource " << resource->getId() << std::endl;
            }
        }
    }
}

void Process::releaseResources() {
    for (auto& res : allocatedResources) {
        res->releaseResources(id);
    }
    allocatedResources.clear();
    for (auto& resTuple : resources) {
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

void Process::addResource(Resource* res) {
    if (std::find(allocatedResources.begin(), allocatedResources.end(), res) == allocatedResources.end()) {
        allocatedResources.push_back(res);
    }
}

void Process::printStatus() const {
    std::cout << "Process ID: " << id << " holds: ";
    for (const auto& res : allocatedResources) {
        std::cout << res->getId() << " ";
    }
    std::cout << std::endl;
}
