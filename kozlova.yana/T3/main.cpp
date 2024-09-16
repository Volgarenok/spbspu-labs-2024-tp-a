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

int main(int argc, char* argv[])
{
  using namespace kozlova;
  std::vector< Polygon > polygons;
  if (argc < 2)
  {
    std::cout << "There are not enough vertices\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cout << "The file does not open\n";
    return 2;
  }

  while (!file.eof())
  {
    std::copy(std::istream_iterator< Polygon >{file}, std::istream_iterator< Polygon >{}, std::back_inserter(polygons));
    file.clear();
    file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  using namespace std::placeholders;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  {
    commands["AREA"] = std::bind(generalArea, polygons, _1, _2);
    commands["MAX"] = std::bind(generalMax, polygons, _1, _2);
    commands["MIN"] = std::bind(generalMin, polygons, _1, _2);
    commands["COUNT"] = std::bind(generalCount, polygons, _1, _2);
    commands["PERMS"] = std::bind(generalPerms, polygons, _1, _2);
    commands["RMECHO"] = std::bind(generalRmEcho, polygons, _1, _2);
    commands["RIGHTSHAPES"] = std::bind(generalRightShapes, polygons, _2);
  }

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what() << '\n';
    }
     catch (...)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  return 0;
  }
