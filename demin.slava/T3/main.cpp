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
#include "figures.hpp"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    return 1;
  }

  std::vector< demin::Polygon > polygons;
  using input_it_t = std::istream_iterator< demin::Polygon >;
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
    cmds["AREA"] = std::bind(demin::doarea, std::cref(polygons), _1, _2);
    cmds["MIN"] = std::bind(demin::domin, std::cref(polygons), _1, _2);
    cmds["MAX"] = std::bind(demin::domax, std::cref(polygons), _1, _2);
    cmds["COUNT"] = std::bind(demin::count, std::cref(polygons), _1, _2);
    cmds["LESSAREA"] = std::bind(demin::lessArea, std::cref(polygons), _1, _2);
    cmds["RIGHTSHAPES"] = std::bind(demin::doRightShapes, std::cref(polygons), _2);
    cmds["INFRAME"] = std::bind(demin::doInFrame, std::cref(polygons), _1, _2);
  }

  std::string cmd;
  demin::StreamGuard streamGuard(std::cout);
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
