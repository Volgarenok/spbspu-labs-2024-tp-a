#include <iostream>
#include <fstream>
#include <iterator>
#include <limits>
#include <map>
#include <iomanip>
#include <string>
#include <streamGuard.hpp>
#include "polygon.hpp"
#include "commands.hpp"

using namespace zolotukhin;
int main(int argc, const char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "<INVALID ARGUMENTS>\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "<INVALID FILE>\n";
    return 1;
  }
  std::vector< Polygon > polygons;
  using inIterator = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(inIterator{file}, inIterator{}, std::back_inserter(polygons));
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
  using namespace std::placeholders;
    cmds["AREA"] = std::bind(doArea, std::ref(polygons), _1, _2);
    cmds["MAX"] = std::bind(doMax, std::ref(polygons), _1, _2);
    cmds["MIN"] = std::bind(doMin, std::ref(polygons), _1, _2);
    cmds["LESSAREA"] = std::bind(lessarea, std::ref(polygons), _1, _2);
    cmds["COUNT"] = std::bind(doCount, std::ref(polygons), _1, _2);
    cmds["RIGHTSHAPES"] = std::bind(doRightShapes, std::ref(polygons), _2);
  }

  StreamGuard guard(std::cout);
  std::string command = "";
  std::cout << std::fixed << std::setprecision(1);
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(std::cin, std::cout);
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
