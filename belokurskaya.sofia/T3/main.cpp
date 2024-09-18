#include <functional>
#include <iostream>
#include <limits>
#include <map>

#include "readPolygonsFromFile.hpp"
#include "commands.hpp"

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
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(cmd::area, std::cref(polygons), _1, _2);
    commands["MAX"] = std::bind(cmd::max, std::cref(polygons), _1, _2);
    commands["MIN"] = std::bind(cmd::min, std::cref(polygons), _1, _2);
    commands["COUNT"] = std::bind(cmd::count, std::cref(polygons), _1, _2);
    commands["RMECHO"] = std::bind(cmd::rmecho, std::ref(polygons), _1, _2);
    commands["RECTS"] = std::bind(cmd::rects, std::cref(polygons), _2);
  }

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

    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
      cleanIStream(std::cin);
    }
  }
}
