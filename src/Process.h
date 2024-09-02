#ifndef PROCESS_H
#define PROCESS_H

#include <vector>
#include "Resource.h"
#include "Simulation.h"

class Simulation;

class Process {
private:
    int id;
    std::vector<Resource*> allocatedResources;
    Simulation* simulation;

public:
    Process(int id, Simulation* sim);
    int getId() const { return id; }
    bool requestResource(Resource *resource);
    bool holdsResource(Resource *resource);
    void releaseResources();
    void performRollback();
    void terminate();
    void printHoldingResources();
    void addResource(Resource *resource);
};

#endif // PROCESS_H
