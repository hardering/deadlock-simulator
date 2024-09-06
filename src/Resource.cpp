#include "Resource.h"
#include <vector>

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

void Resource::printResources(const std::vector<Resource> &resources) {
    std::cout << "Current available resources:\n";
    for (size_t i = 0; i < resources.size(); ++i) {
        std::cout << "Resource " << i << ": " << resources[i].getAvailableInstances() << "\n";
    }
}
