#include "Simulation.h"
#include "Graph.h"
#include <iostream>

Simulation::Simulation(QObject *parent) : QObject(parent) {
}

void Simulation::addProcess(Process *process) {
    processes.push_back(process);
    emit processAdded(process->getId());
}

void Simulation::addResource(Resource *resource) {
    resources.push_back(resource);
    emit resourceAdded(resource->getId());
}

void Simulation::removeProcess(Process *process) {
    processes.erase(std::remove(processes.begin(), processes.end(), process), processes.end());
}

void Simulation::initializeProcessWithResources() {
    auto *resA = new Resource(1, 3);
    auto *resB = new Resource(2, 2);
    auto *resC = new Resource(3, 2);

    auto *proc1 = new Process(1, this, {{resA, 0, 2},
                                        {resB, 1, 0},
                                        {resC, 2, 0}});
    auto *proc2 = new Process(2, this, {{resA, 2, 0},
                                        {resB, 0, 1},
                                        {resC, 1, 1}});
    auto *proc3 = new Process(3, this, {{resA, 2, 0},
                                        {resB, 1, 1},
                                        {resC, 0, 0}});

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

bool Simulation::detectDeadlock() {
    // Clear the graph
    waitForGraph = WaitForGraph();

    // Add edges for waiting processes
    for (auto *process : processes) {
        for (auto &resTuple : process->getResourceRequirements()) {
            Resource *resource = std::get<0>(resTuple);
            int need = std::get<1>(resTuple) - std::get<2>(resTuple); // maxDemand minus alreadyHeld
            if (need > 0 && resource->getOwner() != nullptr) {
                waitForGraph.addEdge(process->getId(), resource->getOwner()->getId());
            }
        }
    }

    // Check for cycles
    return waitForGraph.hasCycle();
}