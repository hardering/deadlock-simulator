#include "Simulation.h"
#include <iostream>

Simulation::Simulation(Window *windowInstance, QObject *parent) : QObject(parent), window(windowInstance) {
    connect(this, &Simulation::updateResourcesTable, window, &Window::updateResourcesTable);
    connect(window, &Window::generateDeadlockSituationRequest, this, &Simulation::generateDeadlockSituation);
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

void Simulation::generateDeadlockSituation() {
    auto *resA = new Resource(1, 1);
    auto *resB = new Resource(2, 5);
    auto *resC = new Resource(3, 3);

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

    emit updateResourcesTable(window->resourceTable,
                              {QString::number(resA->getId()), QString::number(resA->getUnits())});
    emit updateResourcesTable(window->resourceTable,
                              {QString::number(resB->getId()), QString::number(resB->getUnits())});
    emit updateResourcesTable(window->resourceTable,
                              {QString::number(resC->getId()), QString::number(resC->getUnits())});

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

