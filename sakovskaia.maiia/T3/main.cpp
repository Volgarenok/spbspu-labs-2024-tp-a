#include "polygon.hpp"
#include "commands.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  using namespace sakovskaia;
  if (argc < 2)
  {
    std::cout << "Not enough arguments\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cout << "Can't open file\n";
    return 1;
  }
  std::vector< Polygon > polygons;
  Polygon polygon;
  while (input >> polygon)
  {
    polygons.push_back(polygon);
  }
  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(getArea, _1, _2, polygons);
    cmds["MAX"] = std::bind(getMaxMin, _1, _2, polygons);
    cmds["MIN"] = std::bind(getMaxMin, _1, _2, polygons);
    cmds["COUNT"] = std::bind(getCount, _1, _2, polygons);
    cmds["MAXSEQ"] = std::bind(getMaxSeq, _1, _2, polygons);
    cmds["RMECHO"] = std::bind(getRmecho, _1, _2, polygons);
    cmds["RECTS"] = std::bind(getRects, _2, polygons);
  }
  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
      std::cout << "\n";
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
