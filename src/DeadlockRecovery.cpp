#include "DeadlockRecovery.h"

void DeadlockRecovery::interruptProcess(int pid, std::vector<Process> &processes, std::vector<Resource> &resources) {
    for (auto &process: processes) {
        if (process.getPID() == pid) {
            process.interrupt();
            process.releaseResources(resources);
            std::cout << "Interrupting process " << pid << " to resolve deadlock...\n";
            break;
        }
    }
}

void DeadlockRecovery::rollbackProcess(int pid, std::vector<Process> &processes, std::vector<Resource> &resources) {
    std::cout << "Rolling back process " << pid << " to its initial state...\n";
    processes[pid].releaseResources(resources);
    processes[pid].reset();
}

void DeadlockRecovery::abortProcess(int pid, std::vector<Process> &processes, std::vector<Resource> &resources) {
    std::cout << "Aborting process " << pid << " to resolve deadlock...\n";
    processes[pid].releaseResources(resources);
    processes.erase(processes.begin() + pid);
}

void DeadlockRecovery::resolveDeadlock(std::vector<Process> &processes, std::vector<Resource> &resources,
                                       const std::string &strategy) {
    if (strategy == "interrupt") {
        for (size_t i = 0; i < processes.size(); ++i) {
            if (!processes[i].isFinished()) {
                interruptProcess(i, processes, resources);
                break;
            }
        }
    } else if (strategy == "rollback") {
        for (size_t i = 0; i < processes.size(); ++i) {
            if (!processes[i].isFinished()) {
                rollbackProcess(i, processes, resources);
                break;
            }
        }
    } else if (strategy == "abort") {
        for (size_t i = 0; i < processes.size(); ++i) {
            if (!processes[i].isFinished()) {
                abortProcess(i, processes, resources);
                break;
            }
        }
    }
}

bool DeadlockRecovery::detectDeadlock(const std::vector<Process> &processes, const std::vector<Resource> &resources) {
    return !detector->isSystemInSafeState(const_cast<std::vector<Process> &>(processes),
                                          const_cast<std::vector<Resource> &>(resources));
}
