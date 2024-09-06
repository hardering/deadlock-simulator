#ifndef RESOURCE_H
#define RESOURCE_H

#include <set>
#include <vector>
#include <list>

class Process;

class Resource {
private:
    int id;
    int units;
    Process *owner;
    std::vector<std::pair<Process *, int>> waitingList;

public:
    explicit Resource(int id, int units);

    bool requestResource(Process *requestor, int requestedUnits);

    void releaseResources(int releasedUnits);

    void addToWaitingList(Process *process, int neededUnits);

    Process *getOwner() const;

    int getId() const { return id; }

    void printStatus() const;

    int getUnits() const;
};

#endif
