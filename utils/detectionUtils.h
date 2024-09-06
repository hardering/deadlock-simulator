#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace detectionUtils {
    bool hasCycle(int node, const std::unordered_map<int, std::vector<int>> &graph,
                  std::unordered_set<int> &visited, std::unordered_set<int> &recursionStack);
}