#include "heuristic.cpp"
#include "brute.cpp"
#include "original.cpp"
#include "readGraph.cpp"
#include "randMatrix.cpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    Brute brute;
    Heuristic heuristic;
    Original original;
    RandomGraphGenerator graphGenerator;

    cout << "Enter the number of vertices: ";
    int n;
    cin >> n;
    cout << endl;

    graphGenerator.generateRandomAdjacencyMatrix(n);
    string filename = "Q60V1000.adjmat";

    // cout << "Enter the file to read from: ";
    // cin >> filename;
    // cout << endl;

    cout << "Heuristic algorithm: " << endl;
    heuristic.run(filename);
    heuristic.print();

    cout << "Original algorithm: " << endl;
    original.run(filename);
    original.print();

    cout << "Brute force algorithm: " << endl;
    brute.run(graphGenerator.getGraph());
    brute.print();

    return 0;
}