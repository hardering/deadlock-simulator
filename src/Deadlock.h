#pragma once

#import <QString>
#include <QTableWidget>

#include "Process.h"
#include "Resource.h"
#include "DeadlockRecovery.h"
#include "../qt/Window.h"

class Deadlock : public QObject {
Q_OBJECT

private:
    std::vector<Resource> resources;
    std::vector<Process> processes;
    Window *window;

public:

    Deadlock(Window *window);

    void initializeResourcesAndProcesses();

    void clear();

    QString vectorToQString(const std::vector<int> &vector);

public slots:

    void createDeadlock();

signals:

    void setTableData(QTableWidget *table, const QList<QString> &data);
};