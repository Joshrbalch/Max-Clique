#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "readGraph.cpp"

using namespace std;

class Heuristic {
private:
    // Function to find the vertex cover using the 2-approximation algorithm
    unordered_set<int> findVertexCover(const vector<vector<int>>& graph) {
        unordered_set<int> cover;
        vector<bool> visited(graph.size(), false);

        for (int u = 0; u < graph.size(); ++u) {
            if (!visited[u]) {
                for (int v : graph[u]) {
                    if (!visited[v]) {
                        cover.insert(u);
                        cover.insert(v);
                        visited[u] = true;
                        visited[v] = true;
                        break;
                    }
                }
            }
        }

        return cover;
    }

    // Function to construct the complement graph
    vector<vector<int>> constructComplementGraph(const vector<vector<int>>& graph) {
        vector<vector<int>> complement(graph.size(), vector<int>());

        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph.size(); ++j) {
                if (i != j && find(graph[i].begin(), graph[i].end(), j) == graph[i].end()) {
                    complement[i].push_back(j);
                }
            }
        }

        return complement;
    }

    // Function to find the independent set in the complement graph
    vector<int> findIndependentSet(const vector<vector<int>>& complementGraph) {
        vector<int> independentSet;

        for (int u = 0; u < complementGraph.size(); ++u) {
            bool isIndependent = true;
            for (int v : independentSet) {
                if (find(complementGraph[u].begin(), complementGraph[u].end(), v) != complementGraph[u].end()) {
                    isIndependent = false;
                    break;
                }
            }
            if (isIndependent) {
                independentSet.push_back(u);
            }
        }

        return independentSet;
    }

public:
    vector<int> maxClique;

    // Function to find maximal clique from vertex cover
    vector<int> run(const string& filename) {
        vector<vector<int>> adjacencyMatrix = readAdjacencyMatrixFromFile(filename);

        // Step 1: Find vertex cover
        unordered_set<int> vertexCover = findVertexCover(adjacencyMatrix);

        // Step 2: Construct complement graph
        vector<vector<int>> complementGraph = constructComplementGraph(adjacencyMatrix);

        // Step 3: Find independent set in complement graph
        vector<int> independentSet = findIndependentSet(complementGraph);

        maxClique = independentSet;

        return independentSet;
    }

    void print() {
        cout << "Maximal Clique: ";
        for (int node : maxClique) {
            cout << node << " ";
        }  
        cout << endl;

        cout << "Size of maximal clique: " << maxClique.size() << endl << endl;
    }
};

// int main() {
//     cout << "Starting..." << endl;

//     string filename;

//     cout << "Enter the filename: ";
//     cin >> filename;

//     MaximalCliqueFromVertexCover cliqueFinder;
//     vector<int> maximalClique = cliqueFinder.findMaximalClique(filename);

//     // Debug: Print the independent set
//     cout << "Maximal Clique:" << endl;
//     for (int node : maximalClique) {
//         cout << node << " ";
//     }
//     cout << endl;

//     cout << "Size of maximal clique for file " << filename << ": " << maximalClique.size() << endl;

//     return 0;
// }
