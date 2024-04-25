#include <iostream>
#include <vector>
#include <algorithm>
#include "readGraph.cpp"

using namespace std;

class Brute {
private:
    // Function to check if a given subset is a clique
    bool isClique(const vector<vector<int>>& graph, const vector<int>& subset) {
        for (size_t i = 0; i < subset.size(); ++i) {
            for (size_t j = i + 1; j < subset.size(); ++j) {
                if (find(graph[subset[i]].begin(), graph[subset[i]].end(), subset[j]) == graph[subset[i]].end()) {
                    return false;
                }
            }
        }
        return true;
    }

    // Function to generate all possible subsets of a given size
    void generateSubsets(const vector<vector<int>>& graph, int size, vector<int>& currentSubset, vector<vector<int>>& allSubsets, int index) {
        if (currentSubset.size() == size) {
            allSubsets.push_back(currentSubset);
            return;
        }
        if (index >= graph.size()) {
            return;
        }
        currentSubset.push_back(index);
        generateSubsets(graph, size, currentSubset, allSubsets, index + 1);
        currentSubset.pop_back();
        generateSubsets(graph, size, currentSubset, allSubsets, index + 1);
    }

public:
    vector<int> maxClique;

    // Function to find the maximum clique in a graph
    vector<int> run(const vector<vector<int>>& graph) {
        int maxSize = 0;
        for (size_t i = 1; i <= graph.size(); ++i) {
            vector<vector<int>> allSubsets;
            vector<int> currentSubset;
            generateSubsets(graph, i, currentSubset, allSubsets, 0);
            for (const auto& subset : allSubsets) {
                if (isClique(graph, subset) && subset.size() > maxSize) {
                    maxSize = subset.size();
                    maxClique = subset;
                }
            }
        }
        return maxClique;
    }

    void print() {
        cout << "Maximum clique: ";
        for (int node : maxClique) {
            cout << node << " ";
        }
        cout << endl;
        cout << "Size of the maximum clique: " << maxClique.size() << endl;
    
    }
};

int main() {
    // Example graph
    vector<vector<int>> graph = {
        {1, 2},
        {0, 2, 3},
        {0, 1, 3},
        {1, 2},
        {1,3},
    };

    // string filename;

    // cout << "Enter the filename: ";
    // cin >> filename;

    // vector<vector<int>> graph = readAdjacencyMatrixFromFile(filename);

    Brute cliqueFinder;
    vector<int> maxClique = cliqueFinder.run(graph);

    cout << "Maximum clique: ";
    for (int node : maxClique) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Size of the maximum clique: " << maxClique.size() << endl;

    return 0;
}
