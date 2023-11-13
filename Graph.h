#include <vector>
#include <string>
#include <iostream>
#include <limits.h>
#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
    // constructor
    Graph(int numVertices);

    // destructor
    ~Graph();

    // method to add an edge between two vertices with a given weight
    void addEdge(int u, int v, int weight);

    // method to get the weight of an edge between two vertices
    int getEdgeWeight(int u, int v) const;

    // method to get the number of vertices in the graph
    int getNumVertices() const;

    // method to get the number of edges in the graph
    int getNumEdges() const;

    // method to convert the graph into a string
    std::string toString() const;

    // method to get the adjacency matrix
    std::vector<std::vector<int>> getAdjecencyMatrix() const;

    //  method to calculate cost of the path
    int calculateCost(std::vector<int> &path);

    // method to find the optimal path
    void findHamiltonianCycles(std::vector<int> &path, std::vector<bool> &visited, int &minCost);

    // method to print the optimal path
    void printOptimalPath() const;

    // method to reduce the matrix for b&b algorithm
    int reduceMatrix(std::vector<std::vector<int>> &matrix);
    
    // recurisve method to solve ATSP using branch and bound algorithm
    void branchAndBoundRecursive(int currentBound, int currentWeight, int level, std::vector<int> &path, std::vector<bool> &visited, int &bestCost);

    // method to find the minimum element in a row
    int firstMin(int i);

    // method to find the second minimum element in a row
    int secondMin(int i);

    // method to solve ATSP using branch and bound algorithm
    void branchAndBound( std::vector<int> &path, std::vector<bool> &visited, int &minCost);

    // method to solve ATSP using dynamic programming algorithm
    void dynamicProgramming(std::vector<int> &path, std::vector<bool> &visited, int &minCost);

    // method to check if the element is in the subset
    bool notIn(int elem, int subset);

    // method to generate all the possible subsets
    void combinations(int set, int at, int r, int n, std::vector<int> &subsets);

    // method to generate all the possible subsets
    std::vector<int> combinations(int r, int n);

    // method to get the minimum distance
    int getMinDist(int subset, int next, const std::vector<std::vector<int>> &memo, const std::vector<int> &path);

private:
    // store the weights of edges between vertices
    std::vector<std::vector<int>> adjacencyMatrix;

    // number of vertices
    int numVertices;

    // variable to store optimal path
    std::vector<int> optimalPath;

    // number of edges
    int numEdges;
};

#endif