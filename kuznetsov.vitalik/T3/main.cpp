#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <limits>
#include "commands.hpp"

int main()
{
  using namespace kuznetsov;
  Polygon polygon1;
  Polygon polygon2;
  Polygon polygon3;
  std::cin >> polygon1;
  std::cin >> polygon2;
  std::cin >> polygon3;

  std::vector< Polygon > polygon{ polygon1, polygon2, polygon3 };

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(getArea, polygon, _1, _2);
    cmds["MAX"] = std::bind(getMax, polygon, _1, _2);
    cmds["MIN"] = std::bind(getMin, polygon, _1, _2);
    cmds["COUNT"];
    cmds["INFRAME"];
    cmds["SAME"];
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}

