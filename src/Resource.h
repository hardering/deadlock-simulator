#pragma once
#include <iostream>

class Resource {
private:
    int totalInstances;
    int availableInstances;

public:
    Resource(int total) : totalInstances(total), availableInstances(total) {}

    bool allocate(int instances) {
        if (availableInstances >= instances) {
            availableInstances -= instances;
            return true;
        }
        return false;
    }

    void release(int instances) {
        availableInstances += instances;
        if (availableInstances > totalInstances)
            availableInstances = totalInstances;
    }

    int getAvailableInstances() const {
        return availableInstances;
    }

    int getTotalInstances() const {
        return totalInstances;
    }
};
