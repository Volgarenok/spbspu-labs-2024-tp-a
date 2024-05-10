#include <iostream>
#include <cstring>
#include <unordered_map>
#include <functional>
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

    std::unordered_map< std::string, std::function< void() > > commands;
    using namespace std::placeholders;
    commands["insert"] = novikov::insert;
    commands["search"] = novikov::search;
    commands["search-keys"] = novikov::searchKeys;
    commands["search-values"] = novikov::searchValues;
    commands["remove"] = novikov::remove;
    commands["remove-keys"] = novikov::removeKeys;
    commands["remove-values"] = novikov::removeValues;
    commands["open"] = novikov::open;
    commands["save"] = novikov::save;
    commands["close"] = novikov::close;
    commands["print"] = novikov::print;
    commands["print-reflected"] = novikov::printReflected;
    commands["size"] = novikov::size;
    commands["merge"] = novikov::merge;
    commands["intersect"] = novikov::intersect;
    commands["filter"] = novikov::filter;
    commands["invert"] = novikov::invert;

    return 0;
}
