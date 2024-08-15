#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include <vector>
#include <map>
#include <iterator>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  if (argc != 2)
  {
    std::cerr << "Wrong CLA number\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  std::vector< Polygon > context;
  while (!file.eof())
  {
    std::copy(
      std::istream_iterator< Polygon >(file),
      std::istream_iterator< Polygon >(),
      std::back_inserter(context)
    );
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();
  using func = std::function< void(std::istream &, std::ostream &) >;
  std::map< std::string, func > command;
  {
    using namespace std::placeholders;
    command["AREA"] = std::bind(doAreaCommand, context, _1, _2);
    command["MAX"] = std::bind(doMaxCommand, context, _1, _2);
    command["MIN"] = std::bind(doMinCommand, context, _1, _2);
    command["COUNT"] = std::bind(doCountCommand, context, _1, _2);
    command["INFRAME"] = std::bind(doInFrameCommand, context, _1, _2);
    command["RIGHTSHAPES"] = std::bind(doRightShapesCommand, context, _1, _2);
  }
  std::string command_name;
  std::cin >> command_name;
  while (!std::cin.eof())
  {
    try
    {
      command.at(command_name)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cin >> command_name;
  }
  return 0;
}
