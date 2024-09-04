#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <QObject>
#include "Process.h"
#include "Resource.h"

class Simulation : public QObject {
Q_OBJECT

private:
    std::vector<Process *> processes;
    std::vector<Resource *> resources;

public:
    explicit Simulation(QObject *parent = nullptr);

    void addProcess(Process *process);

    void addResource(Resource *resource);

    void removeProcess(Process *process);

    void initializeProcessWithResources();

signals:

    void resourceAdded(int id);

    void processAdded(int id);
};

#endif
