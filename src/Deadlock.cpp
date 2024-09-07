#include <Deadlock.h>
#include <QString>

Deadlock::Deadlock() {

};

QString Deadlock::vectorToQString(const std::vector<int> &vec) {
    QString result;
    for (int value: vec) {
        result += QString::number(value) + " ";
    }
    return result.trimmed();
}

void Deadlock::createDeadlock(Window *window) {
    connect(this, &Deadlock::setTableData, window, &Window::setTableData);

    std::vector<Resource> resources =
            {
                    Resource(6), Resource(4), Resource(7)
            };

    std::vector<Process> processes =
            {
                    Process(0, {3, 2, 2}, 1),
                    Process(1, {2, 2, 2}, 2),
                    Process(2, {3, 1, 3}, 3),
                    Process(3, {2, 2, 2}, 1),
            };

    std::vector<int> request1 = {2, 1, 2};
    std::vector<int> request2 = {2, 1, 1};
    std::vector<int> request3 = {1, 1, 2};
    std::vector<int> request4 = {1, 1, 1};

    processes[0].requestResources(request1, resources);
    processes[1].requestResources(request2, resources);
    processes[2].requestResources(request3, resources);
    processes[3].requestResources(request3, resources);
    processes[3].requestResources(request4, resources);

    auto *deadlockDetector = new DeadlockDetector();
    auto *deadlockRecovery = new DeadlockRecovery();
    deadlockDetector->checkForDeadlock(*deadlockRecovery, processes, resources);


    if (!window->isTableFilled(window->defaultTable)) {
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[0].getPID()),
                                  processes[0].getState(processes, resources),
                                  vectorToQString(processes[0].getNeededResources()),
                                  vectorToQString(request1),
                          });
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[1].getPID()),
                                  processes[1].getState(processes, resources),
                                  vectorToQString(processes[1].getNeededResources()),
                                  vectorToQString(request2),
                          });
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[2].getPID()),
                                  processes[2].getState(processes, resources),
                                  vectorToQString(processes[2].getNeededResources()),
                                  vectorToQString(request3),
                          });
        emit setTableData(window->defaultTable,
                          {
                                  QString::number(processes[3].getPID()),
                                  processes[3].getState(processes, resources),
                                  vectorToQString(processes[3].getNeededResources()),
                                  vectorToQString(request3),
                          });

    }
}
