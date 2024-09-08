#pragma once

#import <QString>
#include <QTableWidget>

#include "Process.h"
#include "Resource.h"
#include "DeadlockRecovery.h"
#include "../qt/Window.h"
#include "DeadlockAvoidance.h"

class Deadlock : public QObject {
Q_OBJECT

private:
    std::vector<Resource> resources;
    std::vector<Process> processes;
    Window *window;
    std::vector<int> request_01, request_02, request_03, request_04;
    std::vector<std::vector<int>> requests;
    DeadlockDetector *deadlockDetector;
    DeadlockRecovery *deadlockRecovery;
    DeadlockAvoidance *deadlockAvoidance;
    std::string status;

public:

    Deadlock(Window *window);

    void initializeResourcesAndProcesses();

    void clear();

    QString vectorToQString(const std::vector<int> &vector);

    void updateTable();
    
    std::vector<int> getRequest(int n);

    QString getState();

public slots:

    void createDeadlock();

    void runBankersAlgorithm();

    void runInterruptProcess();

    void runAbortProcess();

    void runAvoidanceStrategy();

signals:

    void setTableData(QTableWidget *table, const QList<QString> &data);

    void setBankersEntry(int processId, bool status);
};