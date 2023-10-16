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
}

int Graph::calculateCost(std::vector<int> &path) const
{
    int cost = 0;
    for (int i = 0; i < path.size() - 1; i++)
    {
        cost += adjacencyMatrix[path[i]][path[i + 1]];
    }
    cost += adjacencyMatrix[path.back()][path.front()];
    return cost;
}

void Graph::findHamiltonianCycles(std::vector<int> &path, std::vector<bool> &visited, int &minCost) const
{
    // if all vertices are visited and there is an edge from the last vertex to the first vertex
    if (path.size() == numVertices && adjacencyMatrix[path.back()][path.front()] != -1)
    {
        int currentCost = calculateCost(path);
        if (currentCost < minCost)
        {
            minCost = currentCost;
            std::cout << "New minimum cost: " << minCost << '\n';
            std::cout << "Path: ";
            for (int i = 0; i < path.size(); i++)
            {
                std::cout << path[i] << " ";
            }
            std::cout << '\n';
        }
        return;
    }

    // try all possible vertices
    for (int v = 0; v < numVertices; v++)
    {
        if (!visited[v] && adjacencyMatrix[path.back()][v] != -1)
        {
            visited[v] = true;
            path.push_back(v);
            findHamiltonianCycles(path, visited, minCost);
            visited[v] = false;
            path.pop_back();
        }
    }
}
