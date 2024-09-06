#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>

class WaitForGraph {
public:
    void addEdge(int from, int to);
    bool hasCycle();

private:
    std::unordered_map<int, std::unordered_set<int>> adjList;
    bool hasCycleUtil(int node, std::unordered_set<int> &visited, std::unordered_set<int> &recStack);
};

#endif // GRAPH_H