#include <iostream>
#include <fstream>
#include <limits>
#include <iterator>
#include <functional>
#include <map>

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
  std::map < std::string, std::function < void(std::istream&, const std::vector< Polygon >&) > > cmds;
  cmds["AREA"] = findAreas;
  cmds["MAX"] = findMax;
  cmds["MIN"] = findMin;
  cmds["COUNT"] = processCount;
  cmds["LESSAREA"] = findLessArea;
  cmds["ECHO"] = processEcho;
  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(std::cin, polygons);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  for (const auto& area: polygons)
  {
    std::cout << findArea(area) << "\n";
  }
}
