#include "Tester.h"

Tester::Tester(int numOfTests) : numOfTests(numOfTests)
{
}

//  method for generating graph
void Tester::generateGraph(Graph *graph)
{
    RandomGenerator random;
    int minWeight = 1;
    int maxWeight = random.generateRandomInt(10, 100);
    for (int i = 0; i < graph->getNumVertices(); i++)
        for (int j = 0; j < graph->getNumVertices(); j++)
            if (i != j)
                graph->addEdge(i, j, random.generateRandomInt(minWeight, maxWeight));
}

// method for printing results to file
void Tester::printResultsToFile(std::string fileName)
{
    std::ofstream file(fileName);
    if (!file)
        std::cout << "Unable to open file" << '\n';
    for (int i = 0; i < numbersOfVertices.size(); i++)
        file << numbersOfVertices[i] << " " << times[i] << '\n';
    file.close();
}

// method for testing algorithm
void Tester::testBruteForce(int numVertices)
{
    Graph *graph = new Graph(numVertices);
    long time = 0;
    generateGraph(graph);
    std::cout << "Testing Brute Force Algorithm with " << numVertices << " vertices" << '\n';
    for (int i = 0; i < numOfTests; i++)
    {
        Timer timer;
        std::vector<int> path;
        std::vector<bool> visited(graph->getNumVertices(), false);
        int minCost = INT_MAX;
        path.push_back(0);
        visited[0] = true;
        timer.start();
        graph->findHamiltonianCycles(path, visited, minCost);
        timer.stop();
        time += timer.getElapsedTime();
    }
    times.push_back(time / numOfTests);
    numbersOfVertices.push_back(numVertices);
}
