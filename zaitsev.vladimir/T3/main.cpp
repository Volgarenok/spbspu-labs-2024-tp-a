#include <fstream>
#include <iterator>
#include <map>
#include <functional>
#include <limits>
#include "commands.hpp"

int main(int argc, char** argv)
{
  using namespace zaitsev;
  std::list < Polygon > shapes;
  if (argc < 2)
  {
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    return 1;
  }
  while (!input.eof())
  {
    input.clear();
    std::copy(std::istream_iterator< Polygon >(input), std::istream_iterator< Polygon >(), std::back_inserter(shapes));
  }
  std::map < std::string, std::function< void(std::istream&, std::ostream&, std::list< Polygon >&) > > cmd;
  cmd["AREA"] = area_cmd;
  cmd["MAX"] = max_cmd;
  cmd["MIN"] = min_cmd;
  cmd["COUNT"] = count_cmd;
  cmd["LESSAREA"] = lessarea_cmd;
  cmd["INFRAME"] = inframe_cmd;
  std::string command;
  while (!std::cin.eof())
  {
    try
    {
      std::string command;
      std::cin >> command;
      if (std::cin.eof())
      {
        break;
      }
      auto func = cmd.find(command);
      if (func == cmd.end())
      {
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        std::cin.setstate(std::ios::failbit);
        throw std::invalid_argument("");
      }
      func->second(std::cin, std::cout, shapes);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    std::cin.clear();
  }
  return 0;
}
