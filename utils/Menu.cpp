#include "Menu.h"
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

Menu::Menu(std::string name, std::vector<MenuItem> menuItems) : menuName(name), menuItems(menuItems), innerLoop(false)
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
        {
            std::cout << i << ". " << item.str << '\n';
            i++;
        }

        int choice = getIntInput("Enter your choice: ");
        if (choice > 0 && choice <= menuItems.size())
        {
            MenuItem chosenItem = menuItems[choice - 1];
            if (chosenItem.menuItems.size() > 0)
            {
                innerLoop = true;
                while (innerLoop)
                {
                    Menu menu(chosenItem.str, chosenItem.menuItems);
                    innerLoop = menu.run();
                }
            }
            else
            {
                std::string chosenItemString = chosenItem.str;
                if (chosenItemString == "exit")
                    return false;
                // else if (chosenItemString == "read from file")
                // {
                //     std::ifstream file(getStringInput("Enter filename: "));
                //     if (!file)
                //     {
                //         std::cout << "Unable to open file" << '\n';
                //         waitForUser();
                //     }
                //     else
                //     {
                //         file.close();
                //         std::cout << "File read successfully - Graph loaded" << '\n';
                //         waitForUser();
                //     }
                // }
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