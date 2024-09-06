#include <Deadlock.h>

Deadlock::Deadlock() = default;

void Deadlock::createDeadlock(std::vector<Process> &processes, std::vector<Resource> &resources) {
    std::vector<int> request1 = {2, 1, 2};
    std::vector<int> request2 = {2, 1, 1};
    std::vector<int> request3 = {1, 1, 2};
    std::vector<int> request4 = {1, 1, 1};

    processes[0].requestResources(request1, resources);
    processes[1].requestResources(request2, resources);
    processes[2].requestResources(request3, resources);

    if (!processes[3].requestResources(request4, resources)) {
        std::cout << "Deadlock detected: Process 3 cannot allocate resources.\n";
    }
}