#pragma once

#include <iostream>

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
};
