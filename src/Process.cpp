#include <iostream>
#include "Process.h"
#include "Simulation.h"

Process::Process(int id, Simulation* sim) : id(id), simulation(sim) {}

bool Process::requestResource(Resource *resource) {
    if (resource->requestResource(this)) {
        allocatedResources.push_back(resource);
        return true;
    }
    return false;
}

void Process::releaseResources() {
    for (auto res : allocatedResources) {
        res->releaseResource();
    }
    allocatedResources.clear();
}

void Process::performRollback() {
    if (!allocatedResources.empty()) {
        allocatedResources.back()->releaseResource();
        allocatedResources.pop_back();
    }
}

void Process::terminate() {
    releaseResources();
    // Notify simulation or manage other cleanup tasks
    simulation->removeProcess(this);
}

void Process::printHoldingResources() {
    std::cout << "Process with id -> [" << id << "] holds resources with id -> ";
    for (const auto &res: allocatedResources) {
        std::cout << "[" << res->getId() << "] ";
    }
    std::cout << std::endl;
}

bool Process::holdsResource(Resource *res) {
    return std::find(allocatedResources.begin(), allocatedResources.end(), res) != allocatedResources.end();
}

void Process::addResource(Resource *res) {
    allocatedResources.push_back(res);
}
