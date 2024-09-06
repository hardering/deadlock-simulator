#include "Simulation.h"
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


void Simulation::generateDeadlockSituation() {
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

    addProcess(proc1);
    addProcess(proc2);
    addProcess(proc3);

    proc1->requestResources();
    proc2->requestResources();
    proc3->requestResources();

    if (!window->isTableFilled(window->defaultTable)) {
        emit setTableData(window->defaultTable,
                          {QString::number(resA->getId()), proc1->getAllHeldResourceIds(),
                           proc1->getWaitingResourceIdsAsString()});
        emit setTableData(window->defaultTable,
                          {QString::number(resB->getId()), proc2->getAllHeldResourceIds(),
                           proc2->getWaitingResourceIdsAsString()});
        emit setTableData(window->defaultTable,
                          {QString::number(resC->getId()), proc3->getAllHeldResourceIds(),
                           proc3->getWaitingResourceIdsAsString()});

    }
}

