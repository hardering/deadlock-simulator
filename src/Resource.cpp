#include "Resource.h"

Resource::Resource(int total) : totalInstances(total), availableInstances(total) {}

bool Resource::allocate(int instances) {
    if (availableInstances >= instances) {
        availableInstances -= instances;
        return true;
    }
    return false;
}

void Resource::release(int instances) {
    availableInstances += instances;
    if (availableInstances > totalInstances)
        availableInstances = totalInstances;
}

int Resource::getAvailableInstances() const {
    return availableInstances;
}

int Resource::getTotalInstances() const {
    return totalInstances;
}