#ifndef RESOURCE_H
#define RESOURCE_H

#include <set>

class Process;

class Resource {
private:
    int id;
    Process* owner;
    std::set<Process*> waitingList;

public:
    explicit Resource(int id);
    bool requestResource(Process* requestor);
    void releaseResource();
    void addToWaitingList(Process* process);
    bool isAvailable() const;
    Process* getOwner() const;
    void printWaitingQueue() const;
    int getId() const { return id; }
};

#endif
