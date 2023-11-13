#include "Graph.h"
#include <algorithm>
#include <limits>

// graph constructor
Graph::Graph(int numVertices)
{
    this->numVertices = numVertices;
    this->numEdges = 0;
    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, -1));
    optimalPath.reserve(numVertices);
}

// graph destructor
Graph::~Graph()
{
}

// adding edges
void Graph::addEdge(int u, int v, int weight)
{
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices)
    {
        adjacencyMatrix[u][v] = weight;
        numEdges++;
    }
}

// getting edge's weight
int Graph::getEdgeWeight(int u, int v) const
{
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices)
        return adjacencyMatrix[u][v];
    else
        return -1;
}
// returns number of vertices
int Graph::getNumVertices() const
{
    return numVertices;
}

// returns number of edges
int Graph::getNumEdges() const
{
    return numEdges;
}

// converting graph into string version
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

// returns adjacency matrix
std::vector<std::vector<int>> Graph::getAdjecencyMatrix() const
{
    return adjacencyMatrix;
}

// calculating cost of the tour
int Graph::calculateCost(std::vector<int> &path)
{
    int cost = 0;

    // calculating the cost of the path from one vertex to another
    for (int i = 0; i < path.size() - 1; i++)
        cost += adjacencyMatrix[path[i]][path[i + 1]];

    // adding the cost of going from the last vertex to the first one
    cost += adjacencyMatrix[path.back()][path.front()];
    return cost;
}

// finding all the hamiltonian cycles
void Graph::findHamiltonianCycles(std::vector<int> &path, std::vector<bool> &visited, int &minCost)
{
    // recursion ends if 2 requirements are fulfilled:
    // first: the path contains all the vertices
    // second: there's a path from the last vertex to the first one
    if (path.size() == numVertices && adjacencyMatrix[path.back()][path.front()] != -1)
    {
        // calculating the cost for the current path
        int currentCost = calculateCost(path);

        // if the current path has smaller cost then we update the optimal path to the current one
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

    // iteration through all the vertices
    for (int v = 0; v < numVertices; v++)
    {
        // if the vertex has not been visited yet and there's path from current vertex to the next one go there
        if (!visited[v] && adjacencyMatrix[path.back()][v] != -1)
        {
            // flag new vertex as visited and add it to the path
            visited[v] = true;
            path.push_back(v);
            // find more cycles by recursion
            findHamiltonianCycles(path, visited, minCost);
            // reset the current vertex
            visited[v] = false;
            path.pop_back();
        }
    }
}

// printing final result
void Graph::printOptimalPath() const
{
    std::cout << "Optimal path: ";
    for (int i = 0; i < optimalPath.size(); i++)
    {
        if (optimalPath[i] == -1) continue;
        std::cout << optimalPath[i] << " ";
    }
    std::cout << '\n';
}

int Graph::reduceMatrix(std::vector<std::vector<int>> &matrix)
{
    int cost = 0;
    // reduce rows
    for (int i = 0; i < matrix.size(); i++)
    {
        int min = INT_MAX;
        for (int j = 0; j < matrix[i].size(); j++)
            if (matrix[i][j] != -1 && matrix[i][j] < min)
                min = matrix[i][j];
        
        if (min != INT_MAX)
        {
            for (int j = 0; j < matrix[i].size(); j++)
                if (matrix[i][j] != -1)
                    matrix[i][j] -= min;
            
            cost += min;
        }
    }
    // reduce columns
    for (int i = 0; i < matrix.size(); i++)
    {
        int min = INT_MAX;
        for (int j = 0; j < matrix[i].size(); j++)
            if (matrix[j][i] != -1 && matrix[j][i] < min)
                min = matrix[j][i];

        if (min != INT_MAX)
        {
            for (int j = 0; j < matrix[i].size(); j++)
                if (matrix[j][i] != -1)
                    matrix[j][i] -= min;

            cost += min;
        }
    }
    return cost;
}


// recurisve method to solve ATSP using branch and bound algorithm
void Graph::branchAndBoundRecursive(int currentBound, int currentWeight, int level, std::vector<int> &path, std::vector<bool> &visited, int &bestCost)
{
    // base case is when we have visited all the vertices
    if (level == numVertices) {
            if (adjacencyMatrix[path[level - 1]][path[0]] != 0) {
                int currRes = currentWeight + adjacencyMatrix[path[level - 1]][path[0]];
                if (currRes < bestCost) {
                    optimalPath.clear();
                    for (int i = 0; i < path.size(); i++)
                        optimalPath.push_back(path[i]);
                    bestCost = currRes;
                }
            }
            return;
        }
        // iterate through all the vertices
        for (int i = 0; i < numVertices; i++) {
            if (adjacencyMatrix[path[level - 1]][i] != 0 && !visited[i]) {
                int temp = currentBound;
                currentWeight += adjacencyMatrix[path[level - 1]][i];
                // different calculation of currentBound for level 2 from the other levels
                if (level == 1)
                    currentBound -= ((firstMin(path[level - 1]) + firstMin(i)) / 2);
                else
                    currentBound -= ((secondMin(path[level - 1]) + firstMin(i)) / 2);
                // currentBound + currentWeight is the actual lower bound for the node that we have arrived on
                if (currentBound + currentWeight < bestCost) {
                    path[level] = i;
                    visited[i] = true;
                    branchAndBoundRecursive(currentBound, currentWeight, level + 1, path, visited, bestCost);
                }

                currentWeight -= adjacencyMatrix[path[level - 1]][i];
                currentBound = temp;

                std::fill(visited.begin(), visited.end(), false);

                for (int j = 0; j <= level - 1; j++) {
                    visited[path[j]] = true;
                }
            }
        }
  
}

// function to find the first minimum edge cost
int Graph::firstMin(int i)
{
    int min = INT_MAX;
    for (int k = 0; k < numVertices; k++)
        if (adjacencyMatrix[i][k] < min && i != k)
            min = adjacencyMatrix[i][k];
    return min;
}
// function to find the second minimum edge cost
int Graph::secondMin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < numVertices; j++) {
        if (i == j)
            continue;

        if (adjacencyMatrix[i][j] <= first) {
            second = first;
            first = adjacencyMatrix[i][j];
        }
        else if (adjacencyMatrix[i][j] <= second && adjacencyMatrix[i][j] != first)
            second = adjacencyMatrix[i][j];
    }
    return second;
}

// method to solve ATSP using branch and bound algorithm
void Graph::branchAndBound(std::vector<int> &path, std::vector<bool> &visited, int &minCost)
{
    int currentBound = 0;
    for (int i = 0; i < numVertices; i++) 
    currentBound += (firstMin(i) + secondMin(i));

    currentBound = (currentBound == 1) ? (currentBound / 2) + 1 : currentBound / 2;

    branchAndBoundRecursive(currentBound, 0, 1, path, visited, minCost);
}
// method to solve ATSP using dynamic programming algorithm
void Graph::dynamicProgramming(std::vector<int> &path, std::vector<bool> &visited, int &minCost)
{   
    int endState = (1 << numVertices) - 1; 

    std::vector<std::vector<int>> memo(numVertices, std::vector<int>(1 << numVertices, 0)); // 2D array to store the results of subproblems
        // base case is when there's only one vertex in the path
      for (int end = 0; end < numVertices; end++) {
            if (end == path[0]) continue;
            memo[end][(1 << path[0]) | (1 << end)] = adjacencyMatrix[path[0]][end];
        }
        // iterate through all the possible subsets
         for (int i = 3; i <= numVertices; i++) {
            for (int subset : combinations(i, numVertices)) {
                if (notIn(path[0], subset)) continue;
                for (int next = 0; next < numVertices; next++) {
                    if (next == path[0] || notIn(next, subset)) continue;
                    int minDist = getMinDist(subset, next, memo, path);
                    memo[next][subset] = minDist;
                }
            }
        }
         // iterate through all the vertices
          for (int i = 0; i < numVertices; i++) {
            if (i == path[0]) continue;
            int tourCost = memo[i][endState] + adjacencyMatrix[i][path[0]];
            if (tourCost < minCost) minCost = tourCost;
        }
        // reconstructing the path
        int lastIndex = path[0];
        int state = endState;
        
        for (int i = 1; i < numVertices; i++) {
            int index = -1;
            for (int j = 0; j < numVertices; j++) {
                if (j == path[0] || notIn(j, state)) continue;
                if (index == -1 || memo[j][state] + adjacencyMatrix[j][lastIndex] < memo[index][state] + adjacencyMatrix[index][lastIndex]) {
                    index = j;
                }
            }
            path.push_back(index);
            state ^= (1 << index);
            lastIndex = index;
        }

        path.push_back(path[0]);
        std::reverse(path.begin(), path.end());
        optimalPath.clear();
        for (int i = 0; i < path.size() - 1; i++)
            optimalPath.push_back(path[i]);
}
// method to check if the element is in the subset
bool Graph::notIn(int elem, int subset) {
        return ((1 << elem) & subset) == 0;
    }

// method to generate all the possible subsets
void Graph::combinations(int set, int at, int r, int n, std::vector<int>& subsets) {
        int elementsLeftToPick = n - at;
        if (elementsLeftToPick < r) return;
        if (r == 0) {
            subsets.push_back(set);
        } else {
            for (int i = at; i < n; i++) {
                set |= 1 << i;
                combinations(set, i + 1, r - 1, n, subsets);
                set &= ~(1 << i);
            }
        }
    }

// method to generate all the possible subsets
std::vector<int> Graph::combinations(int r, int n) {
        std::vector<int> subsets;
        combinations(0, 0, r, n, subsets);
        return subsets;
    }

// method to get the minimum distance
int Graph::getMinDist(int subset, int next, const std::vector<std::vector<int>>& memo, const std::vector<int>& path) {
        int subsetWithoutNext = subset ^ (1 << next);
        int minDist = INT_MAX;

        for (int end = 0; end < numVertices; end++) {
            if (end == path[0] || end == next || notIn(end, subset)) continue;
            int newDistance = memo[end][subsetWithoutNext] + adjacencyMatrix[end][next];
            if (newDistance < minDist) minDist = newDistance;
        }
        return minDist;
    }