#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "Shapes.hpp"
#include "Commands.hpp"

using namespace kuzmina;

int main()
{
  std::vector< Polygon > polygons;

  Polygon p1, p2;
  std::cin >> p1 >> p2;

  polygons.push_back(p1);
  polygons.push_back(p2);

  std::map< std::string, std::function< void (std::istream&, std::ostream&, const std::vector< Polygon >&) > > commands;
  commands["AREA"] = area;
  commands["MAX"] = max;
  commands["MIN"] = min;
  commands["COUNT"] = count;
  //commands["SAME"] = same;
  //commands["RIGHTSHAPES"] = rightshapes;

  std::string command = "";
  while (std::cin >> command)
  {
    commands.at(command)(std::cin, std::cout, polygons);
    std::cout << '\n';
  }

  return 0;
}
