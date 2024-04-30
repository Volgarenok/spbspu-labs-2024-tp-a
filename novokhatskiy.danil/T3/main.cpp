#include <iostream>
#include <limits>
#include <vector>
#include <map>
#include <iterator>
#include <fstream>
#include <functional>
#include "polygon.hpp"
#include "commandsSolving.hpp"
#include "StreamGuard.hpp"

namespace novokhatskiy
{
  using mapCmd = std::map < std::string, std::function<void(std::istream&, std::ostream&) > >;
  mapCmd createMapOfCommands(std::vector< Polygon >& polygons, std::istream&, std::ostream&)
  {
    mapCmd commands;
    using namespace std::placeholders;
    commands["AREA"] = std::bind(commandArea, std::cref(polygons), _1, _2);
    commands["MAX"] = std::bind(commandMaxOrMin, std::cref(polygons), _1, _2, true);
    commands["MIN"] = std::bind(commandMaxOrMin, std::cref(polygons), _1, _2, false);
    commands["COUNT"] = std::bind(commandCountEvenOddVertexes, std::cref(polygons), _1, _2);
    commands["PERMS"] = std::bind(commandPerms, std::cref(polygons), _1, _2);
    commands["RECTS"] = std::bind(commandRectangle, std::cref(polygons), _1, _2);
    return commands;
  }
}


int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cerr << "Wrong input argument\n";
    return 1;
  }
  using namespace novokhatskiy;
  std::ifstream input(argv[1]);
  std::vector< Polygon > polygons;
  using inIt = std::istream_iterator< Polygon >;
  while (!input.eof())
  {
    std::copy(inIt{ input }, inIt{}, std::back_inserter(polygons));
    input.clear();
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::map< std::string, std::function<void(std::istream&, std::ostream&) > > commands;
  commands = createMapOfCommands(polygons, std::cin, std::cout);
  std::string argument;
  //std::cin.clear();
  while (std::cin >>argument)
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
    catch (const std::invalid_argument&)
    {
      std::cerr << "<INVALID COMMAND>";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
