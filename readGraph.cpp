#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> // For stringstream
#include <stdexcept> // For runtime_error
#include <algorithm> // For find

using namespace std;

// Function to read the adjacency matrix from a file
vector<vector<int>> readAdjacencyMatrixFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> adjacencyMatrix;
    if (!file.is_open()) {
        throw runtime_error("Unable to open file " + filename);
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) // Skip empty lines
            continue;
        vector<int> row;
        stringstream ss(line); // Using stringstream to split the line
        int val;
        while (ss >> val) {
            row.push_back(val);
        }
        adjacencyMatrix.push_back(row);
    }

    file.close();
    return adjacencyMatrix;
}

// Function to update the graph with connections from other nodes

vector<vector<int>> updateGraph(vector<vector<int>>& graph) {
    for(int i = 0; i < graph.size(); i++) {
        // cout << "Checking node " << i << "\n";
        vector<int> connections = graph[i];
        for(int j = 0; j < graph.size(); j++) {
            int node = i;
            if(graph[j].empty() == 0) {
                for(int k = 0; k < graph[j].size(); k++) {
                    if(graph[j][k] == node && find(connections.begin(), connections.end(), j) == connections.end()) {
                        // cout << "Adding node " << j << " to node " << i << "\n";
                        connections.push_back(j);
                        graph[i].push_back(j);
                    }
                }
            }
        }
    }
    return graph;
}

// Function to convert adjacency matrix into a graph representation
vector<vector<int>> adjacencyMatrixToGraph(const vector<vector<int>>& adjacencyMatrix) {
    vector<vector<int>> graph(adjacencyMatrix.size());
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                graph[i].push_back(j);
            }
        }
    }

    // Update the graph with connections from other nodes
    updateGraph(graph);

    return graph;
}

int main() {
    string filename = "Q15V100.adjmat"; // Replace with the actual filename
    try {
        vector<vector<int>> adjacencyMatrix = readAdjacencyMatrixFromFile(filename);
        vector<vector<int>> graph = adjacencyMatrixToGraph(adjacencyMatrix);

        // Print the graph
        for (size_t i = 0; i < graph.size(); ++i) {
            cout << "Node " << i << " is connected to nodes: ";
            for (size_t j = 0; j < graph[i].size(); ++j) {
                cout << graph[i][j] << " ";
            }
            cout << endl;
        }
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
