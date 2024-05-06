#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include <vector>
#include "polygonCommands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid filename\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "File cannot be opened\n";
    return 2;
  }
  using namespace kravchenko;

  std::vector< Polygon > polygons;
  using inputIt = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(inputIt{ file }, inputIt{}, std::back_inserter(polygons));
    file.clear();
    file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  file.close();

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(cmdArea, std::cref(polygons), _1, _2);
    cmds["MIN"] = std::bind(cmdMinMax< true >, std::cref(polygons), _1, _2);
    cmds["MAX"] = std::bind(cmdMinMax< false >, std::cref(polygons), _1, _2);
    cmds["COUNT"] = std::bind(cmdCount, std::cref(polygons), _1, _2);
    cmds["RMECHO"] = std::bind(cmdRmEcho, std::ref(polygons), _1, _2);
    cmds["RIGHTSHAPES"] = std::bind(cmdRightShapes, std::cref(polygons), _2);
  }

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  return 0;
}
