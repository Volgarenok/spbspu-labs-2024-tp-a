#include <iostream>
#include <cstring>
#include <unordered_map>
#include "commands.hpp"

int main(int argc, const char* argv[])
{
    if (argc > 2)
    {
        std::cerr << "Error: invalid arguments provided!\n";
        return 1;
    }

    if (argc == 2)
    {
        if (!std::strcmp(argv[1], "--help"))
        {
            std::cout << "Eng-Rus dictionary help\n";
            return 0;
        }
        else
        {
            std::cerr << "Error: invalid arguments provided!\n";
            return 1;
        }
    }

    using namespace novikov;
    std::unordered_map< std::string, Dictionary > dictionaries;

    std::unordered_map< std::string, std::string > commands;

    return 0;
}
