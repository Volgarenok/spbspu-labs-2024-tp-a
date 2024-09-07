#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include <streamGuard.hpp>

#include "commands.hpp"
#include "polygon.hpp"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "fatal: missing file name argument\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "fatal: file cannot be opened or it does not exist\n";
    return 1;
  }

  std::vector< zagrivnyy::Polygon > polygons;
  using input_it_t = std::istream_iterator< zagrivnyy::Polygon >;
  while (!file.eof())
  {
    std::copy(input_it_t{file}, input_it_t{}, std::back_inserter(polygons));

    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();

  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(zagrivnyy::area, std::cref(polygons), _1, _2);
    cmds["MAX"] = std::bind(zagrivnyy::minMax, std::cref(polygons), false, _1, _2);
    cmds["MIN"] = std::bind(zagrivnyy::minMax, std::cref(polygons), true, _1, _2);
    cmds["COUNT"] = std::bind(zagrivnyy::count, std::cref(polygons), _1, _2);
    cmds["RMECHO"] = std::bind(zagrivnyy::rmecho, std::ref(polygons), _1, _2);
    cmds["INTERSECTIONS"] = std::bind(zagrivnyy::intersections, std::cref(polygons), _1, _2);
  }

  std::string cmd;
  zagrivnyy::StreamGuard streamGuard(std::cout);
  std::cout << std::fixed << std::setprecision(1);
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
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
