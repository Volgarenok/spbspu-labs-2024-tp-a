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
    if (input.fail())
    {
      input.clear();
    }
    std::copy(std::istream_iterator< Polygon >(input), std::istream_iterator< Polygon >(), std::back_inserter(shapes));
  }
  std::map < std::string, std::function< void(std::istream&, std::ostream&, std::list< Polygon >&) > > cmd;
  {
    using namespace std::placeholders;
    cmd["AREA"] = area_cmd;
    cmd["MAX"] = std::bind(extr_cmd, false, _1, _2, _3);
    cmd["MIN"] = std::bind(extr_cmd, true, _1, _2, _3);
    cmd["COUNT"] = count_cmd;
    cmd["LESSAREA"] = lessarea_cmd;
    cmd["INFRAME"] = inframe_cmd;
  }
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
    }
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
        throw std::invalid_argument("");
      }
      func->second(std::cin, std::cout, shapes);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
  }
  return 0;
}
