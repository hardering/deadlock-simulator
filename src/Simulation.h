#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <QObject>
#include "Process.h"
#include "Resource.h"
#include "../qt/Window.h"

class Simulation : public QObject {
Q_OBJECT

private:
    std::vector<Process *> processes;
    std::vector<Resource *> resources;
    Window *window;

public:
    explicit Simulation(Window *window, QObject *parent = nullptr);

    void addProcess(Process *process);

    void addResource(Resource *resource);

    void removeProcess(Process *process);

    void generateDeadlockSituation();

    void clearAll();

private:

signals:

    void setTableData(QTableWidget *table, const QList<QString> &data);
};

#endif
