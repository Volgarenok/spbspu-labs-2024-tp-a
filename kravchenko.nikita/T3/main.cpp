#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <limits>
#include <map>
#include <string>
#include <functional>
#include "polygonCommands.hpp"
#include "polygonHandler.hpp"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Required filename argument\n";
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

  std::map< std::string, std::function< void(CommandArguments) > > cmds;
  cmds["AREA"] = Area{};
  {
    using namespace std::placeholders;
    cmds["MIN"] = std::bind(MinMax{}, _1, true);
    cmds["MAX"] = std::bind(MinMax{}, _1, false);
  }
  cmds["COUNT"] = Count{};
  cmds["RMECHO"] = RmEcho{};
  cmds["RIGHTSHAPES"] = RightShapes{};

  std::string command;
  std::cin >> command;
  while (!std::cin.eof())
  {
    try
    {
      cmds.at(command)(CommandArguments{ polygons, std::cin, std::cout });
      std::cout << '\n';
    }
    catch (const std::out_of_range&)
    {
      std::cerr << "<INVALID COMMAND>" << '\n';
    }
    catch (const InvalidCommand& e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    std::cin >> command;
  }

  file.close();
  return 0;
}
