#include <vector>
#include <string>
#include <iostream>
#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
    // Constructor that takes the number of vertices in the graph
    Graph(int numVertices);

    // Method to add an edge between two vertices with a given weight
    void addEdge(int u, int v, int weight);

    // Method to get the weight of an edge between two vertices
    int getEdgeWeight(int u, int v) const;

    // Method to get the number of vertices in the graph
    int getNumVertices() const;

    // Method to get the number of edges in the graph
    int getNumEdges() const;

    std::string toString() const;

    std::vector<std::vector<int>> getAdjecencyMatrix() const;

    //  Method to solve ATSP problem using brute force
    int bruteForceTSP(int startVertex);

private:
    // 2D vector to store the weights of edges between vertices
    std::vector<std::vector<int>> adjacencyMatrix;

    // Number of vertices in the graph
    int numVertices;

    // Number of edges in the graph
    int numEdges;
};

#endif