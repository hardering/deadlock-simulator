// DeadlockDetector.h

#pragma once
#include <vector>
#include "Process.h"
#include "Resource.h"

class DeadlockDetector {
public:
    bool isSystemInSafeState(std::vector<Process>& processes, std::vector<Resource>& resources) {
        std::vector<int> work(resources.size());
        std::vector<bool> finish(processes.size(), false);

        for (size_t i = 0; i < resources.size(); ++i) {
            work[i] = resources[i].getAvailableInstances();
        }

        bool progressMade;
        do {
            progressMade = false;
            for (size_t i = 0; i < processes.size(); ++i) {
                if (!finish[i] && canProcessComplete(processes[i], work)) {
                    finish[i] = true;
                    progressMade = true;

                    for (size_t j = 0; j < work.size(); ++j) {
                        work[j] += processes[i].getNeededResources()[j];
                    }
                }
            }
        } while (progressMade);

        for (bool f : finish) {
            if (!f) return false;
        }

        return true;
    }

private:
    bool canProcessComplete(const Process& process, const std::vector<int>& work) const {
        const std::vector<int>& neededResources = process.getNeededResources();
        for (size_t i = 0; i < work.size(); ++i) {
            if (neededResources[i] > work[i]) {
                return false;
            }
        }
        return true;
    }
};
