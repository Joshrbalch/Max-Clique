#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// Function to check if a vertex can be added to the current clique
bool isSafeToAdd(int v, const vector<vector<int>>& graph, const unordered_set<int>& clique) {
    for (int u : clique) {
        if (graph[v][u] == 0) // If v is not adjacent to u, return false
            return false;
    }
    return true;
}

// Function to find the maximal clique using a greedy approach
unordered_set<int> findMaxClique(const vector<vector<int>>& graph) {
    unordered_set<int> maxClique;
    unordered_set<int> currentClique;

    for (int v = 0; v < graph.size(); ++v) {
        // Try adding v to the current clique
        if (isSafeToAdd(v, graph, currentClique)) {
            currentClique.insert(v);
            // Check if the current clique is larger than the maxClique found so far
            if (currentClique.size() > maxClique.size()) {
                maxClique = currentClique;
            }
            // Recursively find the maximal clique by considering neighbors of v
            unordered_set<int> neighbors;
            for (int u : graph[v]) {
                if (currentClique.find(u) == currentClique.end()) {
                    neighbors.insert(u);
                }
            }
            if (!neighbors.empty()) {
                // Recursively find the maximal clique containing neighbors of v
                unordered_set<int> neighborClique = currentClique;
                for (int neighbor : neighbors) {
                    if (isSafeToAdd(neighbor, graph, neighborClique)) {
                        neighborClique.insert(neighbor);
                    }
                }
                // Update maxClique if the neighborClique is larger
                if (neighborClique.size() > maxClique.size()) {
                    maxClique = neighborClique;
                }
            }
            // Remove v from the current clique for backtracking
            currentClique.erase(v);
        }
    }

    return maxClique;
}

int main() {
    // Example graph representation (adjacency matrix)
    vector<vector<int>> graph = {
        {0, 1, 1, 1, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 0},
        {1, 1, 1, 0, 1},
        {0, 1, 0, 1, 0}
    };

    unordered_set<int> maxClique = findMaxClique(graph);

    cout << "Maximal clique: ";
    for (int node : maxClique) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Size of maximal clique: " << maxClique.size() << endl;

    return 0;
}