#include "Simulation.h"
#include "Graph.h"
#include "../utils/detectionUtils.h"
#include <iostream>

Simulation::Simulation(Window *windowInstance, QObject *parent) : QObject(parent), window(windowInstance) {
    connect(this, &Simulation::setTableData, window, &Window::setTableData);
    connect(window, &Window::generateDeadlockSituationRequest, this, &Simulation::generateDeadlockSituation);
    connect(window, &Window::resetTableRequest, this, &Simulation::clearAll);

}

void Simulation::addProcess(Process *process) {
    processes.push_back(process);
}

void Simulation::addResource(Resource *resource) {
    resources.push_back(resource);
}

void Simulation::removeProcess(Process *process) {
    processes.erase(std::remove(processes.begin(), processes.end(), process), processes.end());
}

void Simulation::clearAll() {
    for (auto *process: processes) {
        delete process;
    }
    processes.clear();

    for (auto *resource: resources) {
        delete resource;
    }
    resources.clear();
}

std::vector<Process *> &Simulation::getProcesses() {
    return processes;
}

std::vector<Resource *> &Simulation::getResources() {
    return resources;
}


bool Simulation::maybeDetection() {
    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_set<int> visited, recursionStack;

    for (auto &process: getProcesses()) {
        for (auto &resource: getResources()) {
            if (resource->getOwner()) {
                graph[process->getId()].push_back(resource->getId());
                graph[resource->getId()].push_back(resource->getOwner()->getId());
            }
        }
    }

    for (auto &node: graph) {
        if (detectionUtils::hasCycle(node.first, graph, visited, recursionStack)) {
            std::cout << "Deadlock detected involving Process ID: " << node.first << std::endl;
            return true;
        }
    }
    std::cout << "No deadlock detected." << std::endl;
    return false;
}

void Simulation::generateDeadlockSituation() {
    auto *resA = new Resource(1, 1);
    auto *resB = new Resource(2, 1);
    auto *resC = new Resource(3, 1);

    auto *proc1 = new Process(1, this, {{resA, 0, 1},
                                        {resB, 1, 0},
                                        {resC, 1, 0}});
    auto *proc2 = new Process(2, this, {{resA, 1, 0},
                                        {resB, 0, 1},
                                        {resC, 1, 0}});
    auto *proc3 = new Process(3, this, {{resA, 1, 0},
                                        {resB, 1, 0},
                                        {resC, 0, 1}});

    addResource(resA);
    addResource(resB);
    addResource(resC);

    addProcess(proc1);
    addProcess(proc2);
    addProcess(proc3);

    proc1->requestResources();
    proc2->requestResources();
    proc3->requestResources();

    if (!window->isTableFilled(window->defaultTable)) {
        emit setTableData(window->defaultTable,
                          {QString::number(resA->getId()), proc1->getAllHeldResourceIds(),
                           proc1->getWaitingResourceIdsAsString(), QString::number(resA->getUnits())});
        emit setTableData(window->defaultTable,
                          {QString::number(resB->getId()), proc2->getAllHeldResourceIds(),
                           proc2->getWaitingResourceIdsAsString(), QString::number(resB->getUnits())});
        emit setTableData(window->defaultTable,
                          {QString::number(resC->getId()), proc3->getAllHeldResourceIds(),
                           proc3->getWaitingResourceIdsAsString(), QString::number(resC->getUnits())});

    }

    detectDeadlock();
}

bool Simulation::detectDeadlock() {
    // Clear the graph
    waitForGraph = WaitForGraph();

    // Add edges for waiting processes
    for (auto *process: processes) {
        for (auto &resTuple: process->getResourceRequirements()) {
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