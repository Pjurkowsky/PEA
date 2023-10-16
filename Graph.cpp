#include "Graph.h"
#include <algorithm>
#include <limits>

Graph::Graph(int numVertices)
{
    this->numVertices = numVertices;
    this->numEdges = 0;
    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, -1));
}

void Graph::addEdge(int u, int v, int weight)
{
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices)
    {
        adjacencyMatrix[u][v] = weight;
        numEdges++;
    }
}

int Graph::getEdgeWeight(int u, int v) const
{
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices)
        return adjacencyMatrix[u][v];
    else
        return -1;
}

int Graph::getNumVertices() const
{
    return numVertices;
}

int Graph::getNumEdges() const
{
    return numEdges;
}

std::string Graph::toString() const
{
    std::string output = "";
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            output += std::to_string(adjacencyMatrix[i][j]) + " ";
        }
        output += "\n";
    }
    return output;
}

std::vector<std::vector<int>> Graph::getAdjecencyMatrix() const
{
    return adjacencyMatrix;
}

int Graph::bruteForceTSP(int startVertex)
{
    std::vector<int> vertices;
    for (int i = 0; i < numVertices; i++)
    {
        if (i != startVertex)
            vertices.push_back(i);
    }

    int minPath = std::numeric_limits<int>::max();
    do
    {
        int currentPathWeight = 0;
        int k = startVertex;
        for (int i = 0; i < vertices.size(); i++)
        {
            currentPathWeight += adjacencyMatrix[k][vertices[i]];
            std::cout << k << " -> " << vertices[i] << " weight: " << adjacencyMatrix[k][vertices[i]] << std::endl;
            k = vertices[i];
        }
        currentPathWeight += adjacencyMatrix[k][startVertex];
        std::cout << k << " -> " << startVertex << " weight: " << adjacencyMatrix[k][startVertex] << std::endl;
        minPath = std::min(minPath, currentPathWeight);
        std::cout << "minPath: " << currentPathWeight << std::endl;
    } while (std::next_permutation(vertices.begin(), vertices.end()));

    return minPath;
}

// pierdol sie