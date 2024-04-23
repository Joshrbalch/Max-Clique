#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <random>
#include "readGraph.cpp"

using namespace std;

class MaxCliqueFinder {
private:
    unordered_set<int> Q;
    unordered_set<int> Qmax;

    // Function to find a vertex with maximum color from set R
    int findMaxColorVertex(const unordered_set<int>& R, const vector<int>& colors) {
        int maxColor = -1;
        int maxColorVertex = -1;

        for (int vertex : R) {
            if (colors[vertex] > maxColor) {
                maxColor = colors[vertex];
                maxColorVertex = vertex;
            }
        }
        return maxColorVertex;
    }

    // Function to obtain a vertex-coloring of G(R ∩ Γ(p))
    vector<int> getColoring(const unordered_set<int>& intersection, const vector<vector<int>>& graph, const vector<int>& colors) {
        vector<int> newColors(graph.size(), -1);

        for (int vertex : intersection) {
            newColors[vertex] = colors[vertex];
        }

        return newColors;
    }

    // Function to recursively find the maximal clique
    void MaxClique(unordered_set<int> R, const vector<vector<int>>& graph, const vector<int>& colors) {
        if (R.empty()) { 
            return;
        }

        int p = findMaxColorVertex(R, colors);
        R.erase(p);

        if (Q.size() + colors[p] > Qmax.size()) {
            Q.insert(p);
            unordered_set<int> intersection;
            for (int neighbor : graph[p]) {
                if (R.find(neighbor) != R.end()) {
                    intersection.insert(neighbor);
                }
            }

            if (!intersection.empty()) {
                vector<int> newColors = getColoring(intersection, graph, colors);
                MaxClique(intersection, graph, newColors);
            } 
            
            else if (Q.size() > Qmax.size()) {
                Qmax = Q;
            }
            Q.erase(p);
        } 
        
        else {
            return;
        }
    }

public:
    unordered_set<int> findMaxClique(const vector<vector<int>>& graph, const vector<int>& colors) {
        unordered_set<int> R;

        for (int i = 0; i < graph.size(); ++i) {
            R.insert(i);
        }

        MaxClique(R, graph, colors);
        return Qmax;
    }
};

// Function to generate random colors for the vertices
vector<int> generateRandomColors(int numVertices, int numColors) {
    vector<int> colors(numVertices);

    for (int i = 0; i < numVertices; ++i) {
        colors[i] = rand() % numColors; // Generate a random color between 0 and numColors-1
    }

    return colors;
}

int main() {
    // Test Graph
    // vector<vector<int>> graph = {
    //     {0, 1, 1, 0, 1},
    //     {1, 0, 1, 1, 0},
    //     {1, 1, 0, 1, 0},
    //     {0, 1, 1, 0, 1},
    //     {1, 0, 0, 1, 0}
    // };

    vector<vector<int>> graph = readAdjacencyMatrixFromFile("Q60V1000.adjmat");

    int numVertices = graph.size();
    int numColors = numVertices; // Number of colors to use

    vector<int> colors = generateRandomColors(numVertices, numColors);

    MaxCliqueFinder finder;
    unordered_set<int> maxClique = finder.findMaxClique(graph, colors);

    cout << "Maximal clique: ";
    for (int node : maxClique) {
        cout << node << " ";
    }

    cout << endl;

    cout << "Size of maximal clique: " << maxClique.size() << endl;

    return 0;
}
