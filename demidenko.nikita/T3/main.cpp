#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include "geometry.hpp"

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    return -1;
  }
  std::ifstream inputFile{ argv[2] };
  std::vector< demidenko::Polygon > polygons;
  if (demidenko::readPolygons(inputFile, polygons).fail())
  {
    return -1;
  }
  std::string cmd;
  using Command = void (*)(std::istream&, std::ostream&);
  std::map< std::string, Command > commands{};
}
