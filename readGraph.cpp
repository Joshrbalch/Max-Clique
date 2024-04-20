#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Function to read the adjacency matrix from a file
vector<vector<int>> readAdjacencyMatrixFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> adjacencyMatrix;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<int> row;
            size_t pos = 0;
            while ((pos = line.find(' ')) != string::npos) {
                string token = line.substr(0, pos);
                row.push_back(stoi(token));
                line.erase(0, pos + 1);
            }
            row.push_back(stoi(line));
            adjacencyMatrix.push_back(row);
        }
        file.close();
    } else {
        cout << "Unable to open file " << filename << endl;
    }
    return adjacencyMatrix;
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
    return graph;
}

// int main() {
//     string filename = "Q15V100.adjmat"; // Replace "your_filename_here.txt" with the actual filename
//     vector<vector<int>> adjacencyMatrix = readAdjacencyMatrixFromFile(filename);
//     vector<vector<int>> graph = adjacencyMatrixToGraph(adjacencyMatrix);

//     // Print the graph
//     for (size_t i = 0; i < graph.size(); ++i) {
//         cout << "Node " << i << " is connected to nodes: ";
//         for (size_t j = 0; j < graph[i].size(); ++j) {
//             cout << graph[i][j] << " ";
//         }
//         cout << endl;
//     }

//     return 0;
// }
