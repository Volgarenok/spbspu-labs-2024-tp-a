#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <string>
#include <functional>
#include <limits>
#include "commands.h"

int main(int arg, char* argv[])
{
  using namespace kazennov;
  std::vector< Polygon > polygons;
  if (arg != 2)
  {
    return 1;
  }
  std::ifstream infile(argv[1]);
  if (!infile.is_open())
  {
    std::cerr << "isn't open\n";
    return 2;
  }
  using input_it_t = std::istream_iterator< Polygon >;
  while (!infile.eof())
  {
    std::copy(input_it_t{infile}, input_it_t{}, std::back_inserter(polygons));
    infile.clear();
    infile.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(getArea, _1, _2, polygons);
    cmds["MAX"] = std::bind(getMax, _1, _2, polygons);
    cmds["MIN"] = std::bind(getMin, _1, _2, polygons);
    cmds["COUNT"] = std::bind(getCount, _1, _2, polygons);
    cmds["PERMS"] = std::bind(getPerms, _1, _2, polygons);
    cmds["INTERSECTIONS"] = std::bind(getIntersections, _1, _2, polygons);
    cmds["INFRAME"] = std::bind(getInframe, _1, _2, polygons);
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
