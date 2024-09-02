#include "Simulation.h"
#include <iostream>

void Simulation::detectDeadlocks() {
    // Implement deadlock detection logic here
}

void Simulation::resolveDeadlockByTermination() {
    if (!processes.empty()) {
        processes.back()->terminate();
    }
}

void Simulation::resolveDeadlockByRollback() {
    if (!processes.empty()) {
        processes.back()->performRollback();
    }
}

void Simulation::addProcess(Process* proc) {
    processes.push_back(proc);
}

void Simulation::addResource(Resource* res) {
    resources.push_back(res);
}

void Simulation::removeProcess(Process* proc) {
    processes.erase(std::remove(processes.begin(), processes.end(), proc), processes.end());
}
