#include "detectionUtils.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace detectionUtils {
    bool hasCycle(int node, const std::unordered_map<int, std::vector<int>> &graph,
                  std::unordered_set<int> &visited, std::unordered_set<int> &recursionStack) {
        if (recursionStack.find(node) != recursionStack.end()) {
            return true;
        }

        if (visited.find(node) != visited.end()) {
            return false;
        }

        visited.insert(node);
        recursionStack.insert(node);

        if (graph.find(node) != graph.end()) {
            try {
                for (int neighbor: graph.at(node)) {
                    if (hasCycle(neighbor, graph, visited, recursionStack)) {
                        return true;
                    }
                }
            } catch (const std::out_of_range &e) {
                std::cerr << "Key not found in the graph: " << e.what() << '\n';
            }
        }

        recursionStack.erase(node);
        return false;
    }
}