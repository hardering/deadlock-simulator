#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "Process.h"
#include "Resource.h"

class Simulation {
private:
    std::vector<Process*> processes;
    std::vector<Resource*> resources;

public:
    void detectDeadlocks();
    void resolveDeadlockByTermination();
    void resolveDeadlockByRollback();
    void addProcess(Process* proc);
    void addResource(Resource* res);
    void removeProcess(Process* proc);
};

#endif
