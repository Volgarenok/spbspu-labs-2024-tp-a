#include <functional>
#include <iostream>
#include <limits>
#include <map>

#include "readPolygonsFromFile.hpp"
#include "commands.hpp"

namespace belokurskaya
{
  namespace mapCommands
  {
    using mapCmd = std::map< std::string, std::function< void(std::istream&, std::ostream&) > >;
    mapCmd createMapOfCommands(std::vector< Polygon >& polygons, std::istream&, std::ostream&)
    {
      mapCmd commands;
      using namespace std::placeholders;
      commands["AREA"] = std::bind(cmd::area, std::cref(polygons), _1, _2);
      commands["MAX"] = std::bind(cmd::max, std::cref(polygons), _1, _2);
      commands["MIN"] = std::bind(cmd::min, std::cref(polygons), _1, _2);
      commands["COUNT"] = std::bind(cmd::count, std::cref(polygons), _1, _2);
      return commands;
    }
  }
}

int main(int argc, char** argv)
{
  using namespace belokurskaya;
  if (argc != 2)
  {
    std::cerr << "Incorrect input\n";
    return 1;
  }
  std::vector< Polygon > polygons = readPolygonsFromFile(argv[1]);
  std::string argument;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  commands = mapCommands::createMapOfCommands(polygons, std::cin, std::cout);

  while (std::cin >> argument)
  {
    if (std::cin.eof())
    {
      break;
    }
    try
    {
      commands.at(argument)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (const std::out_of_range&)
    {
      std::cout << "INVALID COMMAND" << '\n';
    }
    catch (const std::invalid_argument&)
    {
      std::cout << "INVALID COMMAND" << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
