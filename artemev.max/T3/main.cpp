#include <iostream>
#include <fstream>
#include <iterator>
#include <limits>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>

#include "commands.hpp"
#include "shapes.hpp"
int main(int argc, char* argv[])
{
  using namespace artemev;
  if (argc != 2)
  {
    std::cerr << "Error! Incorrect input argc\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error! Files is empty\n";
    return 1;
  }

  std::vector< Polygon > polygons;
  using input_it_t = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_it_t{ file }, input_it_t{}, std::back_inserter(polygons));
  }

  std::map< std::string, std::function< void(const std::vector < Polygon >&, std::istream&, std::ostream&) > > commands;
  commands["AREA"] = area;
  commands["MAX"] = max;
  commands["MIN"] = min;
  commands["COUNT"] = count;
  commands["PERMS"] = perms;
  commands["RIGHTSHAPES"] = rightshapes;
  std::string command = {};
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(polygons, std::cin, std::cout);
      std::cout << "\n";
    }

    catch(const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
