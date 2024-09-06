#ifndef PROCESS_H
#define PROCESS_H

#include <vector>
#include "Resource.h"
#include "Simulation.h"

class Simulation;

class Process {
private:
    int id;
    std::vector<Resource *> allocatedResources;
    Simulation *simulation;
    std::vector<int> waitingResourceIds;

public:
    Process(int id, Simulation *sim, std::vector<std::tuple<Resource *, int, int>> resRequirements);

    int getId() const { return id; }

    QString getAllHeldResourceIds() const;

    void requestResources();

    bool holdsResource(Resource *resource);

    void releaseResources();

    void performRollback();

    void terminate();

    void addResource(Resource *resource);

    void printStatus() const;

    std::vector<std::tuple<Resource *, int, int>> resources;

    QString getWaitingResourceIdsAsString() const;
};

#endif
