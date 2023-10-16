#include "Graph.h"
#include <algorithm>
#include <limits>

//graph constructor
Graph::Graph(int numVertices)
{
    this->numVertices = numVertices;
    this->numEdges = 0;
    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, -1));
    optimalPath.reserve(numVertices);
}

//adding edges
void Graph::addEdge(int u, int v, int weight)
{
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices)
    {
        adjacencyMatrix[u][v] = weight;
        numEdges++;
    }
}

//getting edge's weight
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

//converting graph into string version
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

//calculating cost of the tour
int Graph::calculateCost(std::vector<int> &path)
{
    int cost = 0;

    //calculating the cost of the path from one vertex to another
    for (int i = 0; i < path.size() - 1; i++)
    {
        cost += adjacencyMatrix[path[i]][path[i + 1]];
    }
    //adding the cost of going from the last vertex to the first one
    cost += adjacencyMatrix[path.back()][path.front()];
    return cost;
}


void Graph::findHamiltonianCycles(std::vector<int> &path, std::vector<bool> &visited, int &minCost)
{
    //recursion ends if 2 requirements are fulfilled:
    //first: the path contains all the vertices
    //second: there's a path from the last vertex to the first one
    if (path.size() == numVertices && adjacencyMatrix[path.back()][path.front()] != -1)
    {
        //calculating the cost for the current path
        int currentCost = calculateCost(path);

        //if the current path has smaller cost then we update the optimal path to the current one
        if (currentCost < minCost)
        {
            minCost = currentCost;
            // std::cout << "New minimum cost: " << minCost << '\n';
            // std::cout << "Path: ";
            optimalPath.clear();
            for (int i = 0; i < path.size(); i++)
            {
                // std::cout << path[i] << " ";
                optimalPath.push_back(path[i]);
            }
            // std::cout << '\n';
        }
        return;
    }

    //iteration through all the vertices
    for (int v = 0; v < numVertices; v++)
    {
        //if the vertex has not been visited yet and there's path from current vertex to the next one we go there
        if (!visited[v] && adjacencyMatrix[path.back()][v] != -1)
        {
            //we flag new vertex as visited and add it to the path
            visited[v] = true;
            path.push_back(v);
            //finding more cycles by using recursion
            findHamiltonianCycles(path, visited, minCost);
            //resetting the current vertex
            visited[v] = false;
            path.pop_back();
        }
    }
}

//printing final result
void Graph::printOptimalPath() const
{
    std::cout << "Optimal path: ";
    for (int i = 0; i < optimalPath.size(); i++)
    {
        std::cout << optimalPath[i] << " ";
    }
    std::cout << '\n';
}
