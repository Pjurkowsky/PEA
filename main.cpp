#include <iostream>
#include "utils/Menu.h"
#include <string.h>

std::vector<MenuItem> displayOptions = {{"display matrix", {}},
                                        {"display list", {}},
                                        {"exit", {}}};

std::vector<MenuItem> menuItems = {{"read from file", {}},
                                       {"generate graph", {}},
                                       {"display graph", {displayOptions}},
                                       {"run algorithm", {}},
                                       {"exit", {}}};

std::vector<MenuItem> mainMenuItems = {{"Brute Force", {menuItems}},
                                       {"B&B", {menuItems}},
                                       {"DP", {menuItems}},
                                       {"exit", {}}};

std::vector<MenuItem> testMenuItems = {{"test brute force", {}},
                                       {"test B&B", {}},
                                        {"test DP", {}},
                                       {"exit", {}}};

int main(int argc, char const *argv[])
{

    if (argc > 1)
    {
        for (int i = 0; i < argc; i++)
            if (strcmp(argv[i], "-t") == 0)
            {
                Menu menu("Test Menu", testMenuItems);
                menu.run();
            }
    }
    else
    {
        Menu menu("Main Menu", mainMenuItems);
        menu.run();
    }
    return 0;
}
