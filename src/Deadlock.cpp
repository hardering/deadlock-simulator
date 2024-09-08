#include <Deadlock.h>
#include <QString>
#include "BankersAlgorithm.h"

Deadlock::Deadlock(Window *window) : window(window) {
    initializeResourcesAndProcesses();
    connect(this, &Deadlock::setTableData, window, &Window::setTableData);
    connect(window, &Window::resetTableRequest, this, &Deadlock::clear);
};

void Deadlock::initializeResourcesAndProcesses() {
    resources = {Resource(6), Resource(4), Resource(7)};
    processes = {
            Process(0, {3, 2, 2}, 1),
            Process(1, {2, 2, 2}, 2),
            Process(2, {3, 1, 3}, 3),
            Process(3, {2, 2, 4}, 1),
    };

    request_01 = {2, 1, 2};
    request_02 = {2, 1, 1};
    request_03 = {1, 1, 2};
    request_04 = {1, 1, 3};
}

void Deadlock::clear() {
    for (auto &resource: resources) {
        resource.release(resource.getTotalInstances());

    }

    for (auto &process: processes) {
        process.releaseResources(resources);
    }

    deadlockDetector->checkForDeadlock(*deadlockRecovery, processes, resources);
    std::cout << "Deadlock got cleared." << std::endl;

}

QString Deadlock::vectorToQString(const std::vector<int> &vec) {
    QString result;
    for (int value: vec) {
        result += QString::number(value) + " ";
    }
    return result.trimmed();
}

void Deadlock::requestResources() {
    processes[0].requestResources(request_01, resources);
    processes[1].requestResources(request_02, resources);
    processes[2].requestResources(request_03, resources);
    processes[3].requestResources(request_04, resources);
}

void Deadlock::createDeadlock() {
    requestResources();

    deadlockDetector->checkForDeadlock(*deadlockRecovery, processes, resources);

    if (!window->isTableFilled(window->defaultTable)) {
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[0].getPID()),
                                  processes[0].getState(processes, resources),
                                  vectorToQString(processes[0].getAllocatedResources()),
                                  vectorToQString(processes[0].getCurrentRequest()),
                          });
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[1].getPID()),
                                  processes[1].getState(processes, resources),
                                  vectorToQString(processes[1].getAllocatedResources()),
                                  vectorToQString(processes[1].getCurrentRequest()),
                          });
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[2].getPID()),
                                  processes[2].getState(processes, resources),
                                  vectorToQString(processes[2].getAllocatedResources()),
                                  vectorToQString(processes[2].getCurrentRequest()),
                          });
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[3].getPID()),
                                  processes[3].getState(processes, resources),
                                  vectorToQString(processes[3].getAllocatedResources()),
                                  vectorToQString(processes[3].getCurrentRequest()),
                          });

    }
}

void Deadlock::runBankersAlgorithm() {
    auto bankersAlgorithm = new BankersAlgorithm(processes, resources);
    deadlockDetector->checkForDeadlock(*deadlockRecovery, processes, resources);

    bool status0 = bankersAlgorithm->requestResources(processes[0].getPID(), request_01);
    bool status1 = bankersAlgorithm->requestResources(processes[1].getPID(), request_02);
    bool status2 = bankersAlgorithm->requestResources(processes[2].getPID(), request_03);
    bool status3 = bankersAlgorithm->requestResources(processes[3].getPID(), request_04);


    updateTable();
    emit setBankersEntry(processes[0].getPID(), status0);
    emit setBankersEntry(processes[1].getPID(), status1);
    emit setBankersEntry(processes[2].getPID(), status2);
    emit setBankersEntry(processes[3].getPID(), status3);

    delete bankersAlgorithm;
}

void Deadlock::runInterruptProcess() {
    clear();
    deadlockRecovery->interruptProcess(processes[0].getPID(), processes, resources);

    processes[1].requestResources(request_02, resources);
    processes[2].requestResources(request_03, resources);
    processes[3].requestResources(request_04, resources);
    updateTable();

}

void Deadlock::updateTable() {
    window->defaultTable->setRowCount(0);

    for (auto &process: processes) {
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(process.getPID()),
                                  process.getState(processes, resources),
                                  vectorToQString(process.getAllocatedResources()),
                                  vectorToQString(process.getCurrentRequest())
                          });
    }

    bool deadlockExists = !deadlockDetector->isSystemInSafeState(processes, resources);
    if (deadlockExists) {
        std::cout << "Deadlock exists after updating the table." << std::endl;
    } else {
        std::cout << "No deadlock after updating the table." << std::endl;
    }
}

void Deadlock::runAbortProcess() {
    int pid = 0;
    if (pid < processes.size()) {
        deadlockRecovery->abortProcess(pid, processes, resources);
        updateTable();
    } else {
        std::cerr << "Cannot abort process due to invalid ID." << std::endl;
    }
}

void Deadlock::runAvoidanceStrategy() {
    for (auto &process: processes) {
        if (!deadlockAvoidance->requestAllResourcesAtOnce(process, resources)) {
            std::cout << "Not enough resources to allocate all at once for Process " << process.getPID() << std::endl;

            if (!deadlockAvoidance->requestResourcesInOrder(process, resources)) {
                std::cout << "Failed to allocate resources in order for Process " << process.getPID() << std::endl;

                if (!deadlockAvoidance->preemptResources(process, processes, resources)) {
                    std::cout << "Failed to preempt resources for Process " << process.getPID() << std::endl;
                }
            }
        }
    }

    updateTable();
}






