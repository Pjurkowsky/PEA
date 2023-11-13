#include "Menu.h"
#include "../Graph.h"
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

Menu::Menu(std::string name, std::vector<MenuItem> menuItems, Graph *graph) : menuName(name), menuItems(menuItems), innerLoop(false), graph(graph)
{
}
// runs menu
bool Menu::run()
{
    while (true)
    {
        system(CLEAR);
        int i = 1;
        std::cout << std::setw(menuName.length() * 1.6) << menuName << '\n';

        std::cout << std::string(menuName.length() * 2, '=') << '\n';
        for (auto &item : menuItems)
            std::cout << i++ << ". " << item.str << '\n';

        int choice = getIntInput("Enter your choice: ");
        if (choice > 0 && choice <= menuItems.size())
        {
            MenuItem chosenItem = menuItems[choice - 1];
            if (chosenItem.menuItems.size() > 0)
            {
                innerLoop = true;
                while (innerLoop)
                {
                    Menu menu(chosenItem.str, chosenItem.menuItems, graph);
                    innerLoop = menu.run();
                }
            }
            else
            {
                std::string chosenItemString = chosenItem.str;
                if (chosenItemString == "exit")
                    return false;
                else if (chosenItemString == "read from file")
                {
                    std::ifstream file(getStringInput("Enter filename: "));
                    if (!file)
                    {
                        std::cout << "Unable to open file" << '\n';
                        waitForUser();
                    }
                    else
                    {
                        int numVertices;
                        file >> numVertices;
                        delete graph;
                        graph = new Graph(numVertices);
                        int weight;
                        for (int i = 0; i < numVertices; i++)
                        {
                            for (int j = 0; j < numVertices; j++)
                            {
                                file >> weight;
                                graph->addEdge(i, j, weight);
                            }
                        }
                        std::cout << graph->toString() << '\n';
                        file.close();
                        std::cout << "File read successfully - Graph loaded" << '\n';
                        waitForUser();
                    }
                }
                else if (chosenItemString == "display matrix")
                {
                    std::cout << graph->toString() << '\n';
                    waitForUser();
                }
                else if (chosenItemString == "generate graph")
                {
                    RandomGenerator random;
                    int numVertices = getIntInput("Enter number of vertices: ");
                    int minWeight = getIntInput("Enter minimum weight: ");
                    int maxWeight = getIntInput("Enter maximum weight: ");
                    delete graph;
                    graph = new Graph(numVertices);
                    for (int i = 0; i < numVertices; i++)
                        for (int j = 0; j < numVertices; j++)
                            if (i != j)
                                graph->addEdge(i, j, random.generateRandomInt(minWeight, maxWeight));
                }
                else if (chosenItemString == "run algorithm" && menuName == "Brute Force")
                {
                    Timer timer;
                    std::vector<int> path;
                    std::vector<bool> visited(graph->getNumVertices(), false);
                    int minCost = INT_MAX;
                    path.push_back(getIntInput("Enter starting vertex: "));
                    visited[path.back()] = true;
                    timer.start();
                    graph->findHamiltonianCycles(path, visited, minCost);
                    timer.stop();
                    std::cout << "Minimum cost: " << minCost << '\n';
                    graph->printOptimalPath();
                    std::cout << "Time taken: " << timer.getElapsedTime() << " ns" << '\n';
                    waitForUser();
                }
                else if (chosenItemString == "test brute force")
                {
                    Tester tester(100);
                    std::vector<int> inputs;
                    for (int i = 0; i < 8; i++)
                        inputs.push_back(getIntInput("Enter number of vertices: "));

                    for (auto &input : inputs)
                        tester.testBruteForce(input);

                    tester.printResultsToFile("bruteForceResults.txt");
                    waitForUser();
                }
                else if (chosenItemString == "run algorithm" && menuName == "B&B")
                {
                    Timer timer;
                    std::vector<int> path(graph->getNumVertices(), -1);
                    std::vector<bool> visited(graph->getNumVertices(), false);
                    int minCost = INT_MAX;
                    path[0] = 0;
                    visited[0] = true;
                    timer.start();
                    graph->branchAndBound(path, visited, minCost);
                    timer.stop();
                    std::cout << "Minimum cost: " << minCost << '\n';
                    graph->printOptimalPath();
                    std::cout << "Time taken: " << timer.getElapsedTime() << " ns" << '\n';
                     waitForUser();
                }
                else if (chosenItemString == "run algorithm" && menuName == "DP")
                {
                    Timer timer;
                    std::vector<int> path(graph->getNumVertices(), -1);
                    std::vector<bool> visited(graph->getNumVertices(), false);
                    int minCost = INT_MAX;
                    path[0] = 0;
                    visited[0] = true;
                    timer.start();
                    graph->dynamicProgramming(path, visited, minCost);
                    timer.stop();
                    std::cout << "Minimum cost: " << minCost << '\n';
                    graph->printOptimalPath();
                    std::cout << "Time taken: " << timer.getElapsedTime() << " ns" << '\n';
                     waitForUser();
                }
                else
                {
                    std::cout << "Not implemented yet" << std::endl;
                    waitForUser();
                }
            }
        }
        else
        {
            std::cout << "Invalid choice" << std::endl;
            waitForUser();
        }
    }
}

// waits for user to press enter
void Menu::waitForUser()
{
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    std::cout << "Press any key to continue . . .\n";
    std::cin.get();
}
// gets int input from user
int Menu::getIntInput(std::string message)
{
    int x;
    std::cout << message;
    std::cin >> x;
    return x;
}
// gets float input from user
float Menu::getFloatInput(std::string message)
{
    float x;
    std::cout << message;
    std::cin >> x;
    return x;
}
// gets string input from user
std::string Menu::getStringInput(std::string message)
{
    std::string x;
    std::cout << message;
    std::cin >> x;
    return x;
}
