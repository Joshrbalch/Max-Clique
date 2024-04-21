#include <iostream>
#include <vector>
#include <random>

using namespace std;

class RandomGraphGenerator {
private:
    // Random number generator engine
    random_device rd;
    mt19937 gen;

public:
    vector<vector<int>> graph;
    
    RandomGraphGenerator() : gen(rd()) {}

    vector<vector<int>> getGraph() {
        return graph;
    }

    // Function to generate a random adjacency matrix for a graph with n vertices
    vector<vector<int>> generateRandomAdjacencyMatrix(int n) {
        uniform_int_distribution<> dis(0, 1); // 0 for no edge, 1 for edge

        // Initialize adjacency matrix with zeros
        vector<vector<int>> adjacencyMatrix(n, vector<int>(n, 0));

        // Generate random edges
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                adjacencyMatrix[i][j] = dis(gen);
                adjacencyMatrix[j][i] = adjacencyMatrix[i][j]; // Undirected graph
            }
        }
        graph = adjacencyMatrix;
        return adjacencyMatrix;
    }

    // Function to print adjacency matrix
    void printAdjacencyMatrix(const vector<vector<int>>& adjacencyMatrix) {
        for (const auto& row : adjacencyMatrix) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
};

// int main() {
//     RandomGraphGenerator graphGenerator;

//     int n; // Number of vertices
//     cout << "Enter the number of vertices: ";
//     cin >> n;

//     // Generate random adjacency matrix
//     vector<vector<int>> randomAdjacencyMatrix = graphGenerator.generateRandomAdjacencyMatrix(n);

//     // Print the generated adjacency matrix
//     cout << "Random Adjacency Matrix:" << endl;
//     graphGenerator.printAdjacencyMatrix(randomAdjacencyMatrix);

//     return 0;
// }
