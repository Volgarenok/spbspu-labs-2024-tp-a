#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <nl_types.h>
#include <stdexcept>
#include <vector>
#include <functional>

#include <formatGuard.hpp>

#include "commands.hpp"
#include "polygon.hpp"

int main(int argc, char **argv)
{
  using namespace arakelyan;
  //maxseq rightshapes

  if (argc < 2)
  {
    std::cerr << "<NO SOURCE FILE WITH FIGURES!>\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "<CANNOT OPEN SOURCE FILE!>\n";
    return 1;
  }

  std::vector< Polygon > polygons;

  using inIt = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(inIt{file}, inIt{}, std::back_inserter(polygons));
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  file.close();

  std::map< std::string, std::function< void(std::istream&, std::ostream&, const std::vector< Polygon >&) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(doArea, _1, _2, _3);
    commands["MAX"] = std::bind(findMax, _1, _2, _3);
    commands["MIN"] = std::bind(findMin, _1, _2, _3);
    commands["COUNT"] = std::bind(count, _1, _2, _3);
    commands["MAXSEQ"] = std::bind(maxSeq, _1, _2, _3);
  //   // commands["RIGHTSHAPES"] = std::bind(rightShapes, _1, _2, _3);
  }

  std::cout << std::fixed << std::setprecision(1);

  std::string cmdName = "";
  while (std::cin >> cmdName)
  {
    FormatGuard fmtGuard(std::cout);
    if (std::cin.eof())
    {
      break;
    }
    try
    {
      commands.at(cmdName)(std::cin, std::cout, polygons);
      std::cout << "\n";
    }
    catch (...)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
