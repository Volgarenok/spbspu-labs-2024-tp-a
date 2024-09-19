#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <limits>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include "Geometry.h"
#include "Commands.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Error: Invalid argument count\n";
        return EXIT_FAILURE;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cout << "Error: Unable to open file\n";
        return EXIT_FAILURE;
    }

    std::vector<serter::Polygon> data;
    using iter = std::istream_iterator<serter::Polygon>;

    try {
        std::copy(iter(input), iter(), std::back_inserter(data));
    } catch (const std::exception& e) {
        std::cerr << "Error reading polygons: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::map<std::string, std::function<void(std::istream&, std::ostream&)>> commands;
    using namespace std::placeholders;
    commands.insert({"AREA", std::bind(serter::area, std::cref(data), _1, _2)});
    commands.insert({"MIN", std::bind(serter::min, std::cref(data), _1, _2)});
    commands.insert({"MAX", std::bind(serter::max, std::cref(data), _1, _2)});
    commands.insert({"COUNT", std::bind(serter::count, std::cref(data), _1, _2)});
    commands.insert({"ECHO", std::bind(serter::echo, std::ref(data), _1, _2)});
    commands.insert({"RMECHO", std::bind(serter::rmEcho, std::ref(data), _1, _2)});
    commands.insert({"LESSAREA", std::bind(serter::lessArea, std::cref(data), _1, _2)});

    std::string command;
    while (std::cin >> command)
    {
        try
        {
            commands.at(command)(std::cin, std::cout);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "<INVALID COMMAND: " << command << ">\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            break;
        }
    }

    return 0;
}

