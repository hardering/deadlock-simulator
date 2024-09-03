#include "Simulation.h"
#include <iostream>

void Simulation::detectDeadlocks() {
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

/*void Simulation::initializeSimpleDeadlock() {
    Resource *resource01 = new Resource(1);
    Resource *resource02 = new Resource(2);
    Process *process01 = new Process(1, this);
    Process *process02 = new Process(2, this);

    addResource(resource01);
    addResource(resource02);
    addProcess(process01);
    addProcess(process02);

    process01->requestResource(resource01);
    process02->requestResource(resource02);

    process01->requestResource(resource02);
    process02->requestResource(resource01);
}*/

void Simulation::initializeComplexDeadlock() {
    auto* resA = new Resource(1, 3);
    auto* resB = new Resource(2, 2);
    auto* resC = new Resource(3, 2);

    auto* proc1 = new Process(1, this, {{resA, 0, 2}, {resB, 1, 0}, {resC, 2, 0}});
    auto* proc2 = new Process(2, this, {{resA, 2, 0}, {resB, 0, 1}, {resC, 1, 1}});
    auto* proc3 = new Process(3, this, {{resA, 2, 0}, {resB, 1, 1}, {resC, 0, 0}});

    addResource(resA);
    addResource(resB);
    addResource(resC);
    resA->printStatus();
    resB->printStatus();
    resC->printStatus();

    addProcess(proc1);
    addProcess(proc2);
    addProcess(proc3);
    proc1->printStatus();
    proc2->printStatus();
    proc3->printStatus();

    proc1->requestResources();
    proc2->requestResources();
    proc3->requestResources();

    proc1->printStatus();
    proc2->printStatus();
    proc3->printStatus();
    resA->printStatus();
    resB->printStatus();
    resC->printStatus();
}

int main() {
    auto *simulation = new Simulation();
    simulation->initializeComplexDeadlock();
}
