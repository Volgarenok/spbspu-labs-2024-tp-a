#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include <limits>
#include <iterator>
#include <algorithm>
#include <functional>
#include <streamGuard.hpp>
#include "figures.hpp"
#include "commands.hpp"

using namespace kozlov;
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
  using namespace std::placeholders;
  cmds["AREA"] = std::bind(doCmdArea, std::ref(polygons), _1, _2);
  cmds["MAX"] = std::bind(doCmdMax, std::ref(polygons), _1, _2);
  cmds["MIN"] = std::bind(doCmdMin, std::ref(polygons), _1, _2);
  cmds["COUNT"] = std::bind(doCmdCount, std::ref(polygons), _1, _2);
  cmds["ECHO"] = std::bind(doCmdEcho, std::ref(polygons), _1, _2);
  cmds["INFRAME"] = std::bind(doCmdInframe, std::ref(polygons), _1, _2);

  std::string command = "";
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
