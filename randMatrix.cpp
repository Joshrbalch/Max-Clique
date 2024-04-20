#include <iostream>
#include <vector>

using namespace std;

std::vector<std::vector<int>> generateAdjacencyMatrix(int n) {
    // Create a vector of vectors to represent the adjacency matrix
    std::vector<std::vector<int>> adjacencyMatrix(n, std::vector<int>(n, 0));

    // Fill the adjacency matrix with the specified pattern
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == i - 1)
                adjacencyMatrix[i][j] = i - 1;
            else if (j == i + 1)
                adjacencyMatrix[i][j] = i;
            else if (j == i)
                adjacencyMatrix[i][j] = i;
            else
                adjacencyMatrix[i][j] = 0;
        }
    }

    return adjacencyMatrix;
}

int main() {
    int n = 10; // Number of nodes
    vector<vector<int>> matrix = generateAdjacencyMatrix(n);

    // Print the adjacency matrix
    int node = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << node++ << endl;
    }

    return 0;
}
