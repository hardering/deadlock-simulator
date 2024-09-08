#pragma once

#include <iostream>
#include <vector>
class Resource {
private:
    int totalInstances;
    int availableInstances;

public:
    explicit Resource(int total);

    bool allocate(int instances);

    void release(int instances);

    int getAvailableInstances() const;

    int getTotalInstances() const;

    void printResources(const std::vector<Resource> &resources);

};
