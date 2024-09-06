#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include "commands.hpp"
#include "polygon.hpp"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    return 1;
  }
  std::ifstream inputf(argv[1]);
  if (!inputf)
  {
    return 1;
  }
  using namespace lebedev;
  std::vector< Polygon > polygons;
  while (!inputf.eof())
  {
    std::copy(
      std::istream_iterator< Polygon >(inputf),
      std::istream_iterator< Polygon >(),
      std::back_inserter(polygons)
    );
    if (inputf.fail())
    {
      inputf.clear();
      inputf.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function < void(const std::vector< Polygon > &, std::istream & input, std::ostream & output) > > cmd_map;
  cmd_map["AREA"] = getAreaCmd;
  cmd_map["MAX"] = getMaxCmd;
  //cmd_map["MIN"] = getMinCmd;
  //cmd_map["COUNT"] = getCountCmd;

  std::string curr_command;
  while (std::cin >> curr_command)
  {
    if (std::cin.eof())
    {
      break;
    }
    try
    {
      cmd_map.at(curr_command)(polygons, std::cin, std::cout);
      std::cout << "\n";
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
