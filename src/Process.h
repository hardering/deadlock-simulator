#ifndef PROCESS_H
#define PROCESS_H

#include <vector>
#include "Resource.h"
#include "Simulation.h"

class Simulation;

class Process {
private:
    int id;
    std::vector<std::tuple<Resource*, int, int>> resources;
    std::vector<Resource*> allocatedResources;
    Simulation* simulation;

public:
    Process(int id, Simulation* sim, std::vector<std::tuple<Resource*, int, int>> resRequirements);
    int getId() const { return id; }
    void requestResources();
    bool holdsResource(Resource *resource);
    void releaseResources();
    void performRollback();
    void terminate();
    void addResource(Resource *resource);
    void printStatus() const;
};

#endif
