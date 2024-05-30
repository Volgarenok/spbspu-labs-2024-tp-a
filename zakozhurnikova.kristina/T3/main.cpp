#include <algorithm>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include "commands.hpp"
#include "polygon.hpp"

int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  if (argc < 2)
  {
    std::cerr << "Incorrect number of arguments\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Couldn't open file\n";
    return 2;
  }

  std::vector< Polygon > polygons;

  using input_it_t = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(input_it_t{ file }, input_it_t{}, std::back_inserter(polygons));
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  using namespace std::placeholders;
  commands["AREA"] = std::bind(doAreaCommand, std::cref(polygons), _1, _2);
  commands["MAX"] = std::bind(doMaxCommand, std::cref(polygons), _1, _2);
  commands["MIN"] = std::bind(doMinCommand, std::cref(polygons), _1, _2);
  commands["COUNT"] = std::bind(doCountCommand, std::cref(polygons), _1, _2);
  commands["INTERSECTIONS"] = std::bind(doIntersectionsCommand, std::cref(polygons), _1, _2);
  commands["RMECHO"] = std::bind(doRmechoCommand, std::ref(polygons), _1, _2);

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
