#include <algorithm>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include <vector>
#include "commands.hpp"
#include "geometry.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    return 1;
  }
  std::cout << std::fixed << std::setprecision(1);
  std::ifstream inputFile{ argv[1] };
  std::vector< demidenko::Polygon > polygons;
  using InputIterator = std::istream_iterator< demidenko::Polygon >;
  while (!inputFile.eof())
  {
    if (inputFile.fail())
    {
      inputFile.clear();
      inputFile.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(InputIterator{ inputFile }, InputIterator{}, std::back_inserter(polygons));
  }
  inputFile.clear();
  inputFile.close();
  std::string cmd;
  using namespace std::placeholders;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands{
    { "AREA", std::bind(demidenko::doAreaCommand, _1, _2, std::ref(polygons)) },
    { "MAX", std::bind(demidenko::doMaxCommand, _1, _2, std::ref(polygons)) },
    { "MIN", std::bind(demidenko::doMinCommand, _1, _2, std::ref(polygons)) },
    { "COUNT", std::bind(demidenko::doCountCommand, _1, _2, std::ref(polygons)) },
    { "ECHO", std::bind(demidenko::doEchoCommand, _1, _2, std::ref(polygons)) },
    { "RIGHTSHAPES", std::bind(demidenko::doRightShapesCommand, _2, std::ref(polygons)) },
  };
  std::cin >> cmd;
  while (!std::cin.eof())
  {
    try
    {
      commands.at(cmd)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin >> cmd;
  }
}
