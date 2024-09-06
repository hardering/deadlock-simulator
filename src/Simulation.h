#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <QObject>
#include "Process.h"
#include "Resource.h"
#include "Graph.h"

class Simulation : public QObject {
Q_OBJECT

public:
    explicit Simulation(QObject *parent = nullptr);
    void addProcess(Process *process);
    void addResource(Resource *resource);
    void removeProcess(Process *process);
    void initializeProcessWithResources();
    bool detectDeadlock();  // Add this line

signals:
    void resourceAdded(int id);
    void processAdded(int id);

private:
    std::vector<Process *> processes;
    std::vector<Resource *> resources;
    WaitForGraph waitForGraph;
};

#endif // SIMULATION_H