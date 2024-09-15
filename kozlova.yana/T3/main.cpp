#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <iterator>
#include <map>
#include <functional>
#include <numeric>

#include "Polygon.hpp"
#include "Commands.hpp"

int main()
{
  using namespace kozlova;
  std::vector<Polygon> polygons;

  std::cout << "Enter polygons:\n";

  while (true)
  {
    Polygon p;
    if (std::cin >> p)
    {
      polygons.push_back(p);
    }
    else if (std::cin.eof() || std::cin.fail())
    {
      std::cin.clear();
      std::string temp;
      std::cin >> temp;
      if (temp == "END")
      {
        break;
      }
      std::cout << "Error\n";
    }
  }

  using namespace std::placeholders;
  std::map<std::string, std::function<void(std::istream&, std::ostream&)>> commands;
  {
    commands["AREA"] = std::bind(generalArea, polygons, _1, _2);
    commands["MAX"] = std::bind(generalMax, polygons, _1, _2);
    commands["MIN"] = std::bind(generalMin, polygons, _1, _2);
  }

  std::string command;
  while (std::cout << "Command: ", std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (const std::exception& e)
    {
      std::cout << " <INVALID COMMAND> \n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  return 0;
  }
