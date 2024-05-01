#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "commands.hpp"
#include "polygon.hpp"

// [RMECHO]	[INTERSECTIONS]
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
    cmds["AREA"] = std::bind(zagrivnyy::area, polygons, _1, _2);
    cmds["MAX"] = std::bind(zagrivnyy::minMax, polygons, false, _1, _2);
    cmds["MIN"] = std::bind(zagrivnyy::minMax, polygons, true, _1, _2);
    cmds["COUNT"] = std::bind(zagrivnyy::count, polygons, _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range &)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
