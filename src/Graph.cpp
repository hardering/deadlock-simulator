#include "Graph.h"

void WaitForGraph::addEdge(int from, int to) {
    adjList[from].insert(to);
}

bool WaitForGraph::hasCycle() {
    std::unordered_set<int> visited;
    std::unordered_set<int> recStack;
    for (const auto &node : adjList) {
        if (hasCycleUtil(node.first, visited, recStack)) {
            return true;
        }
    }
    return false;
}

bool WaitForGraph::hasCycleUtil(int node, std::unordered_set<int> &visited, std::unordered_set<int> &recStack) {
    if (!visited.count(node)) {
        visited.insert(node);
        recStack.insert(node);

        for (int neighbor : adjList[node]) {
            if (!visited.count(neighbor) && hasCycleUtil(neighbor, visited, recStack)) {
                return true;
            } else if (recStack.count(neighbor)) {
                return true;
            }
        }
    }
    recStack.erase(node);
    return false;
}