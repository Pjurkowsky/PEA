#include <vector>
#include <string>
#include <iostream>
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