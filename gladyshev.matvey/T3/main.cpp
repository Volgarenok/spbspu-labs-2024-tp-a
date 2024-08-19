#include <limits>
#include <iterator>
#include <map>
#include <iostream>
#include <fstream>
#include <functional>

#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace gladyshev;
  std::ifstream file;
  if (argc == 2)
  {
    file.open(argv[1]);
  }
  else
  {
    std::cerr << "Bad file input\n";
    return 1;
  }
  std::vector< Polygon > polygons;
  while (!file.eof())
  {
    if (!file)
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(
      std::istream_iterator< Polygon >{file},
      std::istream_iterator< Polygon >{},
      std::back_inserter(polygons)
    );
  }
  using namespace std::placeholders;
  std::map < std::string, std::function < void(std::istream&, std::ostream&) > > cmds;
  cmds["AREA"] = std::bind(findAreas, _1, _2, std::cref(polygons));
  cmds["MAX"] = std::bind(findMax, _1, _2, std::cref(polygons));
  cmds["MIN"] = std::bind(findMin, _1, _2, std::cref(polygons));
  cmds["COUNT"] = std::bind(processCount, _1, _2, std::cref(polygons));
  cmds["LESSAREA"] = std::bind(findLessArea, _1, _2, std::cref(polygons));
  cmds["ECHO"] = std::bind(processEcho, _1, _2, std::ref(polygons));
  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
