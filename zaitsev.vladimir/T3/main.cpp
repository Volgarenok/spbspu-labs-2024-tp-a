#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
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
    check_fail(input);
    std::copy(std::istream_iterator< Polygon >(input), std::istream_iterator< Polygon >(), std::back_inserter(shapes));
  }
  std::map < std::string, std::function< void(std::istream&, std::ostream&, std::list< Polygon >&) > > cmd;
  cmd["AREA"] = area_cmd;
  cmd["MAX"] = max_cmd;
  cmd["MIN"] = min_cmd;
  cmd["COUNT"] = count_cmd;
  cmd["LESSAREA"] = lessarea_cmd;
  cmd["INFRAME"] = inframe_cmd;
  while (!std::cin.eof())
  {
    check_fail(std::cin);
    try
    {
      std::string command;
      std::cin >> command;
      if (std::cin.eof())
      {
        break;
      }
      cmd.at(command)(std::cin, std::cout, shapes);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
  }
  return 0;
}
