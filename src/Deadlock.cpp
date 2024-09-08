#include <Deadlock.h>
#include <QString>
#include "BankersAlgorithm.h"

Deadlock::Deadlock(Window *window) : window(window) {
    initializeResourcesAndProcesses();
    connect(this, &Deadlock::setTableData, window, &Window::setTableData);
    connect(window, &Window::resetTableRequest, this, &Deadlock::clear);
};

void Deadlock::initializeResourcesAndProcesses() {
    resources = { Resource(6), Resource(4), Resource(7) };
    processes = {
            Process(0, {3, 2, 2}, 1),  // Prozess 0, Priorität 1
            Process(1, {2, 2, 2}, 2),  // Prozess 1, Priorität 2
            Process(2, {3, 1, 3}, 3),  // Prozess 2, Priorität 3
            Process(3, {2, 2, 2}, 1),  // Prozess 3, Priorität 1
            Process(4, {4, 3, 3}, 2)   // Prozess 4, Priorität 2
    };
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
    processes[3].requestResources(request_03, resources);
}

void Deadlock::createDeadlock() {
    requestResources();
    deadlockDetector->checkForDeadlock(*deadlockRecovery, processes, resources);

    if (deadlockDetector->isSystemInSafeState(processes, resources)) {
        std::cout << "Safe" << std::endl;
    } else {
        std::cout << "Not Safe" << std::endl;

    }
    std::vector<int> request1 = {2, 1, 2};  // Process 0 requests resources
    std::vector<int> request2 = {2, 1, 1};  // Process 1 requests resources
    std::vector<int> request3 = {1, 1, 2};  // Process 2 requests resources
    std::vector<int> request4 = {1, 1, 1};  // Process 3 requests resources

    // Allocate resources that will cause a deadlock
    processes[0].requestResources(request1, resources);  // Process 0 allocated
    processes[1].requestResources(request2, resources);  // Process 1 allocated
    processes[2].requestResources(request3, resources);  // Process 2 allocated
    if (!processes[3].requestResources(request4, resources)) {
        std::cout << "Deadlock detected: Process 3 cannot allocate resources.\n";
    }
    deadlockDetector->checkForDeadlock(*deadlockRecovery, processes, resources);
    if (!window->isTableFilled(window->defaultTable)) {
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[0].getPID()),
                                  processes[0].getState(processes, resources),
                                  vectorToQString(processes[0].getAllocatedResources()),
                                  vectorToQString(request_01),
                          });
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[1].getPID()),
                                  processes[1].getState(processes, resources),
                                  vectorToQString(processes[1].getAllocatedResources()),
                                  vectorToQString(request_02),
                          });
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[2].getPID()),
                                  processes[2].getState(processes, resources),
                                  vectorToQString(processes[2].getAllocatedResources()),
                                  vectorToQString(request_03),
                          });
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[3].getPID()),
                                  processes[3].getState(processes, resources),
                                  vectorToQString(processes[3].getAllocatedResources()),
                                  vectorToQString(request_03),
                          });

    }
}

void Deadlock::runBankersAlgorithm() {
    auto bankersAlgorithm = new BankersAlgorithm(processes, resources);
    deadlockDetector->checkForDeadlock(*deadlockRecovery, processes, resources);

    bool status0 = bankersAlgorithm->requestResources(processes[0].getPID(), request_01);
    bool status1 = bankersAlgorithm->requestResources(processes[1].getPID(), request_02);
    bool status2 = bankersAlgorithm->requestResources(processes[2].getPID(), request_03);
    bool status3 = bankersAlgorithm->requestResources(processes[3].getPID(), request_03);

    emit setBankersEntry(processes[0].getPID(), status0);
    emit setBankersEntry(processes[1].getPID(), status1);
    emit setBankersEntry(processes[2].getPID(), status2);
    emit setBankersEntry(processes[3].getPID(), status3);

    delete bankersAlgorithm;
}

void Deadlock::runInterruptProcess() {
    deadlockRecovery->interruptProcess(processes[0].getPID(), processes, resources);
    updateTable();

}

void Deadlock::updateTable() {
    window->defaultTable->setRowCount(0);

    bool deadlockExists = !deadlockDetector->isSystemInSafeState(processes, resources);

    processes[1].requestResources(request_02, resources);
    processes[2].requestResources(request_03, resources);
    processes[3].requestResources(request_03, resources);

    if (!window->isTableFilled(window->defaultTable)) {
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[0].getPID()),
                                  processes[0].getState(processes, resources),
                                  vectorToQString(processes[0].getAllocatedResources()),
                                  vectorToQString(request_01),
                          });
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[1].getPID()),
                                  processes[1].getState(processes, resources),
                                  vectorToQString(processes[1].getAllocatedResources()),
                                  vectorToQString(request_02),
                          });
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[2].getPID()),
                                  processes[2].getState(processes, resources),
                                  vectorToQString(processes[2].getAllocatedResources()),
                                  vectorToQString(request_03),
                          });
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[3].getPID()),
                                  processes[3].getState(processes, resources),
                                  vectorToQString(processes[3].getAllocatedResources()),
                                  vectorToQString(request_03),
                          });

    }

    if (deadlockExists) {
        std::cout << "Deadlock exists after interrupting the process." << std::endl;
    } else {
        std::cout << "No deadlock present after intervention." << std::endl;
    }
}






