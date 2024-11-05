#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <iterator>
#include <limits>
#include <iomanip>

#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "must be 2 arguments\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "file not open\n";
    return 1;
  }

  using input_it = std::istream_iterator< kovtun::Polygon >;
  std::vector< kovtun::Polygon > polygons;
  while (!file.eof())
  {
    if (!file.fail())
    {
      std::copy(input_it{ file }, input_it{}, std::back_inserter(polygons));
    }
    else
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > commands;

  using namespace std::placeholders;
  commands["AREA"] = std::bind(kovtun::area, std::cref(polygons), _1, _2);
  commands["MAX"] = std::bind(kovtun::max, std::cref(polygons), _1, _2);
  commands["MIN"] = std::bind(kovtun::min, std::cref(polygons), _1, _2);
  commands["COUNT"] = std::bind(kovtun::count, std::cref(polygons), _1, _2);

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cerr << "invalid command\n";
      return 1;
    }
  }

  return 0;
}
